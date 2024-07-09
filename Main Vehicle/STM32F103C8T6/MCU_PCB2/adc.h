 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the STm32f103c8 blue pill ADC driver
 *
 * Author: Shady Alaa Eldeen Mohammed
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_
#include "ADC_Cfg.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


typedef enum {
  DISABLE,ENABLE

}ADC_Enable;
typedef enum {
  ALL,SINGLE

}ADC_wdCh;

typedef enum {
  Independent_Mode=0,
  Regular_Simultaneous_Injected_Simultaneous=1, 
  Regular_Simultaneous_Alternate_Trigger=2,
  Regular_Simultaneous_Only=6,
  Fast_Interleaved_Only=7 ,
  Slow_Interleaved_Only=8,
  Alternate_Trigger_Only=9
}ADC_DualMode_t;

typedef enum {
  ONE_CHANNEL , TWO_CHANNEL, THREE_CHANNEL, FOUR_CHANNEL
}ADC_DModeCount;

typedef enum{
  DISABLE_INTERRUPT,ENABLE_INTERRUPT
}ADC_inter;

typedef enum{
  RIGHT,LEFT
}ADC_Allign;

typedef enum{

  T_1_PERIOD,T_2_PERIOD,T_3_PERIOD,T_4_PERIOD,T_5_PERIOD,T_6_PERIOD,T_7_PERIOD,T_8_PERIOD

}ADC_SampleTime;

typedef enum{
 ADC1,ADC2
}eADC_Num_t;
typedef enum{
  PRESCALE_2_,PRESCALE_4_,PRESCALE_8_
}eADC_prescale_t;
typedef enum{
  TIMER_1_CC1,TIMER_1_CC2,TIMER_1_CC3,TIMER_2_CC2,Timer_3_TRGO,TIMER_4_CC4,EXTERNAL_LINE,SW_START=7
}eADC_ExtSEL_t ;

typedef  struct {
   eADC_Num_t      ADC_num;
   uint8          channel_index;
   eADC_prescale_t ADC_prescaler;
   ADC_Enable      wd_en; /*watchdog enable for regular channels*/
   ADC_DualMode_t  dual_mode;
   ADC_DModeCount  disc_count;  /*no. of discont channels to run*/
   ADC_Enable      disc_mode;
   uint8           wd_channelIndex; /*input Channels to be guarded by watchdog AWDCH[0:4]*/
   ADC_wdCh        wd_single;  /*AWDSGL pin: to Enable the watchdog on a single channel in scan mode*/
   ADC_Enable      scan_mode;
   ADC_inter       wdi_en; /*Watchdog interrupt [AWDIE]*/
   ADC_inter       eoc_en;  /*EOCIE interrupt*/
   ADC_Allign      allign_mode;
   ADC_Enable      DMA_req;            /*Only for ADC1,ADC3*/
   ADC_Enable      wdj_en; /*watchdog enable for injected channels*/
  ADC_Enable      discj_mode;
  ADC_Enable      jauto_mode;
  ADC_inter       intj_en;    /*Interrupt enable for injected channels*/
  eADC_ExtSEL_t     external_trig_mode;
  ADC_Enable      external_trig; /*enable/disable the external trigger used to start conversion of a regular channel group*/
  ADC_Enable      externalj_trig; /*enable/disable the external trigger used to start conversion of a regular channel group*/
  ADC_SampleTime  sample_select;  /*Channel x Sample time selection*/
}ADC_Config;


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */
//extern volatile uint16 g_adcResult;
//extern ADC_Config  ADC_PBcfg;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/******************************************************************************
 * Description :
 * Function responsible for initialize the ADC driver.
 *
 *****************************************************************************/
void ADC_init(ADC_Config* Config_ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num, eADC_Num_t ADC_num);

#endif /* ADC_H_ */
