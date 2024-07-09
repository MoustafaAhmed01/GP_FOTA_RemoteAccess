 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name:ADC_REG.h
 *
 * Description: header file for the STm32f103c8 blue pill ADC REGISTERS MAP
 *
 * Author: Shady Alaa Eldeen Mohammed
 *
 *******************************************************************************/

#ifndef ADC_REG_H_
#define ADC_REG_H_

#include "std_types.h"

#define ADC1_BASE_ADDRESS                                         0x40012400
#define ADC2_BASE_ADDRESS                                         0x40012800
#define ADC3_BASE_ADDRESS                                         0x40013C00
#define RCC_BASE_ADDRESS                                          0x40021000

typedef struct{  
volatile uint32  ADC_SR_REGISTER;
volatile uint32  ADC_CR1_REGISTER;
volatile uint32  ADC_CR2_REGISTER;
volatile uint32  ADC_SMPR1_REGISTER;
volatile uint32  ADC_SMPR2_REGISTER;
volatile uint32  ADC_JOFR1_REGISTER;
volatile uint32  ADC_JOFR2_REGISTER;
volatile uint32  ADC_JOFR3_REGISTER;
volatile uint32  ADC_JOFR4_REGISTER;
volatile uint32  ADC_HTR_REGISTER;
volatile uint32  ADC_LTR_REGISTER;
volatile uint32  ADC_SQR1_REGISTER;
volatile uint32  ADC_SQR2_REGISTER;
volatile uint32  ADC_SQR3_REGISTER;
volatile uint32  ADC_JSQR_REGISTER;
volatile uint32  ADC_JDR1_REGISTER;
volatile uint32  ADC_JDR2_REGISTER;
volatile uint32  ADC_JDR3_REGISTER;
volatile uint32  ADC_JDR4_REGISTER;
volatile uint32  ADC_DR_REGISTER;
}ADC_Map;

ADC_Map * ADCx[2]=
{
	(( ADC_Map*)ADC1_BASE_ADDRESS),
	(( ADC_Map*)ADC2_BASE_ADDRESS),
       
};

typedef struct {
   uint32 RCC_CR_REGISTER;
   uint32 RCC_CFGR_REGISTER;
   uint32 RCC_CIR_REGISTER;
   uint32 RCC_APB2RSTR_REGISTER;
   uint32 RCC_APB1RSTR_REGISTER;
   uint32 RCC_AHBENR_REGISTER;
   uint32 RCC_APB2ENR_REGISTER;
   uint32 RCC_APB1ENR_REGISTER;
   uint32 RCC_BDCR_REGISTER;
   uint32 RCC_CSR_REGISTER;
   uint32 RCC_AHBSTR_REGISTER;
   uint32 RCC_CFGR2_REGISTER;
  
  
   }RCC_Map;

RCC_Map *RCC;

#endif /*ADC_REG_H_*/
