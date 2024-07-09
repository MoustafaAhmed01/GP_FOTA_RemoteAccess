 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for STM32F401RCT6 Microcontroller - Port Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#include "Port.h"
#include "stm32f103c8t6_registers.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"

/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif
   
/* Static global variable to show If Port_Init function 
 * is not called first, then no operation can occur on 
 * the MCU ports and port pins. 
 */
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/* 
 * Pointer to hold the address of the passed configuration
 * array of structures
 */
STATIC volatile Port_ConfigType *Port_ConfigPtr = NULL_PTR;   

/************************************************************************************
* Service Name: Port_Init
* Service ID :0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(  Port_ConfigType* ConfigPtr )
{
      #if ( PORT_DEV_ERROR_DETECT == STD_ON )
      if(ConfigPtr == NULL_PTR)
      {
        Det_ReportError (
                            PORT_MODULE_ID, 
                            PORT_INSTANCE_ID,
                            Port_Init_SID,
                            PORT_E_PARAM_POINTER
                         );
        return ;
      }
      #endif
      
      Port_ConfigPtr = ConfigPtr ;
      Port_Status = PORT_INITIALIZED ;
      
      volatile uint32 delay = 0;
    
      /* index to configure each pin (32)*/
      uint8 Pin_Index; 
      for(Pin_Index = ZERO ; Pin_Index < PORT_CONFIGURED_CHANNLES ; Pin_Index++ )
      {
        /* point to the required Port Registers base address */
        volatile uint32 * PortGpio_Ptr = NULL_PTR; 
        switch( Port_ConfigPtr->Pin[Pin_Index].port_num )
        {
            /* PORTA Base Address */
            case  0: PortGpio_Ptr = &GPIO_PORTA_BASE_ADDRESS; 
                     break;
                     
            /* PORTB Base Address */         
            case  1: PortGpio_Ptr = &GPIO_PORTB_BASE_ADDRESS; 
                     break;
                     
            /* PORTC Base Address */         
            case  2: PortGpio_Ptr = &GPIO_PORTC_BASE_ADDRESS; 
                     break;
                     
            /* PORTD Base Address */         
            case  3: PortGpio_Ptr = &GPIO_PORTD_BASE_ADDRESS; 
                     break;
                     
            /* PORTE Base Address */         
            case  4: PortGpio_Ptr = &GPIO_PORTE_BASE_ADDRESS; 
                     break;
                     
            /* PORTF Base Address */         
            case  5: PortGpio_Ptr = &GPIO_PORTF_BASE_ADDRESS; 
                     break;
            
            /* PORTG Base Address */         
            case  6: PortGpio_Ptr = &GPIO_PORTG_BASE_ADDRESS; 
                     break;
        }
       
        /* Enable clock for PORT and allow time for clock to start*/
        SET_BIT( RCC_APB2ENR , Port_ConfigPtr->Pin[Pin_Index].port_num + 2 );
        
        if( Port_ConfigPtr->Pin[Pin_Index].pin_num < 8 )
        {
           /* First MASK the Port configuration register low at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00' ) */
           *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) &= ~( (0x0000000F) << 4 * (Port_ConfigPtr->Pin[Pin_Index].pin_num) );

           if( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_MODE_DIO )
           {
             if( Port_ConfigPtr->Pin[Pin_Index].Direction == PORT_PIN_IN )
             {
               if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_UP )
               {
                 /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000002) << (4 * Port_ConfigPtr->Pin[Pin_Index].pin_num ) + 2 );
                                           
                 /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                 SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin_Index].pin_num ); 
               }
               else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_DOWN )
               {
                 /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000002) << 4 * (Port_ConfigPtr->Pin[Pin_Index].pin_num ) + 2 );
                                           
                 /* Clear the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-DOWN */
                 CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin_Index].pin_num );
               }  
               else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  FLOATING )
               {
                 /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '01' ) to configure it as Input FLOATING */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000001) << 4 * (Port_ConfigPtr->Pin[Pin_Index].pin_num ) + 2 );    
               }
             }
             else if( Port_ConfigPtr->Pin[Pin_Index].Direction == PORT_PIN_OUT )
             {
                /* Set the corresponding bit in the GPIOx_CRL register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin_Index].pin_output_speed << 4* (Port_ConfigPtr->Pin[Pin_Index].pin_num) );
                      
                /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = ' General purpose output push-pull / open-drain ' ) to configure it as OUTPUT */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (Port_ConfigPtr->Pin[Pin_Index].pin_output_type ) << 4 * (Port_ConfigPtr->Pin[Pin_Index].pin_num ) + 2 );  
                      
                if(Port_ConfigPtr->Pin[Pin_Index].initial_value == LEVEL_HIGH)
                {
                  /* Set the corresponding bit in the GPIOx_ODR register to provide initial value 1 */
                  SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin_Index].pin_num );          
                }
                else
                {
                  /* Clear the corresponding bit in the GPIOx_ODR register to provide initial value 0 */
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin_Index].pin_num );        
                }
             }
           }
           else if( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_ANALOG )
           {
             /* Clear the corresponding bit in the GPIOx_CRL register ( MODEy[1:0] = '00' & CNFy[1:0] = '00' ) to configure it as ANALOG  */
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) &= ~( (0x0000000F) << 4 * (Port_ConfigPtr->Pin[Pin_Index].pin_num) );
           }
           else 
           {
             if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_PWM )
             {
                /* First we need to give the clock of the AFIO */
                 SET_BIT( RCC_APB2ENR , 0 );
                 /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00') */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) &= (0xFFFFFFF0);
                              
                 /* Set the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |= 11 ;
                      
//                 /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as AF purpose output push-pull */
//                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  (1<<19) | (1<<23); 
            
             }
             else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_SPI_SCK )  
             {}
             else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_SPI_MISO )
             {}
             else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_SPI_NSS )
             {}
             else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_SPI_MOSI )
             {}
             else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_I2C_SCL )
             {}
             else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_I2C_SDA )
             {}
           }     
        }
        else if ( Port_ConfigPtr->Pin[Pin_Index].pin_num >= 8 && Port_ConfigPtr->Pin[Pin_Index].pin_num <= 15 )
        {
          if( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_MODE_DIO )
          {
            /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] , MODEy[1:0] ) */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x0000000F) << 4 * (Port_ConfigPtr->Pin[Pin_Index].pin_num - 8) );
             
            if( Port_ConfigPtr->Pin[Pin_Index].Direction == PORT_PIN_IN )
            {                 
              if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_UP )
              {
                /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << ( 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) ) + 2 );
                 
                /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin_Index].pin_num ); 
              }
              else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_DOWN )
              {
                /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );
                  
                /* Clear the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-DOWN */
                CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin_Index].pin_num );
              }  
              else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  FLOATING )
              {
                /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '01' ) to configure it as Input with FLOATING */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000001) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );                  
              }
            }
            else if( Port_ConfigPtr->Pin[Pin_Index].Direction == PORT_PIN_OUT )
            {
              /* Set the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin_Index].pin_output_speed << 4* ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                      
              /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = ' General purpose output push-pull / open-drain ' ) to configure it as OUTPUT */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (Port_ConfigPtr->Pin[Pin_Index].pin_output_type ) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );  
                      
              if(Port_ConfigPtr->Pin[Pin_Index].initial_value == LEVEL_HIGH)
              {
                /* Set the corresponding bit in the GPIOx_ODR register to provide initial value 1 */
                SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num ) );          
              }
              else
              {
                /* Clear the corresponding bit in the GPIOx_ODR register to provide initial value 0 */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num ) );        
              }
            }
          }
          else if( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_ANALOG )
          {
            /* Clear the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = '00' & CNFy[1:0] = '00' ) to configure it as ANALOG  */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x0000000F) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );  
          }
          else 
          {
            if( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_CAN_RD )
            {
               if( Port_ConfigPtr->Pin[Pin_Index].pin_num == PORT_PIN_11 && *PortGpio_Ptr == GPIO_PORTA_BASE_ADDRESS )
               {
                 /* CAN_RX (Receive data line) Input floating / Input pull-up */  
                             
                 /* First we need to give the clock of the AFIO */
                 SET_BIT( RCC_APB2ENR , 0 );
                              
                 /* Then we need to activate the clock of the CAN */
                 SET_BIT( RCC_APB1ENR , 25 );
                             
                 /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] , MODEy[1:0] ) */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                                                      
                 if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_UP )
                 {
                   /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up */
                   *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );
                                 
                   /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                   SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num ) ); 
                 }
                 else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  FLOATING )
                 {
                   /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with FLOATING  */
                   *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000001) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );
                 }     
               }
               else 
               {
                 /* Do Nothing */
               }
            }
            else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_CAN_TD )
            {
               if( Port_ConfigPtr->Pin[Pin_Index].pin_num == PORT_PIN_12 && *PortGpio_Ptr == GPIO_PORTA_BASE_ADDRESS )
               {
                  /* CAN_TX (Transmit data line) Alternate function push-pull */  
                            
                  /* First we need to give the clock of the AFIO */
                  SET_BIT( RCC_APB2ENR , 0 );
                                
                  /* Then we need to activate the clock of the CAN */
                  SET_BIT( RCC_APB1ENR , 25 );
                               
                  /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00') */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                               
                  /* Set the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin_Index].pin_output_speed << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                      
                  /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as General purpose output push-pull */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( ( 0x00000002 ) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );        
               }
               else 
               {
                  /* Do Nothing */
               }
            }
            else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_PWM )
            {
                                    
                 /* First we need to give the clock of the AFIO */
                 SET_BIT( RCC_APB2ENR , 0 );
                 /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00') */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= (0xFFFFFFF0);
                              
                 /* Set the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin_Index].pin_output_speed << 0 );
                      
                 /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as AF purpose output push-pull */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  (1<<3); 
            }                     
            else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_SERIAL_TX )
            {
               if( Port_ConfigPtr->Pin[Pin_Index].pin_num == PORT_PIN_9 && *PortGpio_Ptr == GPIO_PORTA_BASE_ADDRESS )
               {
                 /*
                 *Full duplex Alternate function push-pull
                 *Half duplex synchronous mode Alternate function push-pull
                 */
                             
                 /* First we need to give the clock of the AFIO */
                 SET_BIT( RCC_APB2ENR , 0 );
                                
                 /* Then we need to activate the clock of the UART */
                 SET_BIT( RCC_APB2ENR , 14 );  
                               
                 /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00') */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                              
                 /* Set the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin_Index].pin_output_speed << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                      
                 /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as General purpose output push-pull */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( ( 0x00000002 ) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );                               
               }
               else 
               {
                 /* Do Nothing */
               }
            }
            else if ( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_FUNC_ALT_SERIAL_RX )
            {
               if( Port_ConfigPtr->Pin[Pin_Index].pin_num == PORT_PIN_10 && *PortGpio_Ptr == GPIO_PORTA_BASE_ADDRESS )
               {
                 /*
                  * Full duplex Input floating / Input pull-up
                  * Half duplex synchronous mode Not used. Can be used as a general IO
                  */
                             
                  /* First we need to give the clock of the AFIO */
                  SET_BIT( RCC_APB2ENR , 0 );
                                
                  /* Then we need to activate the clock of the UART */
                  SET_BIT( RCC_APB2ENR , 14 ); 
                                
                  /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] , MODEy[1:0] ) */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                                                      
                  /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );
                               
                  /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                  SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num ) ); 
                                              
               }
               else 
               {
                 /* Do Nothing */
               }                      
            }          
          }        
        }
      }
}
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID :0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Direction - Port Pin Direction
*                  Direction Type - OFF , PIN_FLOATING , PIN_PULL_UP , PIN_PULL_DOWN , PIN_PUSH_PULL , PIN_OPEN_DRAIN
*                  Direction Speed - Default , PIN_10MHz_SPEED , PIN_2MHz_SPEED , PIN_50MHz_SPEED     
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
void Port_SetPinDirection( Port_PinType Pin , Port_PinDirectionType Direction , Direction_Type Type , Direction_Speed Speed) 
{
#if ( PORT_DEV_ERROR_DETECT == STD_ON )
    if( Port_Status == PORT_NOT_INITIALIZED )
    {
        Det_ReportError (
                         PORT_MODULE_ID,
                         PORT_INSTANCE_ID,
                         Port_SetPinDirection_SID,
                         PORT_E_UNINIT
                         );
    }
    if( Pin >= PORT_CONFIGURED_CHANNLES )
    {
        Det_ReportError (
                         PORT_MODULE_ID,
                         PORT_INSTANCE_ID,
                         Port_SetPinDirection_SID,
                         PORT_E_PARAM_PIN
                         );
    }    
    if( Port_ConfigPtr->Pin[Pin].pin_dir_changeable == Direction_UnChangeable )
    {
        Det_ReportError (
                         PORT_MODULE_ID,
                         PORT_INSTANCE_ID,
                         Port_SetPinDirection_SID,
                         PORT_E_DIRECTION_UNCHANGEABLE
                         );
    }
    
#endif
    
          /* point to the required Port Registers base address */
          volatile uint32 * PortGpio_Ptr = NULL_PTR; 
          volatile uint32 delay = 0;         
        
          switch( Port_ConfigPtr -> Pin[Pin].port_num )
          {
                /* PORTA Base Address */
                case  0: PortGpio_Ptr = &GPIO_PORTA_BASE_ADDRESS; 
                         break;
                         
                /* PORTB Base Address */         
                case  1: PortGpio_Ptr = &GPIO_PORTB_BASE_ADDRESS; 
                         break;
                         
                /* PORTC Base Address */         
                case  2: PortGpio_Ptr = &GPIO_PORTC_BASE_ADDRESS; 
                         break;
                         
                /* PORTD Base Address */         
                case  3: PortGpio_Ptr = &GPIO_PORTD_BASE_ADDRESS; 
                         break;
                         
                /* PORTE Base Address */         
                case  4: PortGpio_Ptr = &GPIO_PORTE_BASE_ADDRESS; 
                         break;
                         
                /* PORTF Base Address */         
                case  5: PortGpio_Ptr = &GPIO_PORTF_BASE_ADDRESS; 
                         break;
                
                /* PORTG Base Address */         
                case  6: PortGpio_Ptr = &GPIO_PORTG_BASE_ADDRESS; 
                         break;
          }
          
          /* Enable clock for PORT and allow time for clock to start*/
          SET_BIT( RCC_APB2ENR , Port_ConfigPtr->Pin[Pin].port_num + 2 );
          
            if( Port_ConfigPtr->Pin[Pin].pin_num < 8 )
            {              
              if( Port_ConfigPtr->Pin[Pin].Mode == PORT_PIN_MODE_DIO )
              {
                  /* First MASK the Port configuration register low at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00' ) */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) &= ~( (0x0000000F) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num) );
                  
                  if( Direction == PORT_PIN_IN )
                  {
                     /* Save the new change in the direction in our configuration array of structure */
                     Port_ConfigPtr->Pin[Pin].Direction = PORT_PIN_IN;
                     
                     if( Type ==  PIN_PULL_UP )
                     {
                       /* Save the new change in the input type in our configuration array of structure */
                       Port_ConfigPtr->Pin[Pin].pin_internal_resistance = PULL_UP;
                       
                       /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000002) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num ) + 2 );
                                                    
                       /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                       SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin].pin_num ); 
                     }
                     else if( Type ==  PIN_PULL_DOWN )
                     {
                        /* Save the new change in the input type in our configuration array of structure */
                        Port_ConfigPtr->Pin[Pin].pin_internal_resistance = PULL_DOWN; 
                       
                        /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000002) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num ) + 2 );
                                                    
                        /* Clear the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-DOWN */
                        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin].pin_num );
                     }  
                     else if( Type ==  PIN_FLOATING )
                     {
                        /* Save the new change in the input type in our configuration array of structure */
                        Port_ConfigPtr->Pin[Pin].pin_internal_resistance = FLOATING;
                        
                        /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '01' ) to configure it as Input FLOATING */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000001) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num ) + 2 );    
                     }
                  }
                  else if( Direction == PORT_PIN_OUT )
                  {
                      /* Save the new change in the direction in our configuration array of structure */
                      Port_ConfigPtr->Pin[Pin].Direction = PORT_PIN_OUT;
                      
                     /* Set the corresponding bit in the GPIOx_CRL register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                     *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |= ( Speed << 4* (Port_ConfigPtr->Pin[Pin].pin_num) );
                     
                     if( Type ==  PIN_PUSH_PULL )
                     {
                       /* Save the new change in the output type in our configuration array of structure */
                       Port_ConfigPtr->Pin[Pin].pin_output_type = PORT_GP_PIN_PUSH_PULL;
                       
                       /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '00' ) to configure it as OUTPUT with GP PUSH_PULL */
                       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) &= ~( (0x00000003) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num ) + 2 );
                     }
                     else if( Type ==  PIN_OPEN_DRAIN )
                     {
                        /* Save the new change in the output type in our configuration array of structure */
                        Port_ConfigPtr->Pin[Pin].pin_output_type = PORT_GP_PIN_OPEN_DRAIN;
                        
                        /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '01' ) to configure it as OUTPUT with OPEN_DRAIN */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000001) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num ) + 2 );
                     }  
                               
                     if(Port_ConfigPtr->Pin[Pin].initial_value == LEVEL_HIGH)
                     {
                        /* Set the corresponding bit in the GPIOx_ODR register to provide initial value 1 */
                        SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin].pin_num );          
                     }
                     else
                     {
                        /* Clear the corresponding bit in the GPIOx_ODR register to provide initial value 0 */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin].pin_num );        
                     }
                  }    
              }
            }
            else if( Port_ConfigPtr->Pin[Pin].pin_num >= 8 && Port_ConfigPtr->Pin[Pin].pin_num < 16 )
            {              
              if( Port_ConfigPtr->Pin[Pin].Mode == PORT_PIN_MODE_DIO )
              {
                  /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00' ) */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x0000000F) << 4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) );
                  
                  if( Direction == PORT_PIN_IN )
                  {
                     if( Type ==  PIN_PULL_UP )
                     {
                       /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) <<( 4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) + 2 ));
                                                    
                       /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                       SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin].pin_num ) ); 
                     }
                     else if( Type ==  PIN_PULL_DOWN )
                     {
                        /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << (4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) + 2) );
                                                    
                        /* Clear the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-DOWN */
                        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin].pin_num ) );
                     }  
                     else if( Type ==  PIN_FLOATING )
                     {
                        /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '01' ) to configure it as Input FLOATING */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000001) << (4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) + 2) );    
                     }
                  }
                  else if( Direction == PORT_PIN_OUT )
                  {
                     /* Set the corresponding bit in the GPIOx_CRL register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                     *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |= ( Speed << 4* ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) );
                     
                     if( Type ==  PIN_PUSH_PULL )
                     {
                       /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '00' ) to configure it as OUTPUT with PUSH_PULL */
                       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << (4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) + 2) );
                     }
                     else if( Type ==  PIN_OPEN_DRAIN )
                     {
                        /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '01' ) to configure it as OUTPUT with OPEN_DRAIN */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000001) << (4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) + 2) );
                     }  
                               
                     if(Port_ConfigPtr->Pin[Pin].initial_value == LEVEL_HIGH)
                     {
                        /* Set the corresponding bit in the GPIOx_ODR register to provide initial value 1 */
                        SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin].pin_num ) );          
                     }
                     else
                     {
                        /* Clear the corresponding bit in the GPIOx_ODR register to provide initial value 0 */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin].pin_num ) );        
                     }
                  }    
              }
            }
}
#endif
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID :0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction. 
************************************************************************************/
void Port_RefreshPortDirection( void )
{
#if ( PORT_DEV_ERROR_DETECT == STD_ON )
  
      if( Port_Status == PORT_NOT_INITIALIZED )
    {
        Det_ReportError (
                         PORT_MODULE_ID,
                         PORT_INSTANCE_ID,
                         Port_RefreshPortDirection_SID,
                         PORT_E_UNINIT
                         );
    }
    
#endif
    
    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;
    
    /* index to configure each pin (31)*/
    uint8 Pin_Index;              
    
    for(Pin_Index = 0 ; Pin_Index < PORT_CONFIGURED_CHANNLES ; Pin_Index++ )
    {
      switch( Port_ConfigPtr -> Pin[Pin_Index].port_num )
      {
            /* PORTA Base Address */
            case  0: PortGpio_Ptr = &GPIO_PORTA_BASE_ADDRESS; 
                     break;
                     
            /* PORTB Base Address */         
            case  1: PortGpio_Ptr = &GPIO_PORTB_BASE_ADDRESS; 
                     break;
                     
            /* PORTC Base Address */         
            case  2: PortGpio_Ptr = &GPIO_PORTC_BASE_ADDRESS; 
                     break;
                     
            /* PORTD Base Address */         
            case  3: PortGpio_Ptr = &GPIO_PORTD_BASE_ADDRESS; 
                     break;
                     
            /* PORTE Base Address */         
            case  4: PortGpio_Ptr = &GPIO_PORTE_BASE_ADDRESS; 
                     break;
                     
            /* PORTF Base Address */         
            case  5: PortGpio_Ptr = &GPIO_PORTF_BASE_ADDRESS; 
                     break;
            
            /* PORTG Base Address */         
            case  6: PortGpio_Ptr = &GPIO_PORTG_BASE_ADDRESS; 
                     break;
      }
      
      /* Enable clock for PORT and allow time for clock to start*/
      SET_BIT( RCC_APB2ENR , Port_ConfigPtr->Pin[Pin_Index].port_num + 2 );
      
      if( Port_ConfigPtr -> Pin[Pin_Index].pin_dir_changeable == Direction_UnChangeable )
      { 
        if( Port_ConfigPtr->Pin[Pin_Index].pin_num < 8 )
        {
              /* First MASK the Port configuration register low at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00' ) */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) &= ~( (0x0000000F) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );

              if( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_MODE_DIO )
              {
                if( Port_ConfigPtr->Pin[Pin_Index].Direction == PORT_PIN_IN )
                {
                  if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_UP )
                  {
                    /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000002) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );
                                                
                    /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                    SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) ); 
                  }
                  else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_DOWN )
                  {
                    /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000002) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );
                                                
                    /* Clear the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-DOWN */
                    CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                  }  
                  else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  FLOATING )
                  {
                    /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = '01' ) to configure it as Input FLOATING */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (0x00000001) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );    
                  }
               }
               else if( Port_ConfigPtr->Pin[Pin_Index].Direction == PORT_PIN_OUT )
               {
                  /* Set the corresponding bit in the GPIOx_CRL register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin_Index].pin_output_speed << 4* ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                          
                  /* Set the corresponding bit in the GPIOx_CRL register ( CNFy[1:0] = ' General purpose output push-pull / open-drain ' ) to configure it as OUTPUT */
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) |=  ( (Port_ConfigPtr->Pin[Pin_Index].pin_output_type ) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );  
                          
                  if(Port_ConfigPtr->Pin[Pin_Index].initial_value == LEVEL_HIGH)
                  {
                    /* Set the corresponding bit in the GPIOx_ODR register to provide initial value 1 */
                    SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );          
                  }
                  else
                  {
                    /* Clear the corresponding bit in the GPIOx_ODR register to provide initial value 0 */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );        
                  }
              }    
            }
        }
        else if( Port_ConfigPtr->Pin[Pin_Index].pin_num >= 8 && Port_ConfigPtr->Pin[Pin_Index].pin_num < 16 )
        {
            if( Port_ConfigPtr->Pin[Pin_Index].Mode == PORT_PIN_MODE_DIO )
            {
                /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] , MODEy[1:0] ) */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x0000000F) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                
                if( Port_ConfigPtr->Pin[Pin_Index].Direction == PORT_PIN_IN )
                {                 
                   if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_UP )
                   {
                         /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                         *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );
                    
                         /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                         SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num ) ); 
                   }
                   else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  PULL_DOWN )
                   {
                         /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up / pull-down */
                         *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );
                    
                         /* Clear the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-DOWN */
                         CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num ) );
                   }  
                   else if( Port_ConfigPtr->Pin[Pin_Index].pin_internal_resistance ==  FLOATING )
                   {
                         /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '01' ) to configure it as Input with FLOATING */
                         *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000001) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );                  
                   }
                }
                else if( Port_ConfigPtr->Pin[Pin_Index].Direction == PORT_PIN_OUT )
                {
                        /* Set the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin_Index].pin_output_speed << 4* ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) );
                        
                        /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = ' General purpose output push-pull / open-drain ' ) to configure it as OUTPUT */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (Port_ConfigPtr->Pin[Pin_Index].pin_output_type ) << 4 * ( Port_ConfigPtr->Pin[Pin_Index].pin_num - 8 ) + 2 );  
                        
                         if(Port_ConfigPtr->Pin[Pin_Index].initial_value == LEVEL_HIGH)
                         {
                            /* Set the corresponding bit in the GPIOx_ODR register to provide initial value 1 */
                            SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num ) );          
                         }
                         else
                         {
                            /* Clear the corresponding bit in the GPIOx_ODR register to provide initial value 0 */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin_Index].pin_num ) );        
                         }
                 }       
             }  
        }    
      }
  }
}
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID :0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module. 
************************************************************************************/
#if ( PORT_VERSION_INFO_API== STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if(Port_Status == PORT_NOT_INITIALIZED)
    {
	Det_ReportError ( PORT_MODULE_ID,
                          PORT_INSTANCE_ID, 
                          PORT_GET_VERSION_INFO_SID, 
                          PORT_E_UNINIT
                        );
    }
	
    /* check if the input configuration pointer is not a NULL_PTR */
    if(versioninfo == NULL_PTR)
    {
	Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }				             		
#endif    
    /* Copy the module Id */
    versioninfo->moduleID = (uint16)PORT_MODULE_ID;
    /* Copy the vendor Id */
    versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;    
}
#endif
/************************************************************************************
* Service Name: Port_SetPinMode 
* Service ID :0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description:  Sets the port pin mode. 
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(
                                        PORT_MODULE_ID, 
                                        PORT_INSTANCE_ID, 
                                        Port_SetPinMode_SID,
                                        PORT_E_UNINIT
                                        );
		}
		/* check if incorrect Port Pin ID passed */
		if(Pin >= PORT_CONFIGURED_CHANNLES)
		{
			Det_ReportError( 
                                       PORT_MODULE_ID, 
                                       PORT_INSTANCE_ID, 
                                       Port_SetPinMode_SID, 
                                       PORT_E_PARAM_PIN
                                         );
		}		
		/* check if the Port Pin Mode passed not valid */
		if(Mode > PORT_PIN_ANALOG)
		{
			Det_ReportError(
                                        PORT_MODULE_ID, 
                                        PORT_INSTANCE_ID, 
                                        Port_SetPinMode_SID, 
                                        PORT_E_PARAM_INVALID_MODE
                                        );
		}
		if(Port_ConfigPtr->Pin[Pin].pin_mode_changeable == Mode_UnChangeable)
		{
			Det_ReportError(
                                        PORT_MODULE_ID,
                                        PORT_INSTANCE_ID,
                                        Port_SetPinMode_SID,
                                        PORT_E_MODE_UNCHANGEABLE
                                        );
		}
	#endif
                
          /* point to the required Port Registers base address */
        volatile uint32 * PortGpio_Ptr = NULL_PTR; 
        switch( Port_ConfigPtr->Pin[Pin].port_num )
        {
            /* PORTA Base Address */
            case  0: PortGpio_Ptr = &GPIO_PORTA_BASE_ADDRESS; 
                     break;
                     
            /* PORTB Base Address */         
            case  1: PortGpio_Ptr = &GPIO_PORTB_BASE_ADDRESS; 
                     break;
                     
            /* PORTC Base Address */         
            case  2: PortGpio_Ptr = &GPIO_PORTC_BASE_ADDRESS; 
                     break;
                     
            /* PORTD Base Address */         
            case  3: PortGpio_Ptr = &GPIO_PORTD_BASE_ADDRESS; 
                     break;
                     
            /* PORTE Base Address */         
            case  4: PortGpio_Ptr = &GPIO_PORTE_BASE_ADDRESS; 
                     break;
                     
            /* PORTF Base Address */         
            case  5: PortGpio_Ptr = &GPIO_PORTF_BASE_ADDRESS; 
                     break;
            
            /* PORTG Base Address */         
            case  6: PortGpio_Ptr = &GPIO_PORTG_BASE_ADDRESS; 
                     break;
        }
       
        /* Enable clock for PORT and allow time for clock to start*/
        SET_BIT( RCC_APB2ENR , Port_ConfigPtr->Pin[Pin].port_num + 2 );

        if( Mode == PORT_PIN_MODE_DIO)
        {
              Port_ConfigPtr->Pin[Pin].Mode = PORT_PIN_MODE_DIO;
        }
        else if (Mode == PORT_PIN_ANALOG)
        {
            if (  Port_ConfigPtr->Pin[Pin].pin_num < 8 )
            {
              /* Clear the corresponding bit in the GPIOx_CRL register ( MODEy[1:0] = '00' & CNFy[1:0] = '00' ) to configure it as ANALOG  */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_LOW_REG_OFFSET) &= ~( (0x0000000F) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num) );                            
            }
            else if ( Port_ConfigPtr->Pin[Pin].pin_num >= 8 && Port_ConfigPtr->Pin[Pin].pin_num <= 15 )
            {
              /* Clear the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = '00' & CNFy[1:0] = '00' ) to configure it as ANALOG  */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x0000000F) << 4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) );                            
            }                                  
        }
        else 
        {
             if (  Port_ConfigPtr->Pin[Pin].pin_num < 8 )
             {
                if ( Mode == PORT_PIN_FUNC_ALT_PWM )
                {
                   Port_ConfigPtr->Pin[Pin].Mode = PORT_PIN_FUNC_ALT_PWM;
                }
                else
                {
                   Port_ConfigPtr->Pin[Pin].Mode = Mode;                        
                }
             }
             else if ( Port_ConfigPtr->Pin[Pin].pin_num >= 8 && Port_ConfigPtr->Pin[Pin].pin_num <= 15 )
             {
                Port_ConfigPtr->Pin[Pin].Mode = Mode;
                
                if( Port_ConfigPtr->Pin[Pin].Mode == PORT_PIN_FUNC_ALT_CAN_RD )
                {
                   if( Port_ConfigPtr->Pin[Pin].pin_num == PORT_PIN_11 && *PortGpio_Ptr == GPIO_PORTA_BASE_ADDRESS )
                   {
                      /* CAN_RX (Receive data line) Input floating / Input pull-up */  
                             
                      /* First we need to give the clock of the AFIO */
                      SET_BIT( RCC_APB2ENR , 0 );
                              
                      /* Then we need to activate the clock of the CAN */
                      SET_BIT( RCC_APB1ENR , 25 );
                              
                      /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] , MODEy[1:0] ) */
                      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << 4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) );
                                                       
                      if( Port_ConfigPtr->Pin[Pin].pin_internal_resistance ==  PULL_UP )
                      {
                        /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << 4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) + 2 );
                                 
                        /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                        SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , ( Port_ConfigPtr->Pin[Pin].pin_num ) ); 
                      }
                      else if( Port_ConfigPtr->Pin[Pin].pin_internal_resistance ==  FLOATING )
                      {
                        /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with FLOATING  */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000001) << 4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) + 2 );
                      }     
                   }
                   else 
                   {
                      /* Do Nothing */
                   }
               }
               else if ( Port_ConfigPtr->Pin[Pin].Mode == PORT_PIN_FUNC_ALT_CAN_TD )
               {
                 if( Port_ConfigPtr->Pin[Pin].pin_num == PORT_PIN_12 && *PortGpio_Ptr == GPIO_PORTA_BASE_ADDRESS )
                 {
                   /* CAN_TX (Transmit data line) Alternate function push-pull */  
                             
                   /* First we need to give the clock of the AFIO */
                   SET_BIT( RCC_APB2ENR , 0 );
                                
                   /* Then we need to activate the clock of the CAN */
                   SET_BIT( RCC_APB1ENR , 25 );
                               
                   /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00') */
                   *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << 4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) );
                               
                   /* Set the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                   *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin].pin_output_speed << 4 * ( Port_ConfigPtr->Pin[Pin].pin_num - 8 ) );
                      
                   /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as General purpose output push-pull */
                   *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( ( 0x00000002 ) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num - 8) + 2 );   
                    
                 }
                 else 
                 {
                   /* Do Nothing */
                 }
               }
               else if ( Port_ConfigPtr->Pin[Pin].Mode == PORT_PIN_FUNC_ALT_PWM )
               {
                      
               }                     
               else if ( Port_ConfigPtr->Pin[Pin].Mode == PORT_PIN_FUNC_ALT_SERIAL_TX )
               {
                 if( Port_ConfigPtr->Pin[Pin].pin_num == PORT_PIN_9 && *PortGpio_Ptr == GPIO_PORTA_BASE_ADDRESS )
                 {
                   /*
                    *Full duplex Alternate function push-pull
                    *Half duplex synchronous mode Alternate function push-pull
                    */
                             
                   /* First we need to give the clock of the AFIO */
                   SET_BIT( RCC_APB2ENR , 0 );
                               
                   /* Then we need to activate the clock of the UART */
                   SET_BIT( RCC_APB2ENR , 14 );  
                               
                   /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] = '00' , MODEy[1:0] = '00') */
                   *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num - 8) );
                               
                   /* Set the corresponding bit in the GPIOx_CRH register ( MODEy[1:0] = ' Output mode, max speed value' ) to configure it as OUTPUT with required max speed */
                   *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |= ( Port_ConfigPtr->Pin[Pin].pin_output_speed << 4 * (Port_ConfigPtr->Pin[Pin].pin_num - 8) );
                      
                    /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as General purpose output push-pull */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( ( 0x00000002 ) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num -8) + 2 );                               
                   }
                 else 
                 {
                    /* Do Nothing */
                 }
                }
               else if ( Port_ConfigPtr->Pin[Pin].Mode == PORT_PIN_FUNC_ALT_SERIAL_RX )
               {
                 if( Port_ConfigPtr->Pin[Pin].pin_num == PORT_PIN_10 && *PortGpio_Ptr == GPIO_PORTA_BASE_ADDRESS )
                 {
                    /*
                     * Full duplex Input floating / Input pull-up
                     * Half duplex synchronous mode Not used. Can be used as a general IO
                     */
                             
                    /* First we need to give the clock of the AFIO */
                    SET_BIT( RCC_APB2ENR , 0 );
                               
                    /* Then we need to activate the clock of the UART */
                    SET_BIT( RCC_APB2ENR , 14 ); 
                              
                    /* First MASK the Port configuration register high at the required pins ( CNFy[1:0] , MODEy[1:0] ) */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) &= ~( (0x00000003) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num - 8) );
                                                      
                    /* Set the corresponding bit in the GPIOx_CRH register ( CNFy[1:0] = '10' ) to configure it as Input with pull-up */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CONF_HIGH_REG_OFFSET) |=  ( (0x00000002) << 4 * (Port_ConfigPtr->Pin[Pin].pin_num - 8) + 2 );
                               
                    /* Set the corresponding bit in the GPIOx_ODR register to configure it as INPUT with PULL-UP */
                    SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OUTPUT_DATA_REG_OFFSET) , Port_ConfigPtr->Pin[Pin].pin_num );                                 
                  }
                  else 
                  {
                    /* Do Nothing */
                  }                      
            }                         
        }
      } 
}
#endif












