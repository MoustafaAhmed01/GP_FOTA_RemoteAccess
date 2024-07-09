
/******************************************************************************
 *
 * Module: SYS_TIMER
 *
 * File Name: SYS_TIMER.c
 *
 * Description: Source file for STM32F103xx Microcontroller - SYS_TIMER Driver
 *
 * Author: Esraa Ali
 ******************************************************************************/
#include "sys_timer.h"


/* Global pointer to function used to point upper layer functions
 * to be used in Call Back */
static void (*g_SysTick_Call_Back_Ptr)(void) = NULL_PTR;

/************************************************************************************
* Description: SysTick Timer ISR
************************************************************************************/
void SysTick_Handler(void)
{
    /* Check if the Timer0_setCallBack is already called */
    if(g_SysTick_Call_Back_Ptr != NULL_PTR)
    {
        (*g_SysTick_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
   /*
 * Description :
 * Functional responsible for Initialize the SysTick device by:
 * 1. Reset and Configure the SysTick Control Register.
 * 2. Setup the SysTick Reload value.
 * 3. Enable the SysTick.
 */
void SysTick_Init(const SYS_TIMER_ConfigType*Config_Ptr,uint32 Counter_Value)
{
  STK_CTRL_REG &= (0xFFFEFFF8 |0x04 );        /* Disable the SysTick Timer by Clear the ENABLE Bit (reset value=reserved 0 reserved 100)*/
  STK_LOAD_REG = Counter_Value-1;           /*to count 1 millisecond  Set the Reload value (N-1) but if delay (N).any value in the range 0x00000001-0x00FFFFFF [23:0] bit*/
  STK_VAL_REG  =0;                            /* Clear the Current Register value */
  /* Configure the SysTick Control Register 
     * Enable the SysTick Timer (ENABLE = 1)
     * SysTick exception request enable (TICKINT)
     * Choose the clock source to be System Clock (CLK_SRC = AHB_8 OR Processor_clock_AHB) */
  STK_CTRL_REG = (STK_CTRL_REG & 0xFFFEFFF8) | (((Config_Ptr->clocksource)<<2) | ((Config_Ptr->tickint)<<1) | ((Config_Ptr->enable)<<0));
 // NVIC_IPR1_REG= (NVIC_IPR1_REG &TIMER1_PRIORITY_MASK) | (TIMER1_INTERRUPT_PRIORITY<<TIMER1_PRIORITY_BITS_POS);
 //NVIC_ISER0_REG=(NVIC_ISER0_REG&TIMER1_SET_ENABLE_MASK)|(1<<TIMER1_SET_ENABLE_BIT_POS);
}

/*----------------------------------------------------------------------------*/
/*
 * Description :
 * Functional responsible for DeInitialize the SysTick device by:
 * 1.Reset and Disable the SysTick Registers.
 */
void SysTick_DeInit(void)
{
  STK_CTRL_REG &= (0xFFFEFFF8 |0x04 );        /* Disable the SysTick Timer by Clear the ENABLE Bit */
  STK_LOAD_REG = 0;                           /* Reset the Reload value (N-1) */
  STK_VAL_REG  =0;                            /* Clear the Current Register value */
}

/* 
Description:
Function to Setup the SysTick Timer call back
*/
void SysTick_SetCallBack(void(*Ptr2Func)(void))
{
    g_SysTick_Call_Back_Ptr = Ptr2Func;
}