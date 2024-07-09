 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Port_Regs.h
 *
* Description: Header file for STM32F103C8T6 Microcontroller - STM32F103C8T6 REGISTERS
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#ifndef TM4C123GH6PM_REGISTERS
#define TM4C123GH6PM_REGISTERS

#include "Std_Types.h"

/*****************************************************************************
                           GPIO registers (PORTA)
*****************************************************************************/
#define GPIO_PORTA_CONF_LOW_REG                   (*((volatile uint32 *)0x40010800))           /*GPIOx_CRL*/
#define GPIO_PORTA_CONF_HIGH_REG                  (*((volatile uint32 *)0x40010804))           /*GPIOx_CRH*/
#define GPIO_PORTA_INPUT_DATA_REG                 (*((volatile uint32 *)0x40010808))           /*GPIOx_IDR*/
#define GPIO_PORTA_OUTPUT_DATA_REG                (*((volatile uint32 *)0x4001080C))           /*GPIOx_ODR*/
#define GPIO_PORTA_BIT_SET_OR_RESET_REG           (*((volatile uint32 *)0x40010810))           /*GPIOx_BSRR*/
#define GPIO_PORTA_BIT_RESET_REG                  (*((volatile uint32 *)0x40010814))           /*GPIOx_BRR*/
#define GPIO_PORTA_CONF_LOCK_REG                  (*((volatile uint32 *)0x40010818))           /*GPIOx_LCKR*/

/*****************************************************************************
                           GPIO registers (PORTB)
*****************************************************************************/
#define GPIO_PORTB_CONF_LOW_REG                   (*((volatile uint32 *)0x40010C00))           /*GPIOx_CRL*/
#define GPIO_PORTB_CONF_HIGH_REG                  (*((volatile uint32 *)0x40010C04))           /*GPIOx_CRH*/
#define GPIO_PORTB_INPUT_DATA_REG                 (*((volatile uint32 *)0x40010C08))           /*GPIOx_IDR*/
#define GPIO_PORTB_OUTPUT_DATA_REG                (*((volatile uint32 *)0x40010C0C))           /*GPIOx_ODR*/
#define GPIO_PORTB_BIT_SET_OR_RESET_REG           (*((volatile uint32 *)0x40010C10))           /*GPIOx_BSRR*/
#define GPIO_PORTB_BIT_RESET_REG                  (*((volatile uint32 *)0x40010C14))           /*GPIOx_BRR*/
#define GPIO_PORTB_CONF_LOCK_REG                  (*((volatile uint32 *)0x40010C18))           /*GPIOx_LCKR*/

/*****************************************************************************
                           GPIO registers (PORTC)
*****************************************************************************/
#define GPIO_PORTC_CONF_LOW_REG                   (*((volatile uint32 *)0x40011000))           /*GPIOx_CRL*/
#define GPIO_PORTC_CONF_HIGH_REG                  (*((volatile uint32 *)0x40011004))           /*GPIOx_CRH*/
#define GPIO_PORTC_INPUT_DATA_REG                 (*((volatile uint32 *)0x40011008))           /*GPIOx_IDR*/
#define GPIO_PORTC_OUTPUT_DATA_REG                (*((volatile uint32 *)0x4001100C))           /*GPIOx_ODR*/
#define GPIO_PORTC_BIT_SET_OR_RESET_REG           (*((volatile uint32 *)0x40011010))           /*GPIOx_BSRR*/
#define GPIO_PORTC_BIT_RESET_REG                  (*((volatile uint32 *)0x40011014))           /*GPIOx_BRR*/
#define GPIO_PORTC_CONF_LOCK_REG                  (*((volatile uint32 *)0x40011018))           /*GPIOx_LCKR*/

/* PORTC External Interrupts Registers */

/*****************************************************************************
                           GPIO registers (PORTD)
*****************************************************************************/
#define GPIO_PORTD_CONF_LOW_REG                   (*((volatile uint32 *)0x40011400))           /*GPIOx_CRL*/
#define GPIO_PORTD_CONF_HIGH_REG                  (*((volatile uint32 *)0x40011404))           /*GPIOx_CRH*/
#define GPIO_PORTD_INPUT_DATA_REG                 (*((volatile uint32 *)0x40011408))           /*GPIOx_IDR*/
#define GPIO_PORTD_OUTPUT_DATA_REG                (*((volatile uint32 *)0x4001140C))           /*GPIOx_ODR*/
#define GPIO_PORTD_BIT_SET_OR_RESET_REG           (*((volatile uint32 *)0x40011410))           /*GPIOx_BSRR*/
#define GPIO_PORTD_BIT_RESET_REG                  (*((volatile uint32 *)0x40011414))           /*GPIOx_BRR*/
#define GPIO_PORTD_CONF_LOCK_REG                  (*((volatile uint32 *)0x40011418))           /*GPIOx_LCKR*/


/* PORTD External Interrupts Registers */

/*****************************************************************************
                           GPIO registers (PORTE)
*****************************************************************************/
#define GPIO_PORTE_CONF_LOW_REG                   (*((volatile uint32 *)0x40011800))           /*GPIOx_CRL*/
#define GPIO_PORTE_CONF_HIGH_REG                  (*((volatile uint32 *)0x40011804))           /*GPIOx_CRH*/
#define GPIO_PORTE_INPUT_DATA_REG                 (*((volatile uint32 *)0x40011808))           /*GPIOx_IDR*/
#define GPIO_PORTE_OUTPUT_DATA_REG                (*((volatile uint32 *)0x4001180C))           /*GPIOx_ODR*/
#define GPIO_PORTE_BIT_SET_OR_RESET_REG           (*((volatile uint32 *)0x40011810))           /*GPIOx_BSRR*/
#define GPIO_PORTE_BIT_RESET_REG                  (*((volatile uint32 *)0x40011814))           /*GPIOx_BRR*/
#define GPIO_PORTE_CONF_LOCK_REG                  (*((volatile uint32 *)0x40011818))           /*GPIOx_LCKR*/

/* PORTE External Interrupts Registers */

/*****************************************************************************
                           GPIO registers (PORTF)
*****************************************************************************/
#define GPIO_PORTF_CONF_LOW_REG                   (*((volatile uint32 *)0x40011C00))           /*GPIOx_CRL*/
#define GPIO_PORTF_CONF_HIGH_REG                  (*((volatile uint32 *)0x40011C04))           /*GPIOx_CRH*/
#define GPIO_PORTF_INPUT_DATA_REG                 (*((volatile uint32 *)0x40011C08))           /*GPIOx_IDR*/
#define GPIO_PORTF_OUTPUT_DATA_REG                (*((volatile uint32 *)0x40011C0C))           /*GPIOx_ODR*/
#define GPIO_PORTF_BIT_SET_OR_RESET_REG           (*((volatile uint32 *)0x40011C10))           /*GPIOx_BSRR*/
#define GPIO_PORTF_BIT_RESET_REG                  (*((volatile uint32 *)0x40011C14))           /*GPIOx_BRR*/
#define GPIO_PORTF_CONF_LOCK_REG                  (*((volatile uint32 *)0x40011C18))           /*GPIOx_LCKR*/

/* PORTF External Interrupts Registers */

/*****************************************************************************
                           GPIO registers (PORTF)
*****************************************************************************/
#define GPIO_PORTG_CONF_LOW_REG                   (*((volatile uint32 *)0x40012000))           /*GPIOx_CRL*/
#define GPIO_PORTG_CONF_HIGH_REG                  (*((volatile uint32 *)0x40012004))           /*GPIOx_CRH*/
#define GPIO_PORTG_INPUT_DATA_REG                 (*((volatile uint32 *)0x40012008))           /*GPIOx_IDR*/
#define GPIO_PORTG_OUTPUT_DATA_REG                (*((volatile uint32 *)0x4001200C))           /*GPIOx_ODR*/
#define GPIO_PORTG_BIT_SET_OR_RESET_REG           (*((volatile uint32 *)0x40012010))           /*GPIOx_BSRR*/
#define GPIO_PORTG_BIT_RESET_REG                  (*((volatile uint32 *)0x40012014))           /*GPIOx_BRR*/
#define GPIO_PORTG_CONF_LOCK_REG                  (*((volatile uint32 *)0x40012018))           /*GPIOx_LCKR*/

/* PORTG External Interrupts Registers */

/*****************************************************************************
Reset and clock control RCC registers
*****************************************************************************/
#define RCC_CR                                    (*((volatile uint32 *)0x40021000))
#define RCC_CFGR                                  (*((volatile uint32 *)0x40021004))
#define RCC_CIR                                   (*((volatile uint32 *)0x40021008))
#define RCC_APB2RSTR                              (*((volatile uint32 *)0x4002100C))
#define RCC_APB1RSTR                              (*((volatile uint32 *)0x40021010))
#define RCC_AHBENR                                (*((volatile uint32 *)0x40021014))
#define RCC_APB2ENR                               (*((volatile uint32 *)0x40021018))      
#define RCC_APB1ENR                               (*((volatile uint32 *)0x4002101C))
#define RCC_BDCR                                  (*((volatile uint32 *)0x40021020))
#define RCC_CSR                                   (*((volatile uint32 *)0x40021024))
#define RCC_AHBSTR                                (*((volatile uint32 *)0x40021028))
#define RCC_CFGR2                                 (*((volatile uint32 *)0x4002102C))
   
#define RCC_CR_HSEON                              0x00010000
#define RCC_CR_HSERDY                             0x00020000
#define RCC_CR_PLLON                              0x01000000
#define RCC_CR_PLLRDY                             0x02000000  
 
#define RCC_CFGR_PLLSRC_HSE                       0x00010000
#define RCC_CFGR_PLLMULL9                         0x001C0000
#define RCC_CFGR_PLLXTPRE_HSE_DIV1                0x00000000
#define RCC_CFGR_SW_PLL                           0x00000002
#define RCC_CFGR_SWS_PLL                          0x00000008  
       
/*****************************************************************************
                                AFIO registers
*****************************************************************************/
#define AFIO_EVENT_CTRL_REG                       (*((volatile uint32 *)0x40010000))           /*AFIO_EVCR*/
#define AFIO_REMAP_AND_DEBUG_REG                  (*((volatile uint32 *)0x40010004))           /*AFIO_MAPR*/
#define AFIO_EXTERNAL_INTERRUPT_CFG_REG_1         (*((volatile uint32 *)0x40010008))           /*AFIO_EXTICR1*/
#define AFIO_EXTERNAL_INTERRUPT_CFG_REG_2         (*((volatile uint32 *)0x4001000C))           /*AFIO_EXTICR2*/
#define AFIO_EXTERNAL_INTERRUPT_CFG_REG_3         (*((volatile uint32 *)0x40010010))           /*AFIO_EXTICR3*/
#define AFIO_EXTERNAL_INTERRUPT_CFG_REG_4         (*((volatile uint32 *)0x40010014))           /*AFIO_EXTICR4*/
#define AFIO_REMAP_AND_DEBUG_REG_2                (*((volatile uint32 *)0x4001001C))           /*AFIO_MAPR2*/

/*****************************************************************************
*                              NVIC Registers
*****************************************************************************/
#define NVIC_BASE_ADDRESS                         (*((volatile uint32 *)0xE000E100))

#define NVIC_ISER0_REG                            (*((volatile uint32 *)0xE000E100))
#define NVIC_ISER1_REG                            (*((volatile uint32 *)0xE000E104))
#define NVIC_ISER2_REG                            (*((volatile uint32 *)0xE000E108))
#define NVIC_ICER0_REG                            (*((volatile uint32 *)0xE000E180))
#define NVIC_ICER1_REG                            (*((volatile uint32 *)0xE000E184))
#define NVIC_ICER2_REG                            (*((volatile uint32 *)0xE000E188))
#define NVIC_ISPR0_REG                            (*((volatile uint32 *)0xE000E200))
#define NVIC_ISPR1_REG                            (*((volatile uint32 *)0xE000E204))
#define NVIC_ISPR2_REG                            (*((volatile uint32 *)0xE000E208))
#define NVIC_ICPR0_REG                            (*((volatile uint32 *)0xE000E280))
#define NVIC_ICPR1_REG                            (*((volatile uint32 *)0xE000E284))
#define NVIC_ICPR2_REG                            (*((volatile uint32 *)0xE000E288))
#define NVIC_IABP0_REG                            (*((volatile uint32 *)0xE000E300))
#define NVIC_IABP1_REG                            (*((volatile uint32 *)0xE000E304))
#define NVIC_IABP2_REG                            (*((volatile uint32 *)0xE000E308))

#define NVIC_PRI0_REG                             (*((volatile uint32 *)0xE000E400))
#define NVIC_PRI1_REG                             (*((volatile uint32 *)0xE000E404))
#define NVIC_PRI2_REG                             (*((volatile uint32 *)0xE000E408))
#define NVIC_PRI3_REG                             (*((volatile uint32 *)0xE000E40C))
#define NVIC_PRI4_REG                             (*((volatile uint32 *)0xE000E410))
#define NVIC_PRI5_REG                             (*((volatile uint32 *)0xE000E414))
#define NVIC_PRI6_REG                             (*((volatile uint32 *)0xE000E418))
#define NVIC_PRI7_REG                             (*((volatile uint32 *)0xE000E41C))
#define NVIC_PRI8_REG                             (*((volatile uint32 *)0xE000E420))
#define NVIC_PRI9_REG                             (*((volatile uint32 *)0xE000E424))
#define NVIC_PRI10_REG                            (*((volatile uint32 *)0xE000E428))
#define NVIC_PRI11_REG                            (*((volatile uint32 *)0xE000E42C))
#define NVIC_PRI12_REG                            (*((volatile uint32 *)0xE000E430))
#define NVIC_PRI13_REG                            (*((volatile uint32 *)0xE000E434))
#define NVIC_PRI14_REG                            (*((volatile uint32 *)0xE000E438))
#define NVIC_PRI15_REG                            (*((volatile uint32 *)0xE000E43C))

#define NVIC_STIR_REG                             (*((volatile uint32 *)0xE000EF00))

/*****************************************************************************
FLASH registers
*****************************************************************************/ 
 #define FLASH_ACR                                 (*((volatile uint32 *)0x40022000))
  
#define FLASH_ACR_PRFTBE                           0x00000010
#define FLASH_ACR_LATENCY_2                        0x00000002
/*****************************************************************************
Timer registers
*****************************************************************************/
/* TIMER Registers base addresses */
#define TIM_1_BASE_ADDRESSs             0x40012C00
#define TIM_2_BASE_ADDRESS             0x40000000 
#define TIM_3_BASE_ADDRESSs             0x40000400 
#define TIM_4_BASE_ADDRESSs            0x40000800 
#define TIM_5_BASE_ADDRESS             0x40000C00 
#define TIM_8_BASE_ADDRESS             0x40013400
/* TIMER Registers offset addresses */
#define TIMx_ARR_REG_OFFSET            0x2C
#define TIMx_CR1_REG_OFFSET            0x00
#define TIMx_CR2_REG_OFFSET            0x04
#define TIMx_SMCR_REG_OFFSET           0x08
#define TIMx_DIER_REG_OFFSET           0x0C
#define TIMx_SR_REG_OFFSET             0x10
#define TIMx_CCER_REG_OFFSET           0x20
#define TIMx_CNT_REG_OFFSET            0x24
#define TIMx_CCR1_REG_OFFSET           0x34
#define TIMx_CCR2_REG_OFFSET           0x38
#define TIMx_CCR3_REG_OFFSET           0x3C
#define TIMx_CCR4_REG_OFFSET           0x40
#define TIMx_PSC_REG_OFFSET            0x28
#define TIMx_CCMR1_REG_OFFSET          0x18
#define TIMx_CCMR2_REG_OFFSET          0x1C
#define TIMx_EGR_REG_OFFSET            0x14
#define TIMx_BDTR_REG_OFFSET           0x44

/************************Redefine for a certain purpose************************/
#define TIM1_SR_REGG                     (*((volatile uint32 *)0x40012C10))
#define TIM2_SR_REG                     (*((volatile uint32 *)0x40000010))
#define TIM3_SR_REGG                     (*((volatile uint32 *)0x40000410))
#define TIM4_SR_REGG                     (*((volatile uint32 *)0x40000810))
#define TIM5_SR_REG                     (*((volatile uint32 *)0x40000C10))
#define TIM8_SR_REG                     (*((volatile uint32 *)0x40013410))


/*****************************************************************************
*                              systick Registers
*****************************************************************************/
#define STK_BASE_ADDRESS                        (*((volatile uint32 *)0xE000E010))

#define STK_CTRL_REG                            (*((volatile uint32 *)0xE000E010))
#define STK_LOAD_REG                            (*((volatile uint32 *)0xE000E014))
#define STK_VAL_REG                             (*((volatile uint32 *)0xE000E018))
#define STK_CNT_FLAG                            16                        


#endif
