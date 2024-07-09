/******************************************************************************
 *
 * Module: USART2
 *
 * File Name: UART2.h
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - UART Driver.
 *
 * Author: Moustafa/Hatem
 ******************************************************************************/
#ifndef UART2_H
#define UART2_H

#include "Std_Types.h"
#include "Common_Macros.h"
#include "stm32f103c8t6_registers.h"
#include "UART_Regs.h"
#include "Port.h"

#define  USART_2_CR1_MASK               0xFFFFC80F  
   
/*Description: Enum to hold the state of the parity enabled or disabled */   
typedef enum
{
    Disable_2 ,
    Enable_2
}UART2_Parity_Control;

/*Description: Enum to hold the type of parity */
typedef enum
{
    Even_Parity_2 ,
    Odd_Parity_2
}UART2_Parity;

/*Description: Enum to hold the number of stop bits */
typedef enum
{
    One_Stop_Bit_2,
    Half_Stop_Bit_2,
    Two_Stop_Bit_2,
    OneAndHalf_Stop_Bit_2
    
}UART2_StopBit;

/*Description: Enum to hold the word length */
typedef enum
{
    DATA_8_Bits_2 ,
    DATA_9_Bits_2_2
}UART2_Word_Length;

/*Description: Enum to hold if Parity Error Interrupt is activated or not */
typedef enum
{
    PEI_DISABLE_2,
    PEI_ENABLE_2
}UART2_PE_INTERRUPT;

/*Description: Enum to hold if Transmit data register empty Interrupt is activated or not */
typedef enum
{
    TXEI_DISABLE_2,
    TXEI_ENABLE_2
}UART2_TXE_INTERRUPT;

/*Description: Enum to hold if Transmission complete Interrupt is activated or not */
typedef enum
{
    TCI_DISABLE_2,
    TCI_ENABLE_2
}UART2_TC_INTERRUPT;

/*Description: Enum to hold if Receiver data register is not empty Interrupt is activated or not */
typedef enum
{
    RXNEI_DISABLE_2,
    RXNEI_ENABLE_2
}UART2_RXNE_INTERRUPT;

/*Description: Enum to hold if : IDLE Interrupt is activated or not */
typedef enum
{
    IDLEI_DISABLE_2,
    IDLEI_ENABLE_2
}UART2_IDLE_INTERRUPT;

typedef enum
{
    INTERRUPT_2,
    POLLING_2
}UART2_Event_Type;

/* DMA Config */
typedef enum
{
  NO_DMA_2,
  DMA_TX_Enable_2,
  DMA_RX_Enable_2  
}UART_DMA_RX_EN_2;

typedef struct
{
   UART2_Event_Type Event_Type;                  /* Interrupt or Polling */
   UART2_Word_Length Word_Length;                /* 8 bits or 9 bits */
   UART2_Parity_Control Parity_Mode;             /* Disable or Enable */
   UART2_Parity Parity_Type;                     /* Even or Odd */
   UART2_StopBit Stop_Bit;                       /* 1 or 0.5 or 2 or 1.5 */
   UART2_IDLE_INTERRUPT IDLE_INTERRUPT;          /* IDLEI_DISABLE or IDLEI_ENABLE */
   UART_DMA_RX_EN_2 DMA_CONTROL;                  /* Enable or Disable the DMA */
   UART2_RXNE_INTERRUPT RXNE_INTERRUPT;          /* RXNEI_DISABLE or RXNEI_ENABLE */
   UART2_TC_INTERRUPT TC_INTERRUPT;              /* TCI_DISABLE or TCI_ENABLE */
   UART2_TXE_INTERRUPT TXE_INTERRUPT;            /* TXEI_DISABLE or TXEI_ENABLE */
   UART2_PE_INTERRUPT PE_Interrupt;              /* PEI_DISABLE or PEI_ENABLE*/
   uint32 Baud_Rate;
   uint8 Priority_Level;
}UART2_ConfigType;

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART2_init( const UART2_ConfigType * config );

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART2_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART2_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART2_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART2_receiveString(uint8 *Str); 

/* A variable to store the received data */
//extern uint8 RECEIVED_DATA ; 

#endif /* UART_H */
