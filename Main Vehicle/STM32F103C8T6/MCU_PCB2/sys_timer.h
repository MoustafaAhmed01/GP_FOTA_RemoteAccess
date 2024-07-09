/******************************************************************************
 *
 * Module: SYS_TIMER
 *
 * File Name: SYS_TIMER.h
 *
 * Description: Header file for STM32F103xx Microcontroller - SYS_TIMER Driver
 *
 * Author: Esraa Ali
 ******************************************************************************/

#ifndef SYS_TIMER_H
#define SYS_TIMER_H

#include "Std_Types.h"
#include "stm32f103c8t6_registers.h"
/*
#define TIMER1_PRIORITY_MASK  0xFF00FFFF
#define TIMER1_INTERRUPT_PRIORITY  4           //DESIRED PRIORITY
#define TIMER1_PRIORITY_BITS_POS   16
#define TIMER1_SET_ENABLE_MASK 0xFFFFFFBF
#define TIMER1_SET_ENABLE_BIT_POS 6
*/
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/*Clock source selection*/
typedef enum
{
	AHB_8,Processor_clock_AHB
}SYS_TIMER_ClockSource;

/*SysTick exception request enable
not_assert_SysTick_request (0): Counting down to zero does not assert the SysTick exception request
assert_SysTick_request(1): Counting down to zero assert the SysTick exception request*/
typedef enum
{
	not_assert_SysTick_request,assert_SysTick_request
}SYS_TIMER_Tickint;
/* Counter enable*/
typedef enum
{
	disable,enabled
}SYS_TIMER_Enable;

typedef struct
{        
	SYS_TIMER_ClockSource clocksource;
	SYS_TIMER_Tickint tickint;
	SYS_TIMER_Enable enable;
}SYS_TIMER_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the SysTick device by:
 * 1. Reset and Configure the SysTick Control Register.
 * 2. Setup the SysTick Reload value.
 * 3. Enable the SysTick.
 */
void SysTick_Init(const SYS_TIMER_ConfigType*Config_Ptr,uint32 Counter_Value);
/*
 * Description :
 * Functional responsible for DeInitialize the SysTick device by:
 * Reset and Disable the SysTick Registers.
 */
void SysTick_DeInit(void);
/* 
Description:
Function to Setup the SysTick Timer call back
*/
void SysTick_SetCallBack(void(*Ptr2Func)(void));
#endif /* SYS_TIMER_H_ */