 /******************************************************************************
 *
 * Module: DMA
 *
 * File Name: DMA.h
 *
* Description: Header file for STM32F103C8T6 Microcontroller - DMA Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#ifndef DMA_H
#define DMA_H

#define DMA_VENDOR_ID    (1000U)

/* DMA Module Id */
#define DMA_MODULE_ID    (120U)

/* DMA Instance Id */
#define DMA_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define DMA_SW_MAJOR_VERSION           (1U)
#define DMA_SW_MINOR_VERSION           (0U)
#define DMA_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DMA_AR_RELEASE_MAJOR_VERSION   (4U)
#define DMA_AR_RELEASE_MINOR_VERSION   (0U)
#define DMA_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"
   
/* AUTOSAR checking between Std Types and DMA Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DMA_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DMA_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DMA_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* DMA Pre-Compile Configuration Header file */
#include "DMA_Cfg.h"
#include "UART.h"
/* AUTOSAR Version checking between DMA_Cfg.h and DMA.h files */
#if ((DMA_CFG_AR_RELEASE_MAJOR_VERSION != DMA_AR_RELEASE_MAJOR_VERSION)\
 ||  (DMA_CFG_AR_RELEASE_MINOR_VERSION != DMA_AR_RELEASE_MINOR_VERSION)\
 ||  (DMA_CFG_AR_RELEASE_PATCH_VERSION != DMA_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of DMA_Cfg.h does not match the expected version"
#endif

/* Software Version checking between DMA_Cfg.h and DMA.h files */
#if ((DMA_CFG_SW_MAJOR_VERSION != DMA_SW_MAJOR_VERSION)\
 ||  (DMA_CFG_SW_MINOR_VERSION != DMA_SW_MINOR_VERSION)\
 ||  (DMA_CFG_SW_PATCH_VERSION != DMA_SW_PATCH_VERSION))
  #error "The SW version of DMA_Cfg.h does not match the expected version"
#endif   
   
/* Non AUTOSAR files */
#include "Common_Macros.h"
        
    /*=============== DMA 1 peripherals ===============/  
    /--------------- Channel 1 ---------------/
    None, ADC_1, TIM2_CH3, TIM4_CH1,
    /--------------- Channel 2 ---------------/
    SPI1_RX, USART3_TX, TIM1_CH1, TIM2_UP ,TIM3_CH3,
    /--------------- Channel 3 ---------------/
    SPI1_TX, USART3_RX, TIM1_CH2 ,TIM3_CH4 ,TIM3_UP,
    /--------------- Channel 4 ---------------/
    SPI2_RX, I2S2_RX, USART1_TX, I2C2_TX, TIM1_CH4 ,TIM1_TRIG ,TIM1_COM ,TIM4_CH2,
    /--------------- Channel 5 ---------------/
    SPI2_TX, I2S2_TX, USART1_RX, I2C2_RX, TIM1_UP, TIM2_CH1 ,TIM4_CH3,
    /--------------- Channel 6 ---------------/
    USART2_RX, I2C1_TX, TIM1_CH3 ,TIM3_CH1 , TIM3_TRIG,
    /--------------- Channel 7 ---------------/
    USART2_TX, I2C1_RX, TIM2_CH2 ,TIM2_CH4 ,TIM4_UP,
      
    /=============== DMA21 peripherals ===============/    
    /--------------- Channel 1 ---------------/
    SPI_RX, I2S3_RX, TIM5_CH4 ,TIM5_TRIG ,TIM8_CH3 ,TIM8_UP,
    /--------------- Channel 2 ---------------/
    SPI_TX, I2S3_TX, TIM5_CH3, TIM5_UP, TIM8_CH4, TIM8_TRIG ,TIM8_COM,
    /--------------- Channel 3 ---------------/
    UART4_RX, TIM6_UP, DAC_Channel1, TIM8_CH1,
    /--------------- Channel 4 ---------------/
    SDIO, TIM5_CH2, TIM7_UP, DAC_Channel2,
    /--------------- Channel 5 ---------------/
    ADC3, UART4_TX, TIM5_CH21 ,TIM8_CH2     
    /-------------------------------------------------*/ 

/*******************************************************************************
 *                              Module Data Types                              *
 ******************************************************************************/   
   
/* Description: Enum to hold data transfer direction */
typedef enum
{
    Memory_to_Memory, Read_From_Peripheral, Read_From_Memory 
}DMA_Direction;   
   
/* Description: Used to hold the size of the passed buffer that the value will be read or written into it */
typedef enum
{
   Bits_8, Bits_16, Bits_32
}SIZE;

/* Description: Used to hold the priority level of each channel */
typedef enum
{
  Low, Medium, High, Very_High
}Priority_Level;

/* Description: Used to hold the state of the required interrupt request */
typedef enum
{
  D_Disable, D_Enable 
}Mode;

/* Description: Structure to configure DMA: */
typedef struct
{
    uint8 Dma_Number;                           /* DMA 1 or DMA 2*/
    uint8 Channel_number;                       /* For DMA 1: Channel 1....7 or DMA 2: channel 1....5*/
     
    Priority_Level priority_level;              /* To Hold the priority level of the channel */

    SIZE Memory_Size;                           /* To Hold the Size of the passed buffer */ 
    SIZE Peripheral_Size;                       /* To Hold the Size of the Passed peripheral data register */
    
    Mode Memory_Increament;                     /* Memory increament mode is enabled if the passed buffer is a block of data for example array */
    Mode Peripheral_Increament;
    Mode Circular_Mode;                         /* If Circular mode is enabled then when the transfers are done the value in the CNDTR register will be reloaded again */
    
    DMA_Direction Direction;                    /* Wheather read from memory or read from peripheral or transfer is from memory location to memory location */
    
    uint32 Transfer_Number;
    
    uint32 Buffer_Address;                     /* To Hold the Address of the Buffer */     
    uint32 Peripheral_Address;                 /* To Hold the Address of the periphral Data register  */
       
}DMA_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 ******************************************************************************/

/* Description: 
          1- Configure data transfer direction, circular mode, peripheral & memory incremented 
             mode, peripheral & memory data size, and interrupt after half and/or full transfer in the 
             DMA_CCRx register.

          2- Configure the total number of data to be transferred in the DMA_CNDTRx register. 
             After each peripheral event, this value will be decremented.
          
          3- Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register
         
          4- Set the memory address in the DMA_CMARx register. The data will be written to or 
             read from this memory after the peripheral event.

          5- Set the peripheral register address in the DMA_CPARx register. The data will be 
             moved from/ to this address to/ from the memory after the peripheral event.
          
          6- Activate the channel by setting the ENABLE bit in the DMA_CCRx register.          
*/
extern uint8 Data_Array[500];
extern uint8 LPWAN_Data[500];
extern const DMA_ConfigType  DMA_Configurations;
extern const DMA_ConfigType  DMA_7_Configurations;
void DMA_Init( const DMA_ConfigType *DMA_Configuration);
void DMA_resetBuffer(uint8 *Memory_start);
void DMA_Disable(const DMA_ConfigType *DMA_Configuration);
void DMA_Enable(const DMA_ConfigType *DMA_Configuration);
void DMA_resetCNDTR(const DMA_ConfigType *DMA_Configuration);

#endif /* DMA_H */