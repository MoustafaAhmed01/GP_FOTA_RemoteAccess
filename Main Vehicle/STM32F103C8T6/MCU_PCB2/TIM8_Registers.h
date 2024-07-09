/******************************************************************************
 *
 * Module: None
 *
 * File Name: TIM1_Registers.h
 *
* Description: Header file for STM32F103C8T6 Microcontroller - Timer 1 REGISTERS
 *
 * Author: Shady Alaa Eldeen Mohammed 
 ******************************************************************************/
#ifndef TIM8_REGISTERS
#define TIM8_REGISTERS

#include "Std_Types.h"
/****************************TIM8 Registers************************************/
#define TIM_1_BASE_ADDRESS      (*((volatile uint32 *)0x40012C00))
#define TIM_4_BASE_ADDRESS      (*((volatile uint32 *)0x40000800))
#define TIM_3_BASE_ADDRESS      (*((volatile uint32 *)0x40000400))
/* TIMER Registers offset addresses */
#define RCC_APB2EN_REG          (*((volatile uint32 *)0x40021018))     
#define TIM1_ARR_REG            (*((volatile uint32 *)0x40012C2C))
#define TIM1_CR1_REG            (*((volatile uint32 *)0x40012C00))
#define TIM1_CR2_REG            (*((volatile uint32 *)0x40012C04))
#define TIM1_SMCR_REG           (*((volatile uint32 *)0x40012C08))
#define TIM1_DIER_REG           (*((volatile uint32 *)0x40012C0C))
#define TIM1_SR_REG             (*((volatile uint32 *)0x40012C10))
#define TIM1_CCER_REG           (*((volatile uint32 *)0x40012C20))
#define TIM1_CNT_REG            (*((volatile uint32 *)0x40012C24))
#define TIM1_CCR1_REG           (*((volatile uint32 *)0x40012C34))
#define TIM1_CCR2_REG           (*((volatile uint32 *)0x40012C38))
#define TIM1_CCR3_REG           (*((volatile uint32 *)0x40012C3C))
#define TIM1_CCR4_REG           (*((volatile uint32 *)0x40012C40))
#define TIM1_PSC_REG            (*((volatile uint32 *)0x40012C28))
#define TIM1_CCMR1_REG          (*((volatile uint32 *)0x40012C18))
#define TIM1_CCMR2_REG          (*((volatile uint32 *)0x40012C1C))
#define TIM1_EGR_REG            (*((volatile uint32 *)0x40012C14))
#define TIM1_BDTR_REG           (*((volatile uint32 *)0x40012C44))
/*******************************TIMER_4 Registers*************/
#define RCC_APB1ENR_REG         (*((volatile uint32 *)0x4002101C))
#define TIM4_CR1_REG            (*((volatile uint32 *)0x40000800))
#define TIM4_CR2_REG            (*((volatile uint32 *)0x40000804))
#define TIM4_SMCR_REG           (*((volatile uint32 *)0x40000808))
#define TIM4_DIER_REG           (*((volatile uint32 *)0x4000080C))
#define TIM4_SR_REG             (*((volatile uint32 *)0x40000810))
#define TIM4_EGR_REG            (*((volatile uint32 *)0x40000814))
#define TIM4_CCMR1_REG          (*((volatile uint32 *)0x40000818))
#define TIM4_CCMR2_REG          (*((volatile uint32 *)0x4000081C))
#define TIM4_CCER_REG           (*((volatile uint32 *)0x40000820))
#define TIM4_CNT_REG            (*((volatile uint32 *)0x40000824))
#define TIM4_PSC_REG            (*((volatile uint32 *)0x40000828))
#define TIM4_ARR_REG            (*((volatile uint32 *)0x4000082C))
#define TIM4_CCR1_REG           (*((volatile uint32 *)0x40000834))
#define TIM4_CCR2_REG           (*((volatile uint32 *)0x40000838))
#define TIM4_CCR3_REG           (*((volatile uint32 *)0x4000083C))
#define TIM4_CCR4_REG           (*((volatile uint32 *)0x40012C40))

/*TIM3*/
#define TIM3_CR1_REG            (*((volatile uint32 *)0x40000400))
#define TIM3_CR2_REG            (*((volatile uint32 *)0x40000404))
#define TIM3_SMCR_REG           (*((volatile uint32 *)0x40000408))
#define TIM3_DIER_REG           (*((volatile uint32 *)0x4000040C))
#define TIM3_SR_REG             (*((volatile uint32 *)0x40000410))
#define TIM3_EGR_REG            (*((volatile uint32 *)0x40000414))
#define TIM3_CCMR1_REG          (*((volatile uint32 *)0x40000418))
#define TIM3_CCMR2_REG          (*((volatile uint32 *)0x4000041C))
#define TIM3_CCER_REG           (*((volatile uint32 *)0x40000420))
#define TIM3_CNT_REG            (*((volatile uint32 *)0x40000424))
#define TIM3_PSC_REG            (*((volatile uint32 *)0x40000428))
#define TIM3_ARR_REG            (*((volatile uint32 *)0x4000042C))
#define TIM3_CCR1_REG           (*((volatile uint32 *)0x40000434))
#define TIM3_CCR2_REG           (*((volatile uint32 *)0x40000438))
#define TIM3_CCR3_REG           (*((volatile uint32 *)0x4000043C))
#define TIM3_CCR4_REG           (*((volatile uint32 *)0x40000440))



/*********************************Bits*****************************************/
#define ARPE                           7
#define CMS                            5
#define DIR                            4
#define CEN                            0
#define OC1M                           4
#define OC1PE                          3
#define CC1S                           0
#define CC1E                           0
#define CC1P                           1
#define MOE                            15
#define URS                            2
#define UG                             0
#define UIF                            0
#endif