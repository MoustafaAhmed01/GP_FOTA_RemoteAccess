/******************************************************************************
 *
 * Module: Advanced Timer 1
 *
 * File Name: TIM1_PWM.h
 *
* Description: Header File for STM32F103C8T6 Microcontroller - Timer 1 /3/4
 *
 * Author: Shady Alaa Eldeen Mohammed 
 ******************************************************************************/
#ifndef TIM1_H
#define TIM1_H
#include "Std_Types.h"
#include "Common_Macros.h"
#include "TIM8_Registers.h"
#include "stm32f103c8t6_registers.h"
#define TIM1_CR1_MASK     0xFFFFFC00
#define TIM1_CCMR1_MASK   0xFFFF0000
#define TIM1_CCER_MASK    0xFFFF4000
#define TIM1_BDTR_MASK    0xFFFF0000
#define TIM1_EGR_REG_MASK 0xFFFF0000
#define TIM4_CR1_MASK     0xFFFFFC00
#define TIM4_EGR_REG_MASK 0xFFFFFFA0
void TIM1_Init( );
void TIM4_Init();
void TIM1_SetDuty(uint16 Duty_Cycle);
void TIM3_Init();
void TIM3_SetDuty(uint16 Duty_Cycle);
void Timer_SetCallBack(void(*Ptr2Func)(void));
#endif