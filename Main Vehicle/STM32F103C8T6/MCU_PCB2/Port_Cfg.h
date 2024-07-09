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

#ifndef PORT_CFG_H
#define PORT_CFG_H

 /*
  * Module Version 1.0.0
  */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

  /*
   * AUTOSAR Version 4.0.3
   */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION                  (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION                  (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION                  (3U)

   /* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                           (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                           (STD_ON)

/* Pre-compile option for presence of Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API			(STD_ON)

/* Pre-compile option for presence of Port_SetPinMode API */
#define PORT_SET_PIN_MODE_API				(STD_ON)

/* Number of the configured Port Channels */
#define PORT_CONFIGURED_CHANNLES                                       (32U) 

/* Ports Type */
#define PORT_PORT_A                                                    (0U)
#define PORT_PORT_B                                                    (1U)
#define PORT_PORT_C                                                    (2U)
#define PORT_PORT_D                                                    (3U)
#define PORT_PORT_E                                                    (4U)
#define PORT_PORT_H                                                    (5U)
#define PORT_PORT_G                                                    (6U)

/* Pin Numbers */
#define PORT_PIN_0                                                     (0U)
#define PORT_PIN_1                                                     (1U)
#define PORT_PIN_2                                                     (2U)
#define PORT_PIN_3                                                     (3U)
#define PORT_PIN_4                                                     (4U)
#define PORT_PIN_5                                                     (5U)
#define PORT_PIN_6                                                     (6U)
#define PORT_PIN_7                                                     (7U)
#define PORT_PIN_8                                                     (8U)
#define PORT_PIN_9                                                     (9U)
#define PORT_PIN_10                                                    (10U)
#define PORT_PIN_11                                                    (11U)
#define PORT_PIN_12                                                    (12U)
#define PORT_PIN_13                                                    (13U)
#define PORT_PIN_14                                                    (14U)
#define PORT_PIN_15                                                    (15U)

/* PORTA Pins */
#define PORTA_PIN_0                                                     (0U)
#define PORTA_PIN_1                                                     (1U)
#define PORTA_PIN_2                                                     (2U)
#define PORTA_PIN_3                                                     (3U)
#define PORTA_PIN_4                                                     (4U)
#define PORTA_PIN_5                                                     (5U)
#define PORTA_PIN_6                                                     (6U)
#define PORTA_PIN_7                                                     (7U)
#define PORTA_PIN_8                                                     (8U)
#define PORTA_PIN_9                                                     (9U)
#define PORTA_PIN_10                                                    (10U)
#define PORTA_PIN_11                                                    (11U)
#define PORTA_PIN_12                                                    (12U)
#define PORTA_PIN_15                                                    (13U)

/* PORTB Pins */
#define PORTB_PIN_0                                                     (14U)
#define PORTB_PIN_1                                                     (15U)
#define PORTB_PIN_3                                                     (16U)
#define PORTB_PIN_4                                                     (17U)
#define PORTB_PIN_5                                                     (18U)
#define PORTB_PIN_6                                                     (19U)
#define PORTB_PIN_7                                                     (20U)
#define PORTB_PIN_8                                                     (21U)
#define PORTB_PIN_9                                                     (22U)
#define PORTB_PIN_10                                                    (23U)
#define PORTB_PIN_11                                                    (24U)
#define PORTB_PIN_12                                                    (25U)
#define PORTB_PIN_13                                                    (26U)
#define PORTB_PIN_14                                                    (27U)
#define PORTB_PIN_15                                                    (28U)

/* PORTC Pins */
#define PORTC_PIN_13                                                    (29U)
#define PORTC_PIN_14                                                    (30U)
#define PORTC_PIN_15                                                    (31U)

#endif /* PORT_CFG_H */