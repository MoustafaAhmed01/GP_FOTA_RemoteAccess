/******************************************************************************
 *
 * Module: GPT
 *
 * File Name: GPT.h
 *
 * Description: Header file for STM32F103xx Microcontroller - GPT Driver
 *
 * Author: Esraa Ali - Shady Alaa
 ******************************************************************************/

#ifndef GPT_H
#define GPT_H
#include "Std_Types.h"
#include "Common_macros.h"
#include "stm32f103c8t6_registers.h"
#include "Timer_Cfg.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/*Clock division: (Bits 9:8 CKD[1:0])
This bit-field indicates the division ratio between the timer clock (CK_INT) frequency and the 
dead-time and sampling clock (tDTS)used by the dead-time generators and the digital filters 
(ETR, TIx)*/
typedef enum
{
	tCK_INT,tCK_INT_multible_2,tCK_INT_multible_4,Reserved
}TIMx_CR1_CKD;

/*ARPE: Auto-reload preload enable*/
typedef enum
{
	TIMx_ARR_register_is_not_buffered,TIMx_ARR_register_is_buffered
}TIMx_CR1_ARPE;

/*CMS[1:0]: Center-aligned mode selection*/
typedef enum
{
	Edge_aligned_mode,Center_aligned_mode_1,Center_aligned_mode_2,Center_aligned_mode_3    /*00: Edge-aligned mode. The counter counts up or down depending on the direction bit(DIR).
                                                                                                 01: Center-aligned mode 1. The counter counts up and down alternatively. Output compare 
                                                                                                     interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set         
                                                                                                     only when the counter is counting down.
                                                                                                 10: Center-aligned mode 2. The counter counts up and down alternatively. Output compare 
                                                                                                     interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set 
                                                                                                     only when the counter is counting up.
                                                                                                 11: Center-aligned mode 3. The counter counts up and down alternatively. Output compare 
                                                                                                     interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set 
                                                                                                     both when the counter is counting up or down.
                                                                                                 Note: It is not allowed to switch from edge-aligned mode to center-aligned mode as long as 
                                                                                                       the counter is enabled (CEN=1)*/
}TIMx_CR1_CMS;

/*DIR: Direction,This bit is read only when the timer is configured in Center-aligned mode or Encoder mode*/
typedef enum
{
	upcounter,downcounter
}TIMx_CR1_DIR;

/*OPM: One pulse mode*/
typedef enum
{
	Counter_is_not_stopped_at_UEV,Counter_stops_at_next_UEV                                /*0: Counter is not stopped at update event
                                                                                                 1: Counter stops counting at the next update event (clearing the bit CEN)*/
}TIMx_CR1_OPM;

/*URS: Update request source,This bit is set and cleared by software to select the UEV event sources.*/
typedef enum
{
	any_event,Only_counter_overflow_underflow_event                                        /*0: Any of the following events generate an update interrupt or DMA request if enabled. 
                                                                                                    These events can be: 
                                                                                                    – Counter overflow/underflow
                                                                                                    – Setting the UG bit
                                                                                                    – Update generation through the slave mode controller
                                                                                                 1: Only counter overflow/underflow generates an update interrupt or DMA request if enabled.*/
}TIMx_CR1_URS;

/*UDIS: Update disable , This bit is set and cleared by software to enable/disable UEV event generation.*/
typedef enum
{
	UEV_enabled,UEV_disabled
}TIMx_CR1_UDIS;

/*CEN: Counter enable*/
typedef enum
{
	Counter_disabled,Counter_enabled
}TIMx_CR1_CEN;

typedef enum
{
	UG_BIT,CC1G_BIT,CC2G_BIT,CC3G_BIT,CC4G_BIT
}TIMx_EGR_REG;

typedef enum
{
	no_channel,channel_1,channel_2,channel_3,channel_4
}CHANNEL_NUM;

typedef enum
{
	CC1IE_BIT=1,CC2IE_BIT=2,CC3IE_BIT=3,CC4IE_BIT=4
}DIER_CHANNEL_NUM;

typedef enum
{
	CC1IF_BIT=1,CC2IF_BIT=2,CC3IF_BIT=3,CC4IF_BIT=4
}SR_CHANNEL_NUM;

typedef enum
{
	CC1E_BIT=0,CC2E_BIT=4,CC3E_BIT=8,CC4E_BIT=12
}CCER_CHANNEL_NUM;



typedef enum
{
	NORMAL,COMPARE,PWM
}TIMx_MODE;

typedef enum
{
	NO_TIM=0,TIM_1=1,TIM_2=2,TIM_3=3,TIM_4=4,TIM_5=5,TIM_8=8
}TIM_NUM;

typedef struct
{
        TIM_NUM TIM_ID ;
        uint32 clock_frecuency;            //frequency of system
        TIMx_MODE MODE;
        CHANNEL_NUM channel_num;
        uint16 no_millisec;
	TIMx_CR1_CEN CEN;
	TIMx_CR1_UDIS UDIS;
	TIMx_CR1_URS URS;
        TIMx_CR1_OPM OPM;
        TIMx_CR1_DIR DIR;
        TIMx_CR1_CMS CMS;
        TIMx_CR1_ARPE ARPE;
        TIMx_CR1_CKD CKD;
}GPT_Configuration;


typedef struct
{
       GPT_Configuration  TIMERS_NUM[TIMERS_NUMBER];
}GPT_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
   /*
 * Description :
 * Functional responsible for Initialize the TIMER device by:
 * 1. Reset and Configure the TIMER Control Register 1.
 * 2. Setup the TIMER Reload value and Prescaler.
 * 3. Enable the timer clock.
 */
/*********************************************************************************************/
void GPT_INIT ( const GPT_ConfigType*Config_Ptr);
 /*
 * Description :
 * Functional responsible for Initialize the PWM Only:
 * 1. Reset and Configure the TIMER Control Register 1.
 * 2. Setup the TIMER Reload value and Prescaler.
 * 3. Enable the timer clock.
 * 4. Setting mode to be PWM mode. 
 */
/*********************************************************************************************/
void Gpt_PWM_Init(const GPT_ConfigType*Config_Ptr);
/*********************************************************************************************/
/*
 * Description :
 * Functional responsible for DeInitialize the TIMER device by:
 * Reset and Disable the TIMER Registers.
 */
/*********************************************************************************************/
void GPT_DeInit(uint8 TIM_X);
/*********************************************************************************************/
/* 
 *Description:
 *Function to Set DUTY CYCLE for PWM mode.
 */
/*********************************************************************************************/
void GPT_SET_DUTY_CYCLE(uint8 TIM_x,uint16 duty_cycle);
/*********************************************************************************************/
   /* 
 *Description:
 *Function to Setup the Timer call back
 */
/*********************************************************************************************/
void GPT_SetCallBack(void(*Ptr2Func)(void));
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Post build structure used with GPT_Init API */
//extern GPT_ConfigType GPT_Configuration;

#endif /* GPT_H_ */
