 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Regs.h
 *
* Description: Header file for STM32F401RCT6 Microcontroller - Port Driver Registers
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#ifndef PORT_REGS_H
#define PORT_REGS_H

#include "Std_Types.h"

/*******************************************************************************
 GPIO Registers base addresses 
*******************************************************************************/

#define GPIO_PORTA_BASE_ADDRESS                    (*((volatile uint32 *)0x40010800 ))     /*to 0x40010BFF*/
#define GPIO_PORTB_BASE_ADDRESS                    (*((volatile uint32 *)0x40010C00 ))     /*to 0x40010FFF*/
#define GPIO_PORTC_BASE_ADDRESS                    (*((volatile uint32 *)0x40011000 ))     /*to 0x400113FF*/
#define GPIO_PORTD_BASE_ADDRESS                    (*((volatile uint32 *)0x40011400 ))     /*to 0x400117FF*/
#define GPIO_PORTE_BASE_ADDRESS                    (*((volatile uint32 *)0x40011800 ))     /*to 0x40011BFF*/
#define GPIO_PORTF_BASE_ADDRESS                    (*((volatile uint32 *)0x40011C00 ))     /*to 0x40011FFF*/
#define GPIO_PORTG_BASE_ADDRESS                    (*((volatile uint32 *)0x40012000 ))     /*to 0x400123FF*/

/*******************************************************************************
 AFIO Register base addresses 
*******************************************************************************/
#define AFIO_BASE_ADDRESS                          (*((volatile uint32 *)0x40010000 ))     /*to 0x400103FF*/

/******************************************************************************* 
GPIO Registers offset addresses 
*******************************************************************************/

#define PORT_CONF_LOW_REG_OFFSET                   0x00           /*GPIOx_CRL*/
#define PORT_CONF_HIGH_REG_OFFSET                  0x04           /*GPIOx_CRH*/
#define PORT_INPUT_DATA_REG_OFFSET                 0x08           /*GPIOx_IDR*/
#define PORT_OUTPUT_DATA_REG_OFFSET                0x0C           /*GPIOx_ODR*/
#define PORT_BIT_SET_OR_RESET_REG_OFFSET           0x10           /*GPIOx_BSRR*/
#define PORT_BIT_RESET_REG_OFFSET                  0x14           /*GPIOx_BRR*/
#define PORT_CONF_LOCK_REG_OFFSET                  0x18           /*GPIOx_LCKR*/

/******************************************************************************* 
AFIO Registers offset addresses 
*******************************************************************************/

#define AF_EVENT_CTRL_REG_OFFSET                   0x00           /*AFIO_EVCR*/
#define AF_REMAP_AND_DEBUG_REG_OFFSET              0x04           /*AFIO_MAPR*/
#define AF_EXTERNAL_INTERRUPT_CFG_REG_1_OFFSET     0x08           /*AFIO_EXTICR1*/
#define AF_EXTERNAL_INTERRUPT_CFG_REG_2_OFFSET     0x0C           /*AFIO_EXTICR2*/
#define AF_EXTERNAL_INTERRUPT_CFG_REG_3_OFFSET     0x10           /*AFIO_EXTICR3*/
#define AF_EXTERNAL_INTERRUPT_CFG_REG_4_OFFSET     0x14           /*AFIO_EXTICR4*/
#define AF_REMAP_AND_DEBUG_REG_2_OFFSET            0x1C           /*AFIO_MAPR2*/

#endif /* PORT_REGS_H */