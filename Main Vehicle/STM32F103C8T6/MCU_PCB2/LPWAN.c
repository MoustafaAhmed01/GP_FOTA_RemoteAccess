/******************************************************************************
 *
 * Module: LPWAN
 *
 * File Name: LPWAN.c
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - LPWAN Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#include "LPWAN.h"

/*
 * Description :
 * Functional responsible for Initialize the Lpwan device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits in UART.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void LPWAN_Init( void )
{
  /* Initializing UART as Interrupt
  *
  * UART_RECEIVE_INT : YES
  * UART_TRANSMIT_INT : NO
  * UART_EMPTY_INT : No
  * UART_RECEIVER : Yes
  * UART_TRANSMITTER : Yes
  * UART_CharSize : 8-bit
  * UART_MODE_SELECT : A-sync
  * UART_PARITY_SELECT : No
  * UART_STOP_BIT_SELECT : 1-bit
  * UART_CLOCK_POLARITY : A-sync Rising
  * baud_rate : 115200
  *
  */
  UART_ConfigType config2 = { INTERRUPT , DATA_8_Bits , Disable , Even_Parity , One_Stop_Bit , IDLEI_ENABLE , RXNEI_DISABLE, TCI_DISABLE ,TXEI_DISABLE , PEI_DISABLE , 115200 , 3};
  UART_init(&config2);
}

STATIC void USART_INTERRUPT_ENABLE(void)
{
    SET_BIT( USART_1_CR1_REG , IDLEIE );
}

STATIC void USART_INTERRUPT_DISABLE(void)
{
    CLEAR_BIT( USART_1_CR1_REG , IDLEIE );
}

/*
 * Description :
 * Functional responsible for send frame to another lpwan device.
 */
void LPWAN_SendFrame(const uint8* data)
{
  uint8 i ;
  
  /*- Disable the interrupt for the usart so that lpwan can send the frame without any interrupt -*/
  USART_INTERRUPT_DISABLE();
 // Delay_MS(1000);
  
  /*- Start the frame by sending a start byte of 0x0A which is in the internal configuration of the LPWAN MCU -*/
  UART_sendByte(Start_Frame);
  
  /*- Send the ID of the LPWAN to make sure that you are talking to the desired reciever -*/
  UART_sendByte(LPWAN_ID);
  
  /*- Send the required data  -*/
 
  UART_sendString(data);
  
    
   /*- End the Frame by the End byte -*/ 
  UART_sendByte(End_Frame);
  
  /*- Last step is to Enable again the USART interrupt  -*/
  USART_INTERRUPT_ENABLE();
}

/*
 * Description :
 * Checks the ID
 */
uint8 LPWAN_ReceiveCheck(uint8 ID)
{
  if(ID == LPWAN_ID)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}