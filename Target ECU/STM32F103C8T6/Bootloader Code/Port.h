 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
* Description: Header file for STM32F103C8T6 Microcontroller - Port Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Ahmed Hatem's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (120U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
   
/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif
   
/* Non AUTOSAR files */
#include "Common_Macros.h"

#define ZERO                             (0U)  
   
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
   
/* Service ID for Port init function */   
#define Port_Init_SID                    (uint8)(0x00)
   
/* Service ID for Port Set Pin Direction function */ 
#define Port_SetPinDirection_SID         (uint8)(0x01)
   
/* Service ID for Port Refresh Port Direction function */ 
#define Port_RefreshPortDirection_SID    (uint8)(0x02)
   
/* Service ID for Port Get Version Info function */   
#define PORT_GET_VERSION_INFO_SID        (uint8)(0x03) 
 
/* Service ID for Port Set Pin Mode function */   
#define Port_SetPinMode_SID              (uint8)(0x04)    
   
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Det code for Invalid Port Pin ID request  */
#define PORT_E_PARAM_PIN                 (uint8)(0x0A)

/* Det code for Port Pin not configured as changeable  */
#define PORT_E_DIRECTION_UNCHANGEABLE    (uint8)(0x0B)

/* DET code for API Port_Init service called with wrong parameter. */
#define PORT_E_PARAM_CONFIG              (uint8)(0x0C)

/* API Port_SetPinMode service called when Port Pin Mode passed not valid */
#define PORT_E_PARAM_INVALID_MODE 	 (uint8)(0x0D)

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE 	 (uint8)(0x0E)

/* API service called without module initialization */
#define PORT_E_UNINIT 			 (uint8)(0x0F)

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER 		 (uint8)(0x10)   
   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN , PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold Pin level init */
typedef enum
{
    LEVEL_LOW , LEVEL_HIGH  
}Pin_Level_Init;
  
/*Description: Enum to hold if Pin is Locked or not during runtime*/
typedef enum
{
    PORT_PIN_LOCKED ,PORT_PIN_UNLOCKED  
}Pin_Lock;

/* Description: Enum to hold pin output type */
typedef enum
{
    PORT_GP_PIN_PUSH_PULL , PORT_GP_PIN_OPEN_DRAIN , PORT_AF_PIN_PUSH_PULL , PORT_AF_PIN_OPEN_DRAIN 
}PORT_PinDrivenMode;

/* Description: Enum to hold PIN mode */
typedef enum
{
     PORT_PIN_FUNC_ALT_CAN_TD = 0,
     PORT_PIN_FUNC_ALT_CAN_RD,
     PORT_PIN_FUNC_ALT_PWM,
     PORT_PIN_FUNC_ALT_SPI_NSS,
     PORT_PIN_FUNC_ALT_SPI_SCK,
     PORT_PIN_FUNC_ALT_SPI_MISO,
     PORT_PIN_FUNC_ALT_SPI_MOSI,
     PORT_PIN_FUNC_ALT_I2C_SDA,
     PORT_PIN_FUNC_ALT_I2C_SCL,
     PORT_PIN_FUNC_ALT_SERIAL_RX,
     PORT_PIN_FUNC_ALT_SERIAL_TX,
     PORT_PIN_MODE_DIO,
     PORT_PIN_ANALOG  
}Port_PinModeType;

/* Description: Enum to hold pin output speed */
typedef enum
{
    PORT_PIN_10MHz_SPEED = 1 , PORT_PIN_2MHz_SPEED , PORT_PIN_50MHz_SPEED  
}PORT_PinOutputSpeed;
   
/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    FLOATING , PULL_UP , PULL_DOWN
}Port_PinInternalResistor;

/*Description: Enum to hold if Pin direction changeable during runtime*/
typedef enum
{
    Direction_UnChangeable ,Direction_Changeable 
}Pin_Direction_Changeable;

/*Description: Enum to hold if Pin mode changeable during runtime*/
typedef enum
{
    Mode_UnChangeable ,Mode_Changeable  
}Pin_Mode_Changeable;

/* Description: To hold Different port types */
typedef  uint8 Port_PortType ;

/* Description: Data type for the symbolic name of a port pin. */
typedef  uint8 Port_PinType ;

/* Description: Direction type for input or the output of a port pin. */
typedef enum
{
    OFF ,
    PIN_FLOATING , 
    PIN_PULL_UP , 
    PIN_PULL_DOWN ,
    PIN_PUSH_PULL , 
    PIN_OPEN_DRAIN
}Direction_Type;

/* Description: Output Speed of a port pin. */
typedef enum
{
    Default,
    PIN_10MHz_SPEED ,
    PIN_2MHz_SPEED , 
    PIN_50MHz_SPEED , 
}Direction_Speed; 
    

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT (pin0 to pin15, except H0 and H1 only) .
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. initial port pin value (low , high)
 *      5. the port pin lock is activated or not (LOCKED , UNLOCKED)
 *      6. initial port pin mode  (DIO , ALTERNATE , ANALOG)
 *      7. the output type of pin --> Push Pull or Open Drain
 *      8. the output speed of pin --> Low , Mid , High , Very high
 *      9. the internal resistor --> Disable, Pull up or Pull down
 *      10.pin direction changeable (true, false)
 *      11. pin mode changeable (true, false)        
 */
typedef struct
{
    Port_PortType port_num;
    
    Port_PinType  pin_num;
    
    Port_PinDirectionType Direction;                            /*PORT_PIN_IN , PORT_PIN_OUT*/
    
    Pin_Level_Init initial_value;                               /*LEVEL_LOW , LEVEL_HIGH  */
    
    Pin_Lock Lock_Typed;                                        /*PORT_PIN_LOCKED ,PORT_PIN_UNLOCKED */
        
    Port_PinModeType Mode;	                                /* PORT_PIN_MODE_DIO, PORT_ALT_FUNC, PORT_PIN_ANALOG*/
      				
    PORT_PinDrivenMode   pin_output_type;                       /*PORT_PIN_PUSH_PULL, PORT_PIN_OPEN_DRAIN*/
    
    PORT_PinOutputSpeed  pin_output_speed;                      /*PORT_PIN_LOW_SPEED , PORT_PIN_MID_SPEED , PORT_PIN_HIGH_SPEED , PORT_PIN_VERY_HIGH_SPEED, */
      
    Port_PinInternalResistor  pin_internal_resistance;          /*OFF , PULL_UP , PULL_DOWN*/
                  
    Pin_Direction_Changeable pin_dir_changeable;		/* STD_ON,STD_OFF*/
    
    Pin_Mode_Changeable pin_mode_changeable;		     	/* STD_ON,STD_OFF */
        
}Port_ConfigPin;

/* Array of Port_ConfigPin */
typedef struct
{
	Port_ConfigPin Pin[PORT_CONFIGURED_CHANNLES];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

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

void Port_Init(  Port_ConfigType* ConfigPtr ); 
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

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID :0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
void Port_SetPinDirection( Port_PinType Pin , Port_PinDirectionType Direction , Direction_Type Type , Direction_Speed Speed);

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
void Port_RefreshPortDirection( void ); 

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
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );

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
void Port_SetPinMode( Port_PinType Pin , Port_PinModeType Mode ); 

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Post build structure used with Port_Init API */
extern Port_ConfigType Port_Configuration;

#endif /* PORT_H */



