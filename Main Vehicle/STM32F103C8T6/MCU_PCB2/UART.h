/******************************************************************************
 *
 * Module: USART
 *
 * File Name: UART.h
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - UART Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/
#ifndef UART_H
#define UART_H

#include "Std_Types.h"
#include "Common_Macros.h"
#include "stm32f103c8t6_registers.h"
#include "UART_Regs.h"
#include "Port.h"

#define  USART_1_CR1_MASK               0xFFFFC80F  
   
/*Description: Enum to hold the state of the parity enabled or disabled */   
typedef enum
{
    Disable ,
    Enable
}UART_Parity_Control;

/*Description: Enum to hold the type of parity */
typedef enum
{
    Even_Parity ,
    Odd_Parity
}UART_Parity;

/*Description: Enum to hold the number of stop bits */
typedef enum
{
    One_Stop_Bit,
    Half_Stop_Bit,
    Two_Stop_Bit,
    OneAndHalf_Stop_Bit
    
}UART_StopBit;

/*Description: Enum to hold the word length */
typedef enum
{
    DATA_8_Bits ,
    DATA_9_Bits
}UART_Word_Length;

/*Description: Enum to hold if Parity Error Interrupt is activated or not */
typedef enum
{
    PEI_DISABLE,
    PEI_ENABLE
}UART_PE_INTERRUPT;

/*Description: Enum to hold if Transmit data register empty Interrupt is activated or not */
typedef enum
{
    TXEI_DISABLE,
    TXEI_ENABLE
}UART_TXE_INTERRUPT;

/*Description: Enum to hold if Transmission complete Interrupt is activated or not */
typedef enum
{
    TCI_DISABLE,
    TCI_ENABLE
}UART_TC_INTERRUPT;

/*Description: Enum to hold if Receiver data register is not empty Interrupt is activated or not */
typedef enum
{
    RXNEI_DISABLE,
    RXNEI_ENABLE
}UART_RXNE_INTERRUPT;

/*Description: Enum to hold if : IDLE Interrupt is activated or not */
typedef enum
{
    IDLEI_DISABLE,
    IDLEI_ENABLE
}UART_IDLE_INTERRUPT;

typedef enum
{
    INTERRUPT,
    POLLING
}UART_Event_Type;

typedef struct
{
   UART_Event_Type Event_Type;                  /* Interrupt or Polling */
   UART_Word_Length Word_Length;                /* 8 bits or 9 bits */
   UART_Parity_Control Parity_Mode;             /* Disable or Enable */
   UART_Parity Parity_Type;                     /* Even or Odd */
   UART_StopBit Stop_Bit;                       /* 1 or 0.5 or 2 or 1.5 */
   UART_IDLE_INTERRUPT IDLE_INTERRUPT;          /* IDLEI_DISABLE or IDLEI_ENABLE */
   UART_RXNE_INTERRUPT RXNE_INTERRUPT;          /* RXNEI_DISABLE or RXNEI_ENABLE */
   UART_TC_INTERRUPT TC_INTERRUPT;              /* TCI_DISABLE or TCI_ENABLE */
   UART_TXE_INTERRUPT TXE_INTERRUPT;            /* TXEI_DISABLE or TXEI_ENABLE */
   UART_PE_INTERRUPT PE_Interrupt;              /* PEI_DISABLE or PEI_ENABLE*/
   uint32 Baud_Rate;
   uint8 Priority_Level;
}UART_ConfigType;

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init( const UART_ConfigType * config );

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); 

/* A variable to store the received data */
//extern uint8 RECEIVED_DATA ; 

#endif /* UART_H */
