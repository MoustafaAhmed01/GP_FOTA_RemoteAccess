 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_Cfg.h
 *
 * Description: Driver Configuration file for the STm32f103c8 blue pill ADC driver
 *
 * Author: Shady Alaa Eldeen Mohammed
 *
 *******************************************************************************/

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/***************************************************/
#define ADC_MAXIMUM_THRESHOLD    4095  /*0~2047*/
#define ADC_MINIMUM_THRESHOLD     0    /*0~2047*/
#define ADC_TOTAL_REGULAR_CONVERSIONS  1 /*1~15*/
#define  ADC_TOTAL_INJECTED_CONVERSIONS  1 /*1~4*/
#define ADC_CHANNEL_0_        0
#define ADC_CHANNEL_1_        1
#define ADC_CHANNEL_2_        2
#define ADC_CHANNEL_3_        3
#define ADC_CHANNEL_4_        4
#define ADC_CHANNEL_5_        5
#define ADC_CHANNEL_6_        6
#define ADC_CHANNEL_7_        7
#define ADC_CHANNEL_8_        8
#define ADC_CHANNEL_9_        9
#define ADC_CHANNEL_10_       10
#define ADC_CHANNEL_11_       11
#define ADC_CHANNEL_12_       12
#define ADC_CHANNEL_13_       13
#define ADC_CHANNEL_14_       14
#define ADC_CHANNEL_15_       15
#define ADC_CHANNEL_16_       16
#define ADC_CHANNEL_17_       17
/*********************************************************************************/
#define ADC1EN_BIT            9
#define ADC2EN_BIT            10
#define AWDEN_BIT             23
#define SCAN_BIT              8
#define DISCEN_BIT            11
#define AWDSGL_BIT            9
#define ALIGN_BIT             11
#define DMA_BIT               8
#define RSTCAL_BIT            3
#define ADON_BIT              0
#define CAL_BIT               2
#define SWSTART_BIT           22
#define START_BIT             4
#define EOC_BIT               1
#define AWD_BIT               0
#define CONT_BIT              1
/**********************************************************************************/
#endif /*ADC_CFG_H_*/