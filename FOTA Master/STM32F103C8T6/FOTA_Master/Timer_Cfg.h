/******************************************************************************
 *
 * Module: GPT
 *
 * File Name: Timer_Cfg.h
 *
 * Description: Configuration  for STM32F103xx Microcontroller - GPT Module
 *
 * Author: Esraa Ali
 ******************************************************************************/
#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_
#include "Port.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
   /*timer 1*/
#define TIMER1_NORMAL_PRIORITY_MASK  0xFFFF00FF
#define TIMER1_NORMAL_INTERRUPT_PRIORITY  5           //DESIRED PRIORITY
#define TIMER1_NORMAL_PRIORITY_BITS_POS   8
#define TIMER1_NORMAL_SET_ENABLE_MASK 0xFDFFFFFF
#define TIMER1_NORMAL_SET_ENABLE_BIT_POS 25
#define TIMER1_COMPARE_PRIORITY_MASK  0x00FFFFFF
#define TIMER1_COMPARE_INTERRUPT_PRIORITY  5           //DESIRED PRIORITY
#define TIMER1_COMPARE_PRIORITY_BITS_POS   24
#define TIMER1_COMPARE_SET_ENABLE_MASK 0xF7FFFFFF
#define TIMER1_COMPARE_SET_ENABLE_BIT_POS 27
   /*timer 8*/
#define TIMER8_NORMAL_PRIORITY_MASK  0xFFFFFF00
#define TIMER8_NORMAL_INTERRUPT_PRIORITY  4           //DESIRED PRIORITY
#define TIMER8_NORMAL_PRIORITY_BITS_POS   0
#define TIMER8_NORMAL_SET_ENABLE_MASK 0xFFFFEFFF
#define TIMER8_NORMAL_SET_ENABLE_BIT_POS 12             //44
#define TIMER8_COMPARE_PRIORITY_MASK  0xFF00FFFF
#define TIMER8_COMPARE_INTERRUPT_PRIORITY  4           //DESIRED PRIORITY
#define TIMER8_COMPARE_PRIORITY_BITS_POS   16
#define TIMER8_COMPARE_SET_ENABLE_MASK 0xFFFFBFFF
#define TIMER8_COMPARE_SET_ENABLE_BIT_POS 14           //46
   /*timer 2*/
#define TIMER2_PRIORITY_MASK  0xFFFFFF00
#define TIMER2_INTERRUPT_PRIORITY  6           //DESIRED PRIORITY
#define TIMER2_PRIORITY_BITS_POS   0
#define TIMER2_SET_ENABLE_MASK 0xEFFFFFFF
#define TIMER2_SET_ENABLE_BIT_POS 28
   /*timer 3*/
#define TIMER3_PRIORITY_MASK  0xFFFF00FF
#define TIMER3_INTERRUPT_PRIORITY  7           //DESIRED PRIORITY
#define TIMER3_PRIORITY_BITS_POS   8
#define TIMER3_SET_ENABLE_MASK 0xDFFFFFFF
#define TIMER3_SET_ENABLE_BIT_POS 29
   /*timer 4*/
#define TIMER4_PRIORITY_MASK  0xFF00FFFF
#define TIMER4_INTERRUPT_PRIORITY  8           //DESIRED PRIORITY
#define TIMER4_PRIORITY_BITS_POS   16
#define TIMER4_SET_ENABLE_MASK 0xBFFFFFFF
#define TIMER4_SET_ENABLE_BIT_POS 30
   /*timer 5*/
#define TIMER5_PRIORITY_MASK  0xFF00FFFF
#define TIMER5_INTERRUPT_PRIORITY  9           //DESIRED PRIORITY
#define TIMER5_PRIORITY_BITS_POS   16
#define TIMER5_SET_ENABLE_MASK 0xFFFBFFFF
#define TIMER5_SET_ENABLE_BIT_POS 18               //50
   
#define UIF_BIT                 0 
#define UIE_BIT                 0 
#define MOE_BIT                 15 
#define TIMER1_ENABLE_BIT       11
#define TIMER8_ENABLE_BIT       13
#define TIMER2_ENABLE_BIT       0
#define TIMER3_ENABLE_BIT       1
#define TIMER4_ENABLE_BIT       2
#define TIMER5_ENABLE_BIT       3
#define F_PWM                   1000
#define TIMx_CCMR1_CC1_REG_MASK 0xFF80  
#define TIMx_CCMR1_CC2_REG_MASK 0x84FF  
#define TIMx_CCMR2_CC3_REG_MASK 0xFF84
#define TIMx_CCMR2_CC4_REG_MASK 0x84FF
   
#define TOGGLE                  3                                  //011
#define PWM_MODE_1              6                                  //110 
   
#define TIMERS_NUMBER           6                                

  
   /* Configuring DC_MOTOR -> Port Indicies  */
#define GPT_DCMOTOR_PORT_ID_INDEX        PORTB_PIN_1    /*TIM_3 - Channel_4*/
#define GPT_SERVO_PORT_ID_INDEX          PORTA_PIN_8   /*TIM_1 - Channel_1*/
#define GPT_FANOUT_PORT_ID_INDEX         PORTA_PIN_15  /*TIM_2 - Channel_1*/









#endif