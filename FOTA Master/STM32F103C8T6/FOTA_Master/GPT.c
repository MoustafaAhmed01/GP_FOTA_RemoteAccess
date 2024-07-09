/******************************************************************************
 *
 * Module: GPT
 *
 * File Name: GPT.c
 *
 * Description: Source file for STM32F103xx Microcontroller - GPT Driver
 *
 * Author: Esraa Ali - Shady Alaa
 ******************************************************************************/
#include "GPT.h"
/************************************************************************************
* Privelage access for timer irqs.
************************************************************************************/
/* Disable interrupts (CPSID instruction) */   
/*void __disable_irq(void) 
{
    __asm volatile ("cpsid i"); 
}
*/
/* Enable interrupts (CPSIE instruction) */
/*void __enable_irq(void) 
{
    __asm volatile ("cpsie i"); 
}   
*/

/* Global pointer to function used to point upper layer functions
 * to be used in Call Back */
static void (*g_Timer_Call_Back_Ptr)(void) = NULL_PTR;
volatile uint32 * TIMER_Ptr = NULL_PTR; /* point to the required GPT Registers base address */
volatile uint32 * PWM_Ptr_TIM[6] = {NULL_PTR}; /* point to the required PWM Registers base address */
volatile uint8 Flag_BIT=0;
uint16 autoReload_TIM[6]={0};               /*stores autoreload values for each Timer*/
uint8 channel_TIM[6] ={0};                 /*stores Channel used for each timer*/ 
/************************************************************************************
* Description: Timer ISR
************************************************************************************/
void Timer1_Normal_Handler(void)
{
   if (BIT_IS_SET(TIM1_SR_REG,UIF_BIT))
   {
    /* Check if the Timer_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    CLEAR_BIT(TIM1_SR_REG,UIF_BIT);
    /* WE need to clear the trigger flag (COUNT) bit ... it cleared  by the SW */
   }
}
void Timer1_Compare_Handler(void)
{
   if (BIT_IS_SET(TIM1_SR_REG,Flag_BIT))
   {
    /* Check if the Timer_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    CLEAR_BIT(TIM1_SR_REG,Flag_BIT);
    /* WE need to clear the trigger flag (COUNT) bit ... it cleared  by the SW */
   }
}
void Timer8_Normal_Handler(void)
{
   if (BIT_IS_SET(TIM8_SR_REG,UIF_BIT))
   {
    /* Check if the Timer_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    CLEAR_BIT(TIM8_SR_REG,UIF_BIT);
    /* WE need to clear the trigger flag (COUNT) bit ... it cleared  by the SW */
   }
}
void Timer8_Compare_Handler(void)
{
   if (BIT_IS_SET(TIM8_SR_REG,Flag_BIT))
   {
    /* Check if the Timer_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    CLEAR_BIT(TIM8_SR_REG,Flag_BIT);
    /* WE need to clear the trigger flag (COUNT) bit ... it cleared  by the SW */
   }
}
void Timer2_Handler(void)
{
   if (BIT_IS_SET(TIM2_SR_REG,Flag_BIT))
   {
    /* Check if the Timer_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    CLEAR_BIT(TIM2_SR_REG,Flag_BIT);
    /* WE need to clear the trigger flag (COUNT) bit ... it cleared  by the SW */
   }
}
void Timer3_Handler(void)
{
   if (BIT_IS_SET(TIM3_SR_REG,Flag_BIT))
   {
    /* Check if the Timer_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    CLEAR_BIT(TIM3_SR_REG,Flag_BIT);
    /* WE need to clear the trigger flag (COUNT) bit ... it cleared  by the SW */
   }
}
void Timer4_Handler(void)
{
   if (BIT_IS_SET(TIM4_SR_REG,Flag_BIT))
   {
    /* Check if the Timer_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    CLEAR_BIT(TIM4_SR_REG,Flag_BIT);
    /* WE need to clear the trigger flag (COUNT) bit ... it cleared  by the SW */
   }
}
void Timer5_Handler(void)
{
   if (BIT_IS_SET(TIM5_SR_REG,Flag_BIT))
   {
    /* Check if the Timer_setCallBack is already called */
    if(g_Timer_Call_Back_Ptr != NULL_PTR)
    {
        (*g_Timer_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    CLEAR_BIT(TIM5_SR_REG,Flag_BIT);
    /* WE need to clear the trigger flag (COUNT) bit ... it cleared  by the SW */
   }
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
   /*
 * Description :
 * Functional responsible for Initialize the TIMER device by:
 * 1. Reset and Configure the TIMER Control Register 1.
 * 2. Setup the TIMER Reload value and Prescaler.
 * 3. Enable the timer clock.
 * 4. CONFIGURE CCMRX REGISTER
     Bits 1:0 CC1S: Capture/Compare 1 selection
     00: CC1 channel is configured as output
     Bit 3 OC1PE: Output compare 1 preload enable
     Bits 6:4 OC1M: Output compare 1 mode
     011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1
     110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 
     else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as 
     TIMx_CNT>TIMx_CCR1 else active (OC1REF=1).*/
/*********************************************************************************************/
void GPT_INIT ( const GPT_ConfigType*Config_Ptr)
{
  for (uint8 i=0;i<TIMERS_NUMBER;i++ )
  {
    if (Config_Ptr->TIMERS_NUM[i].TIM_ID==NO_TIM)
    {
      /*Do Nothing*/
    }
    else
    {
     if(Config_Ptr->TIMERS_NUM[i].MODE!=PWM)
     {
        switch(Config_Ptr->TIMERS_NUM[i].TIM_ID)
    {
        case  1: TIMER_Ptr = (volatile uint32 *)TIM_1_BASE_ADDRESS; /* TIMER1 Base Address */
                 SET_BIT(RCC_APB2ENR,TIMER1_ENABLE_BIT);                                                       /*Timer1 clock enable */
		 break;
        case  2: TIMER_Ptr = (volatile uint32 *)TIM_2_BASE_ADDRESS; /* TIMER2 Base Address */
                 SET_BIT(RCC_APB1ENR,TIMER2_ENABLE_BIT);                                                       /*Timer2 clock enable */
                 /* Assign priority level to the TIMER2 Interrupt And Enable It (35 IN VECTOR TABLE)*/
                 NVIC_PRI7_REG= (NVIC_PRI7_REG &TIMER2_PRIORITY_MASK) | (TIMER2_INTERRUPT_PRIORITY<<TIMER2_PRIORITY_BITS_POS);
                 NVIC_ISER0_REG=(NVIC_ISER0_REG&TIMER2_SET_ENABLE_MASK)|(1<<TIMER2_SET_ENABLE_BIT_POS);
                 break;
        case  3: TIMER_Ptr = (volatile uint32 *)TIM_3_BASE_ADDRESS; /* TIMER3 Base Address */
                 SET_BIT(RCC_APB1ENR,TIMER3_ENABLE_BIT);                                                       /*Timer3 clock enable */
                 /* Assign priority level to the TIMER2 Interrupt And Enable It (36 IN VECTOR TABLE)*/
                 NVIC_PRI7_REG= (NVIC_PRI7_REG &TIMER3_PRIORITY_MASK) | (TIMER3_INTERRUPT_PRIORITY<<TIMER3_PRIORITY_BITS_POS);
                 NVIC_ISER0_REG=(NVIC_ISER0_REG&TIMER3_SET_ENABLE_MASK)|(1<<TIMER3_SET_ENABLE_BIT_POS);
                 break;
        case  4: TIMER_Ptr = (volatile uint32 *)TIM_4_BASE_ADDRESS; /* TIMER4 Base Address */
                 SET_BIT(RCC_APB1ENR,TIMER4_ENABLE_BIT);                                                       /*Timer4 clock enable */
                 /* Assign priority level to the TIMER2 Interrupt And Enable It (37 IN VECTOR TABLE)*/
                 NVIC_PRI7_REG= (NVIC_PRI7_REG &TIMER4_PRIORITY_MASK) | (TIMER4_INTERRUPT_PRIORITY<<TIMER4_PRIORITY_BITS_POS);
                 NVIC_ISER0_REG=(NVIC_ISER0_REG&TIMER4_SET_ENABLE_MASK)|(1<<TIMER4_SET_ENABLE_BIT_POS);
                 break;
        case  5: TIMER_Ptr = (volatile uint32 *)TIM_5_BASE_ADDRESS; /* TIMER5 Base Address */
                 SET_BIT(RCC_APB1ENR,TIMER5_ENABLE_BIT);                                                       /*Timer5 clock enable */
                 /* Assign priority level to the TIMER2 Interrupt And Enable It (57 IN VECTOR TABLE)*/
                 NVIC_PRI12_REG= (NVIC_PRI12_REG &TIMER5_PRIORITY_MASK) | (TIMER5_INTERRUPT_PRIORITY<<TIMER5_PRIORITY_BITS_POS);
                 NVIC_ISER1_REG=(NVIC_ISER1_REG&TIMER5_SET_ENABLE_MASK)|(1<<TIMER5_SET_ENABLE_BIT_POS);
                 break;
	case  8: TIMER_Ptr = (volatile uint32 *)TIM_8_BASE_ADDRESS; /* TIMER8 Base Address */
                 SET_BIT(RCC_APB2ENR,TIMER8_ENABLE_BIT);                                                       /*Timer8 clock enable */
		 break;
    
      }
      
       if (Config_Ptr->TIMERS_NUM[i].MODE==COMPARE)                                                                              /*compare mode*/
      {
        if (Config_Ptr->TIMERS_NUM[i].TIM_ID==TIM_1)
        {
          /* Assign priority level to the TIMER1 Interrupt And Enable It (34 IN VECTOR TABLE)*/
                 NVIC_PRI6_REG= (NVIC_PRI6_REG &TIMER1_COMPARE_PRIORITY_MASK) | (TIMER1_COMPARE_INTERRUPT_PRIORITY<<TIMER1_COMPARE_PRIORITY_BITS_POS);
                 NVIC_ISER0_REG=(NVIC_ISER0_REG&TIMER1_COMPARE_SET_ENABLE_MASK)|(1<<TIMER1_COMPARE_SET_ENABLE_BIT_POS);
        }
        else if (Config_Ptr->TIMERS_NUM[i].TIM_ID==TIM_8)
        {
          /* Assign priority level to the TIMER1 Interrupt And Enable It (53 IN VECTOR TABLE)*/
                 NVIC_PRI11_REG= (NVIC_PRI11_REG &TIMER8_COMPARE_PRIORITY_MASK) | (TIMER8_COMPARE_INTERRUPT_PRIORITY<<TIMER8_COMPARE_PRIORITY_BITS_POS);
                 NVIC_ISER1_REG=(NVIC_ISER1_REG&TIMER8_COMPARE_SET_ENABLE_MASK)|(1<<TIMER8_COMPARE_SET_ENABLE_BIT_POS);
        }
        uint16 prescaler = ((Config_Ptr->TIMERS_NUM[i].clock_frecuency) / 1000) - 1;                                    /*1 kHz frequency (1 millisecond )*/
      *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_PSC_REG_OFFSET)=prescaler;                              /*Set the prescaler value*/
       uint16 COMPARE_VALUE = (((Config_Ptr->TIMERS_NUM[i].clock_frecuency)*(Config_Ptr->TIMERS_NUM[i].no_millisec)) / 1000);       /*Set the compare value*/               
      *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CNT_REG_OFFSET) =0;                                                                                  /*CLEAR COUNTER REGISTER*/ 
  switch(Config_Ptr->TIMERS_NUM[i].channel_num)
  {
   case 1: SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_DIER_REG_OFFSET),CC1IE_BIT);/*CC1IE_BIT: Capture/Compare 1 interrupt enable*/ 
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_SR_REG_OFFSET),CC1IF_BIT);/* Capture/compare 1 interrupt flag :CLEAR FLAG*/
           *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCR1_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/ 
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCER_REG_OFFSET),CC1E_BIT); /*Capture/Compare 1 output enable */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_EGR_REG_OFFSET),CC1G_BIT);    /*event generation*/
           *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCMR1_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCMR1_REG_OFFSET) & TIMx_CCMR1_CC1_REG_MASK) | (TOGGLE<<4) ;
           Flag_BIT=CC1IF_BIT;
           break;
   case 2: SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_DIER_REG_OFFSET),CC2IE_BIT);/*CC1IE_BIT: Capture/Compare 2 interrupt enable*/ 
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_SR_REG_OFFSET),CC2IF_BIT);/* Capture/compare 2 interrupt flag :CLEAR FLAG*/
           *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCR2_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCER_REG_OFFSET),CC2E_BIT); /*Capture/Compare 1 output enable */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_EGR_REG_OFFSET),CC2G_BIT);    /*event generation*/
           *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCMR1_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCMR1_REG_OFFSET) & TIMx_CCMR1_CC2_REG_MASK) | (TOGGLE<<12) ; 
           Flag_BIT=CC2IF_BIT;
           break;   
   case 3: SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_DIER_REG_OFFSET),CC3IE_BIT);/*CC1IE_BIT: Capture/Compare 3 interrupt enable*/
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_SR_REG_OFFSET),CC3IF_BIT);/* Capture/compare 3 interrupt flag :CLEAR FLAG*/
           *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCR3_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/ 
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCER_REG_OFFSET),CC3E_BIT); /*Capture/Compare 1 output enable */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_EGR_REG_OFFSET),CC3G_BIT);    /*event generation*/
           *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCMR2_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCMR2_REG_OFFSET) & TIMx_CCMR2_CC3_REG_MASK) | (TOGGLE<<4) ;
           Flag_BIT=CC3IF_BIT;
           break;
   case 4: SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_DIER_REG_OFFSET),CC4IE_BIT);/*CC1IE_BIT: Capture/Compare 4 interrupt enable*/ 
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_SR_REG_OFFSET),CC4IF_BIT);/* Capture/compare 3 interrupt flag :CLEAR FLAG*/
           *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCR4_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/ 
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCER_REG_OFFSET),CC4E_BIT); /*Capture/Compare 1 output enable */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_EGR_REG_OFFSET),CC4G_BIT);    /*event generation*/
           *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCMR2_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CCMR2_REG_OFFSET) & TIMx_CCMR2_CC4_REG_MASK) | (TOGGLE<<12) ; 
           Flag_BIT=CC4IF_BIT;
           break;
  }
                                                                                              
   *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CR1_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CR1_REG_OFFSET) & 0xFC00) | (Config_Ptr->TIMERS_NUM[i].CEN <<0) | (Config_Ptr->TIMERS_NUM[i].UDIS <<1) | (Config_Ptr->TIMERS_NUM[i].URS <<2) | (Config_Ptr->TIMERS_NUM[i].OPM <<3) | (Config_Ptr->TIMERS_NUM[i].DIR <<4) | (Config_Ptr->TIMERS_NUM[i].CMS <<5) | (Config_Ptr->TIMERS_NUM[i].ARPE <<7) | (Config_Ptr->TIMERS_NUM[i].CKD <<8);  // IT IS EQUIVALENT TO 0x0081
      }
  else if ( Config_Ptr->TIMERS_NUM[i].MODE==NORMAL)                                                                        /*normal mode*/
  {
    if (Config_Ptr->TIMERS_NUM[i].TIM_ID==TIM_1)
        {
          /* Assign priority level to the TIMER1 Interrupt And Enable It (32 IN VECTOR TABLE)*/
                 NVIC_PRI6_REG= (NVIC_PRI6_REG &TIMER1_NORMAL_PRIORITY_MASK) | (TIMER1_NORMAL_INTERRUPT_PRIORITY<<TIMER1_NORMAL_PRIORITY_BITS_POS);
                 NVIC_ISER0_REG=(NVIC_ISER0_REG&TIMER1_NORMAL_SET_ENABLE_MASK)|(1<<TIMER1_NORMAL_SET_ENABLE_BIT_POS);
        }
   else if (Config_Ptr->TIMERS_NUM[i].TIM_ID==TIM_8)
        {
           /* Assign priority level to the TIMER1 Interrupt And Enable It (51 IN VECTOR TABLE)*/
                 NVIC_PRI11_REG= (NVIC_PRI11_REG &TIMER8_NORMAL_PRIORITY_MASK) | (TIMER8_NORMAL_INTERRUPT_PRIORITY<<TIMER8_NORMAL_PRIORITY_BITS_POS);
                 NVIC_ISER1_REG=(NVIC_ISER1_REG&TIMER8_NORMAL_SET_ENABLE_MASK)|(1<<TIMER8_NORMAL_SET_ENABLE_BIT_POS);
        }
    uint16 prescaler = ((Config_Ptr->TIMERS_NUM[i].clock_frecuency) / 1000) - 1;                                    /*1 kHz frequency (1 millisecond )*/
   uint16 autoReload = ((Config_Ptr->TIMERS_NUM[i].clock_frecuency)/ (prescaler + 1)) * (Config_Ptr->TIMERS_NUM[i].no_millisec) / 1000 - 1;
   *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_PSC_REG_OFFSET)  =prescaler;                                                                         /*Set the prescaler value*/
   *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_ARR_REG_OFFSET) =autoReload;                                                                         /*Set the autoreload value to the desired delay in milliseconds (1 SEC =1000MilliSEC)*/
   *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CNT_REG_OFFSET) =0;                                                                                  /*CLEAR COUNTER REGISTER*/
   SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_EGR_REG_OFFSET),UG_BIT);                                                                     /*event generation*/
   CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_SR_REG_OFFSET),UIF_BIT);                                                                   /*  Update interrupt flag :CLEAR FLAG*/
   SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_DIER_REG_OFFSET),UIE_BIT);                                                                   /*UIE_BIT: Update interrupt enable*/                           
   SET_BIT(*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_BDTR_REG_OFFSET),MOE_BIT);
   *(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CR1_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)TIMER_Ptr + TIMx_CR1_REG_OFFSET) & 0xFC00) | (Config_Ptr->TIMERS_NUM[i].CEN <<0) | (Config_Ptr->TIMERS_NUM[i].UDIS <<1) | (Config_Ptr->TIMERS_NUM[i].URS <<2) | (Config_Ptr->TIMERS_NUM[i].OPM <<3) | (Config_Ptr->TIMERS_NUM[i].DIR <<4) | (Config_Ptr->TIMERS_NUM[i].CMS <<5) | (Config_Ptr->TIMERS_NUM[i].ARPE <<7) | (Config_Ptr->TIMERS_NUM[i].CKD <<8);  // IT IS EQUIVALENT TO 0x0081
  }           
    }
    
     else  if(Config_Ptr->TIMERS_NUM[i].MODE==PWM)                                                                               /*PWM MODE*/
  {
   // Port_SetPinDirection( GPT_DCMOTOR_PORT_ID_INDEX, PORT_PIN_OUT,PIN_PUSH_PULL,Default);                          /*INITIALIZE PWM PIN DCMOTOR */
   // Port_SetPinMode( GPT_DCMOTOR_PORT_ID_INDEX, PORT_PIN_FUNC_ALT_PWM);
   // Port_SetPinDirection( GPT_SERVO_PORT_ID_INDEX,PORT_PIN_OUT,PIN_PUSH_PULL,Default);                          /*INITIALIZE PWM PIN SERVO */
   // Port_SetPinMode( GPT_SERVO_PORT_ID_INDEX, PORT_PIN_FUNC_ALT_PWM);
   // Port_SetPinDirection( GPT_FANOUT_PORT_ID_INDEX, PORT_PIN_OUT,PIN_PUSH_PULL,Default);                          /*INITIALIZE PWM PIN FANOUT */
    //Port_SetPinMode(GPT_FANOUT_PORT_ID_INDEX,PORT_PIN_FUNC_ALT_PWM);
    
     volatile uint32 * PWM_Ptr = NULL_PTR;                                                        /* point to the required PWM Registers base address */
     uint16 prescaler = ((Config_Ptr->TIMERS_NUM[i].clock_frecuency) /F_PWM) - 1;                                     /*1 kHz frequency (1 millisecond )*/ 
     uint16 autoReload =((Config_Ptr->TIMERS_NUM[i].clock_frecuency)/ ((prescaler + 1)*F_PWM)) - 1;
     switch (Config_Ptr->TIMERS_NUM[i].TIM_ID)
  {
   case 1: SET_BIT(RCC_APB2ENR,TIMER1_ENABLE_BIT);                                                       /*Timer1 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_1_BASE_ADDRESS;                                                /* TIMER1 Base Address */
           PWM_Ptr_TIM[0]=PWM_Ptr;
           channel_TIM[0]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[0]=autoReload;
           break;
  case 2:  SET_BIT(RCC_APB1ENR,TIMER2_ENABLE_BIT);                                                       /*Timer2 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_2_BASE_ADDRESS;                                                /* TIMER2 Base Address */
           PWM_Ptr_TIM[1]=PWM_Ptr;
           channel_TIM[1]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[1]=autoReload;
           break;
  case 3: SET_BIT(RCC_APB1ENR,TIMER3_ENABLE_BIT);                                                       /*Timer3 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_3_BASE_ADDRESS;                                                /* TIMER3 Base Address */
           PWM_Ptr_TIM[2]=PWM_Ptr;
           channel_TIM[2]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[2]=autoReload;
           break;
  case 4: SET_BIT(RCC_APB1ENR,TIMER4_ENABLE_BIT);                                                       /*Timer4 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_4_BASE_ADDRESS;                                                /* TIMER4 Base Address */
           PWM_Ptr_TIM[3]=PWM_Ptr;
           channel_TIM[3]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[3]=autoReload;
           break;
  case 5: SET_BIT(RCC_APB1ENR,TIMER5_ENABLE_BIT);                                                       /*Timer5 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_5_BASE_ADDRESS;                                                /* TIMER5 Base Address */
           PWM_Ptr_TIM[4]=PWM_Ptr;
           channel_TIM[4]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[4]=autoReload;
           break;
  case 8: SET_BIT(RCC_APB2ENR,TIMER8_ENABLE_BIT);                                                       /*Timer8 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_8_BASE_ADDRESS;                                                /* TIMER8 Base Address */
           PWM_Ptr_TIM[5]=PWM_Ptr;
           channel_TIM[5]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[5]=autoReload;
           break;
  }
  
   *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CNT_REG_OFFSET) =0; 
  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_BDTR_REG_OFFSET),MOE_BIT); /*Setting MOE bit to allow updating CC1E bit*/
   *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_PSC_REG_OFFSET) = prescaler;           /*Set the prescaler value*/
   *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_ARR_REG_OFFSET) = autoReload;         /*Set the autoreload value to the desired delay in milliseconds (1 SEC =1000MilliSEC)*/
   uint16 COMPARE_VALUE = ((autoReload+1) * 0) / 100;                                        /*Calculate the CCR value for the desired duty cycle*/
   
  switch(Config_Ptr->TIMERS_NUM[i].channel_num)
  {
   case 1: //SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_DIER_REG_OFFSET),CC1IE_BIT);/*CC1IE_BIT: Capture/Compare 1 interrupt enable*/
           *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR1_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/ 
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),CC1E_BIT); /*Capture/Compare 1 output enable */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_EGR_REG_OFFSET),CC1G_BIT);    /*event generation*/
           *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET) & TIMx_CCMR1_CC1_REG_MASK) | (PWM_MODE_1<<4) |(1<<2) ;
           break;
   case 2: //SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_DIER_REG_OFFSET),CC2IE_BIT);/*CC1IE_BIT: Capture/Compare 2 interrupt enable*/ 
           *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR2_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/       
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),CC2E_BIT); /*Capture/Compare 1 output enable */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_EGR_REG_OFFSET),CC2G_BIT);    /*event generation*/
           *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET) & TIMx_CCMR1_CC2_REG_MASK) | (PWM_MODE_1<<12) ;
           break;   
   case 3: //SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_DIER_REG_OFFSET),CC3IE_BIT);/*CC1IE_BIT: Capture/Compare 3 interrupt enable*/
           *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR3_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/ 
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),CC3E_BIT); /*Capture/Compare 1 output enable */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_EGR_REG_OFFSET),CC3G_BIT);    /*event generation*/
           *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET) & TIMx_CCMR2_CC3_REG_MASK) | (PWM_MODE_1<<4) ;
          break;
   case 4: //SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_DIER_REG_OFFSET),CC4IE_BIT);/*CC1IE_BIT: Capture/Compare 4 interrupt enable*/ 
           *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR4_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),CC4E_BIT); /*Capture/Compare 1 output enable */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_EGR_REG_OFFSET),CC4G_BIT);    /*event generation*/
           *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET) & TIMx_CCMR2_CC4_REG_MASK) | (PWM_MODE_1<<12) ;
           break;
  }
   *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CR1_REG_OFFSET)= (*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CR1_REG_OFFSET)& 0xFC00) | (Config_Ptr->TIMERS_NUM[i].CEN <<0) | (Config_Ptr->TIMERS_NUM[i].UDIS <<1) | (Config_Ptr->TIMERS_NUM[i].URS <<2) | (Config_Ptr->TIMERS_NUM[i].OPM <<3) | (Config_Ptr->TIMERS_NUM[i].DIR <<4) | (Config_Ptr->TIMERS_NUM[i].CMS<<5) | (Config_Ptr->TIMERS_NUM[i].ARPE <<7) | (Config_Ptr->TIMERS_NUM[i].CKD <<8);  // IT IS EQUIVALENT TO 0x0081
    } 
}
}
}
void Gpt_PWM_Init(const GPT_ConfigType*Config_Ptr)
{
  for (uint8 i=0;i<TIMERS_NUMBER;i++ )
  {
    if (Config_Ptr->TIMERS_NUM[i].TIM_ID==NO_TIM)
    {
      /*Do Nothing*/
    }
    else
    {
      volatile uint32 * PWM_Ptr = NULL_PTR;                                                        /* point to the required PWM Registers base address */
  //   uint16 prescaler = ((Config_Ptr->TIMERS_NUM[i].clock_frecuency) /F_PWM) - 1;                                     /*1 kHz frequency (1 millisecond )*/ 
    uint16 prescaler;
    uint16 autoReload;
    //  F_PWM=((Config_Ptr->TIMERS_NUM[i].clock_frecuency)/(autoReload+1)*(prescaler+1));
    prescaler=(uint32)((Config_Ptr->TIMERS_NUM[i].clock_frecuency)/(65536)*F_PWM);
    
    autoReload =(uint32)((Config_Ptr->TIMERS_NUM[i].clock_frecuency)/ ((prescaler + 1)*F_PWM)) - 1;
     switch (Config_Ptr->TIMERS_NUM[i].TIM_ID)
     {
   case 1: SET_BIT(RCC_APB2ENR,TIMER1_ENABLE_BIT);                                                       /*Timer1 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_1_BASE_ADDRESS;                                                /* TIMER1 Base Address */
           PWM_Ptr_TIM[0]=PWM_Ptr;
           channel_TIM[0]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[0]=autoReload;
           break;
  case 2:  SET_BIT(RCC_APB1ENR,TIMER2_ENABLE_BIT);                                                       /*Timer2 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_2_BASE_ADDRESS;                                                /* TIMER2 Base Address */
           PWM_Ptr_TIM[1]=PWM_Ptr;
           channel_TIM[1]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[1]=autoReload;
           break;
  case 3:  SET_BIT(RCC_APB1ENR,TIMER3_ENABLE_BIT);                                                       /*Timer3 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_3_BASE_ADDRESS;                                                /* TIMER3 Base Address */
           PWM_Ptr_TIM[2]=PWM_Ptr;
           channel_TIM[2]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[2]=autoReload;
           break;
  case 4:  SET_BIT(RCC_APB1ENR,TIMER4_ENABLE_BIT);                                                       /*Timer4 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_4_BASE_ADDRESS;                                                /* TIMER4 Base Address */
           PWM_Ptr_TIM[3]=PWM_Ptr;
           channel_TIM[3]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[3]=autoReload;
           break;
  case 5:  SET_BIT(RCC_APB1ENR,TIMER5_ENABLE_BIT);                                                       /*Timer5 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_5_BASE_ADDRESS;                                                /* TIMER5 Base Address */
           PWM_Ptr_TIM[4]=PWM_Ptr;
           channel_TIM[4]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[4]=autoReload;
           break;
  case 8:  SET_BIT(RCC_APB2ENR,TIMER8_ENABLE_BIT);                                                       /*Timer8 clock enable */
           PWM_Ptr = (volatile uint32 *)TIM_8_BASE_ADDRESS;                                                /* TIMER8 Base Address */
           PWM_Ptr_TIM[5]=PWM_Ptr;
           channel_TIM[5]=Config_Ptr->TIMERS_NUM[i].channel_num;
           autoReload_TIM[5]=autoReload;
           break;
     }
    
    
     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr   + TIMx_CR1_REG_OFFSET),7); /*Setting Enable ARR */
     CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CR1_REG_OFFSET),4); /*Upcounting*/
     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr   + TIMx_CR2_REG_OFFSET),6); /*Master output trigger*/
     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr   + TIMx_SMCR_REG_OFFSET),7);/*TRIGGER ADJUSTION*/    
    *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CNT_REG_OFFSET) =0; 
    *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_PSC_REG_OFFSET) = prescaler;           /*Set the prescaler value*/
    *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_ARR_REG_OFFSET) = autoReload;         /*Set the autoreload value to the desired delay in milliseconds (1 SEC =1000MilliSEC)*/
   
       switch(Config_Ptr->TIMERS_NUM[i].channel_num)
  {
   case 1:  *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR1_REG_OFFSET)= 0x00; 
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),0);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),1);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),3);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),4);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),5);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),6);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),1);/*CCER POLARITY ACTIVE HIGH*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),0);  /*Enable Compare output*/ 
           break;
   case 2:  *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR2_REG_OFFSET)= 0x00; 
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),8);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),9);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),11);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),12);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),13);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR1_REG_OFFSET),14);
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),5);/*CCER POLARITY ACTIVE HIGH*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),4);  /*Enable Compare output*/
           break;   
   case 3:  *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR3_REG_OFFSET)= 0x00; 
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),0);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),1);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),3);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),4);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),5);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),6);
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),9);/*CCER POLARITY ACTIVE HIGH*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),8);  /*Enable Compare output*/
           break;
   case 4:  *(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR4_REG_OFFSET)= 0x00; 
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),8);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),9);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),11);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),12);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),13);
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCMR2_REG_OFFSET),14);
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),13);/*CCER POLARITY ACTIVE HIGH*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCER_REG_OFFSET),12);  /*Enable Compare output*/
           break;
  }
  
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_EGR_REG_OFFSET),0);  /*Update generation to initialize all registers*/
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_BDTR_REG_OFFSET),15);/*MOE*/
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CR1_REG_OFFSET),0);  /*counter enable*/
                  
       
     
     
    }
  
  }



}



/*********************************************************************************************/
/* 
 *Description: 
 *Function to Set DUTY CYCLE for PWM mode.
 *1-khzn el value ele gya mn map fel CCR1-->CCR4 3la hasab elchannel
*********************************************************************************************/
void GPT_SET_DUTY_CYCLE(uint8 TIM_x,uint16 duty_cycle)
{
  volatile uint32 * PWM_Ptr = NULL_PTR; /* point to the required PWM Registers base address */
   uint16 autoReload=0;
    uint8 channel =0;

  switch(TIM_x)
  {
    case 1: PWM_Ptr=PWM_Ptr_TIM[0];
            autoReload=autoReload_TIM[0];
            channel=channel_TIM[0];
           break;
    case 2: PWM_Ptr=PWM_Ptr_TIM[1];
            autoReload=autoReload_TIM[1];
            channel=channel_TIM[1];
           break;
    case 3: PWM_Ptr=PWM_Ptr_TIM[2];
            autoReload=autoReload_TIM[2];
            channel=channel_TIM[2];
           break;
    case 4: PWM_Ptr=PWM_Ptr_TIM[3];
            autoReload=autoReload_TIM[3];
            channel=channel_TIM[3];
           break;
    case 5: PWM_Ptr=PWM_Ptr_TIM[4];
            autoReload=autoReload_TIM[4];
            channel=channel_TIM[4];
           break;
    case 8: PWM_Ptr=PWM_Ptr_TIM[5];
            autoReload=autoReload_TIM[5];
            channel=channel_TIM[5];
           break;
  }
  uint16 COMPARE_VALUE = ((autoReload) * duty_cycle) / 100;   /* D (%)=(CCRx/ARRx) So divide by 100 */
  
  switch (channel)
  {
   case 1:*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR1_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/
           break;
   case 2:*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR2_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/
           break;
   case 3:*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR3_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/
           break;
   case 4:*(volatile uint32 *)((volatile uint8 *)PWM_Ptr + TIMx_CCR4_REG_OFFSET) = COMPARE_VALUE;   /*Set the compare value*/
           break;
  }
}
/*********************************************************************************************/
/*
 * Description :
 * Functional responsible for DeInitialize the TIMER device by:
 * Reset and Disable the TIMER Registers.
 */
/*********************************************************************************************/
void GPT_DeInit(uint8 TIM_X)
{
  switch (TIM_X)
  {
  case 1: CLEAR_BIT(RCC_APB2ENR,TIMER1_ENABLE_BIT);
  break;
  case 2: CLEAR_BIT(RCC_APB1ENR,TIMER2_ENABLE_BIT);
  break;
  case 3: CLEAR_BIT(RCC_APB1ENR,TIMER3_ENABLE_BIT);
  break;
  case 4: CLEAR_BIT(RCC_APB1ENR,TIMER4_ENABLE_BIT);
  break;
  case 5: CLEAR_BIT(RCC_APB1ENR,TIMER5_ENABLE_BIT);
  break;
  case 8: CLEAR_BIT(RCC_APB2ENR,TIMER8_ENABLE_BIT);
  break;
 
    
  }
}
/*********************************************************************************************/
/* 
Description:
Function to Setup the Timer call back
*/
/*********************************************************************************************/
/*void GPT_SetCallBack(void(*Ptr2Func)(void))
{
    g_Timer_Call_Back_Ptr = Ptr2Func;
}*/
