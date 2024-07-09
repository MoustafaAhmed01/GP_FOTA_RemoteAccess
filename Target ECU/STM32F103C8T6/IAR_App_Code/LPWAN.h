/******************************************************************************
 *
 * Module: LPWAN
 *
 * File Name: LPWAN.h
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - LPWAN Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/
#ifndef LPWAN_H
#define LPWAN_H

#include "UART.h"
#include "Delay.h"

#define LPWAN_ID                0x90              /* ID of the LPWAN */
#define Start_Frame             0x0A            /* Start of the transmitted Frame */
#define End_Frame               0x0D            /* End of the transmited frame */          

/*
 * Description :
 * Functional responsible for Initialize the Lpwan device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void LPWAN_Init( void );
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Functional responsible for receive byte from another Lpwan device.
 */
uint8 LPWAN_RecieveFrame(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Checks the ID
 */
uint8 LPWAN_ReceiveCheck(uint8 ID);
/*-------------------------------------------------------------------*/

/*
 * Description :
 * Functional responsible for send Frame to another lpwan device.
 */
void LPWAN_SendFrame(const uint8 *Data_Frame);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Functional responsible for send frame to another Lpwan device.
 */
void LPWAN_SendByte(const uint8 data);
/*-------------------------------------------------------------------*/
#endif /* LPWAN_H */