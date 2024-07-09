 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Regs.h
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - Dio Driver Registers
 *
 * Author: Moustafa Ahmed
 ******************************************************************************/

#ifndef DIO_REGS_H
#define DIO_REGS_H

#include "Std_Types.h"

#define GPIO_PORTA_INPUT_DATA_REG             (*((volatile uint32 *)0x40010808))           /*GPIOx_IDR*/
#define GPIO_PORTA_OUTPUT_DATA_REG            (*((volatile uint32 *)0x4001080C))           /*GPIOx_ODR*/

#define GPIO_PORTB_INPUT_DATA_REG             (*((volatile uint32 *)0x40010C08))           /*GPIOx_IDR*/
#define GPIO_PORTB_OUTPUT_DATA_REG            (*((volatile uint32 *)0x40010C0C))           /*GPIOx_ODR*/
                                              
#define GPIO_PORTC_INPUT_DATA_REG             (*((volatile uint32 *)0x40011008))           /*GPIOx_IDR*/
#define GPIO_PORTC_OUTPUT_DATA_REG            (*((volatile uint32 *)0x4001100C))           /*GPIOx_ODR*/
                                              
#define GPIO_PORTD_INPUT_DATA_REG             (*((volatile uint32 *)0x40011408))           /*GPIOx_IDR*/
#define GPIO_PORTD_OUTPUT_DATA_REG            (*((volatile uint32 *)0x4001140C))           /*GPIOx_ODR*/
                                              
#define GPIO_PORTE_INPUT_DATA_REG             (*((volatile uint32 *)0x40011808))           /*GPIOx_IDR*/
#define GPIO_PORTE_OUTPUT_DATA_REG            (*((volatile uint32 *)0x4001180C))           /*GPIOx_ODR*/
                                              
#define GPIO_PORTF_INPUT_DATA_REG             (*((volatile uint32 *)0x40011C08))           /*GPIOx_IDR*/
#define GPIO_PORTF_OUTPUT_DATA_REG            (*((volatile uint32 *)0x40011C0C))           /*GPIOx_ODR*/
                                              
#define GPIO_PORTG_INPUT_DATA_REG             (*((volatile uint32 *)0x40012008))           /*GPIOx_IDR*/
#define GPIO_PORTG_OUTPUT_DATA_REG            (*((volatile uint32 *)0x4001200C))           /*GPIOx_ODR*/


#endif /* DIO_REGS_H */
