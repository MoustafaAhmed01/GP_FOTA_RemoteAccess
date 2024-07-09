/******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for STM32F401RCT6 Microcontroller - Port Driver
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#ifndef DMA_CFG_H
#define DMA_CFG_H

/*
 * Module Version 1.0.0
 */
#define DMA_CFG_SW_MAJOR_VERSION              (1U)
#define DMA_CFG_SW_MINOR_VERSION              (0U)
#define DMA_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DMA_CFG_AR_RELEASE_MAJOR_VERSION                  (4U)
#define DMA_CFG_AR_RELEASE_MINOR_VERSION                  (0U)
#define DMA_CFG_AR_RELEASE_PATCH_VERSION                  (3U)

/* Pre-compile option for Development Error Detect */
#define DMA_DEV_ERROR_DETECT                           (STD_ON)

/* Number of the configured Port Channels */
#define DMA_CONFIGURED_CHANNLES                                       (12U) 

/* DMA Type */
#define DMA_1                                                         (0U)
#define DMA_2                                                         (1U)

/* DMA 1 Channel Numbers */
#define DMA_CHANNEL_1                                                 (1U)
#define DMA_CHANNEL_2                                                 (2U)
#define DMA_CHANNEL_3                                                 (3U)
#define DMA_CHANNEL_4                                                 (4U)
#define DMA_CHANNEL_5                                                 (5U)
#define DMA_CHANNEL_6                                                 (6U)
#define DMA_CHANNEL_7                                                 (7U)

#define DMA_CCR_MASK                                                  0xFFFF8000  
#define DMA_CNDTR_MASK                                                0xFFFF0000 

#endif /* DMA_CFG_H */