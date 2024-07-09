/******************************************************************************
 *
 * Module: USART
 *
 * File Name: UART_Regs.h
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - UART Registers Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#ifndef PORT_REGS_H
#define PORT_REGS_H

#include "Std_Types.h"

/******************************************************************************
*                        UART Registers Base Address
******************************************************************************/
#define UART_1_BASE_ADDRESS                    (*((volatile uint32 *)0x40013800 ))     /*to 0x40013BFF*/ 
#define UART_2_BASE_ADDRESS                    (*((volatile uint32 *)0x40004400 ))     /*to 0x40004BFF*/             
#define UART_3_BASE_ADDRESS                    (*((volatile uint32 *)0x40004800 ))     /*to 0x400047FF*/             
#define UART_4_BASE_ADDRESS                    (*((volatile uint32 *)0x40004C00 ))     /*to 0x40004FFF*/             
#define UART_5_BASE_ADDRESS                    (*((volatile uint32 *)0x40005000 ))     /*to 0x400053FF*/             

/******************************************************************************
*                       UART Registers Offset Address
******************************************************************************/
#define USART_SR                               0x00
#define USART_DR                               0x04
#define USART_BRR                              0x08
#define USART_CR1                              0x0C
#define USART_CR2                              0x10
#define USART_CR3                              0x14
#define USART_GTPR                             0x18

/*****************************************************************************
*                              UART 1 Registers
*****************************************************************************/
#define USART_1_SR_REG                            (*((volatile uint32 *)0x40013800 ))
#define USART_1_DR_REG                            (*((volatile uint32 *)0x40013804 ))
#define USART_1_BRR_REG                           (*((volatile uint32 *)0x40013808 ))
#define USART_1_CR1_REG                           (*((volatile uint32 *)0x4001380C ))
#define USART_1_CR2_REG                           (*((volatile uint32 *)0x40013810 ))
#define USART_1_CR3_REG                           (*((volatile uint32 *)0x40013814 ))
#define USART_1_GTPR_REG                          (*((volatile uint32 *)0x40013818 ))
/*****************************************************************************
*                              UART 2 Registers
*****************************************************************************/
#define USART_2_SR_REG                            (*((volatile uint32 *)0x40004400 ))
#define USART_2_DR_REG                            (*((volatile uint32 *)0x40004404 ))
#define USART_2_BRR_REG                           (*((volatile uint32 *)0x40004408 ))
#define USART_2_CR1_REG                           (*((volatile uint32 *)0x4000440C ))
#define USART_2_CR2_REG                           (*((volatile uint32 *)0x40004410 ))
#define USART_2_CR3_REG                           (*((volatile uint32 *)0x40004414 ))
#define USART_2_GTPR_REG                          (*((volatile uint32 *)0x40004418 ))
/*******************************************************************************
 *                   Status register (USART_SR) Bits Name                      *
 ******************************************************************************/
#define CTS                                       (9u)
#define LBD                                       (8u)
#define TXE                                       (7u)
#define TC                                        (6u)
#define RXNE                                      (5u)
#define IDLE                                      (4u)
#define ORE                                       (3u)
#define NE                                        (2u)    
#define FE                                        (1u)
#define PE                                        (0u)
  
/*******************************************************************************
 *              Control register 1 (USART_CR1) Bits Name                       *
 ******************************************************************************/
#define UE                                     (13u)
#define M                                      (12u)
#define PCE                                    (10u)
#define PS                                     (9u)
#define PEIE                                   (8u)
#define TXEIE                                  (7u)
#define TCIE                                   (6u)
#define RXNEIE                                 (5u)    
#define IDLEIE                                 (4u)
#define TE                                     (3u)
#define RE                                     (2u)
#define RWU                                    (1u)
#define SBK                                    (0u)    
   
/******************************************************************************
*              Control register 2 (USART_CR2) Bits Name                       *
******************************************************************************/
#define STOP_BITS                              (12u)

/******************************************************************************
*              Control register 3 (USART_CR3) Bits Name                       *
******************************************************************************/
#define CTSIE                                  (10u)
#define CTSE                                   (9u)
#define RTSE                                   (8u)
#define DMAT                                   (7u)
#define DMAR                                   (6u)
#define SCEN                                   (5u)
#define NACK                                   (4u)
#define HDSEL                                  (3u)    
#define IRLP                                   (2u)
#define IREN                                   (1u)
#define EIE                                    (0u)
   
/******************************************************************************
*              Baud rate register (USART_BRR) Bits Name                       *
******************************************************************************/   
#define DIV_MANTISSA                           (4u)
#define DIV_FRACTION                           (0u)
/*****************************************************************************
*                              UART MASK
*****************************************************************************/
#define  USART_1_CR1_MASK               0xFFFFC80F  
#define  USART_2_CR1_MASK               0xFFFFC80F     
   
   
#endif /* PORT_REGS_H */