/******************************************************************************
 *
 * Module: Advanced Timer 1
 *
 * File Name: TIM1_PWM.c
 *
* Description: Source File for STM32F103C8T6 Microcontroller - Timer 1 Channel 1 ,TIM3,TIM4
 *
 * Author: Shady Alaa Eldeen Mohammed 
 ******************************************************************************/
#include "TIM8_PWM.h"
/**PWM only**/
static void (*g_Timer_Call_Back_Ptr)(void) = NULL_PTR;
void TIM1_Init( )
{
  RCC_APB2EN_REG |=(1<<11);
  TIM1_CR1_REG   &=TIM1_CR1_MASK;
  TIM1_CR2_REG   &=0xFFFF8002;
  TIM1_CCMR1_REG &=TIM1_CCMR1_MASK;   
  TIM1_CCER_REG  &=TIM1_CCER_MASK;    
  TIM1_BDTR_REG  &=TIM1_BDTR_MASK;
  TIM1_EGR_REG   &=TIM1_EGR_REG_MASK;
  TIM1_SMCR_REG  &=0xFFFF0008;
  TIM1_DIER_REG  &=0xFFFF8000;
  TIM1_CR1_REG   &=~(1<<ARPE);
  TIM1_CCMR1_REG |=(6<<OC1M) | (1<<OC1PE) | (1<<2);
  TIM1_CCER_REG  |=(1<<CC1E);
  TIM1_CNT_REG    =0;
  TIM1_PSC_REG    =71;
  TIM1_ARR_REG    =20000-1;
  TIM1_CCR1_REG  &=0xFFFF0000;
  TIM1_BDTR_REG  |=(1<<MOE);
  TIM1_CR1_REG   |=(1<<CEN);
  TIM1_EGR_REG   |=(1<<UG);
}
void TIM1_SetDuty(uint16 Duty_Cycle)
{
//  TIM1_CNT_REG   =0;
//  TIM1_Init(); 
  TIM1_CCR1_REG  =Duty_Cycle;   
}
/* Interrupt every 1 sec**/
void TIM4_Init()
{
  RCC_APB1ENR_REG |=(1<<2);
  NVIC_ISER0_REG  |=(1<<30);
  NVIC_PRI7_REG   &=~((0xF0<<(16)));
  NVIC_PRI7_REG   |= ( ( 1 << 4 ) << 16 );
  TIM4_CR1_REG &=TIM4_CR1_MASK;
  TIM4_CR1_REG |=(1<<ARPE) | (1<<URS);
  TIM4_CNT_REG  =0;
  TIM4_PSC_REG  =7199;
  TIM4_ARR_REG  =9999;
  TIM4_EGR_REG &=TIM4_EGR_REG_MASK;
  TIM4_EGR_REG |=(1<<UG);
  TIM4_DIER_REG &=0xFFFFA0A0;
  TIM4_DIER_REG |=(1<<0);
  TIM4_CR1_REG |=(1<<CEN); 
}
void TIM3_Init()
{
  RCC_APB1ENR_REG |=(1<<1);
  TIM3_CR1_REG   &=0xFFFFFC00;
  TIM3_CR2_REG   &=0xFFFFFF08;
  TIM3_CCMR1_REG &=0xFFFF0000;
  TIM3_CCMR2_REG &=0xFFFF0000; 
  TIM3_CCER_REG  &=0xFFFFCCCC;    
  TIM3_EGR_REG   &=0xFFFFFFA0;
  TIM3_SMCR_REG  &=0xFFFF0008;
  TIM3_DIER_REG  &=0xFFFF8000;
  TIM3_CR1_REG   &=~(1<<ARPE);
  TIM3_CCMR2_REG |=(6<<4) | (1<<3) | (1<<2) | (6<<12) | (1<<11) | (1<<10);
  TIM3_CCER_REG  |=(1<<8) | (1<<12);
  TIM3_CNT_REG    =0;
  TIM3_PSC_REG    =3999;
  TIM3_ARR_REG    =499;
  TIM3_CCR3_REG  &=0xFFFF0000;
  TIM3_EGR_REG   |=(1<<UG);
  TIM3_CR1_REG   |=(1<<CEN);
 
  
  
}
void TIM3_SetDuty(uint16 Duty_Cycle)
{
//  TIM3_CNT_REG   =0; 
  TIM3_CCR3_REG  =(Duty_Cycle*499)/100;
  TIM3_CCR4_REG  =(Duty_Cycle*499)/100;
}

/************************************************************************************
* Description: SysTick Timer ISR
************************************************************************************/
void Timer_Handler(void)
{
  if(BIT_IS_SET(TIM4_SR_REG,UIF))
  {
    /* Check if the Timer4_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
   CLEAR_BIT(TIM4_SR_REG,UIF);
    /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
}
}
void Timer_SetCallBack(void(*Ptr2Func)(void))
{
    g_Timer_Call_Back_Ptr = Ptr2Func;
}
