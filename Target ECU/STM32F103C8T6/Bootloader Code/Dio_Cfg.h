 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for STM32F103C8T6 Microcontroller - Dio Driver
 *
 * Author: Moustafa Ahmed
 ******************************************************************************/

#ifndef DIO_CFG_H
#define DIO_CFG_H

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                 (STD_OFF)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                 (STD_ON)

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES                 (7U)
/* Channel Index in the array of structures in Dio_PBcfg.c */
/** lCD **/

#define DioConf_LCD_D4_CHANNEL_ID_INDEX             (uint8)0                      /* LCD D4 */
#define DioConf_LCD_D5_CHANNEL_ID_INDEX             (uint8)1                      /* LCD D5 */
#define DioConf_LCD_D6_CHANNEL_ID_INDEX             (uint8)2                      /* LCD D6 */
#define DioConf_LCD_D7_CHANNEL_ID_INDEX             (uint8)3                      /* LCD D7 */
#define DioConf_LCD_EN_CHANNEL_ID_INDEX             (uint8)4                      /* LCD EN */
#define DioConf_LCD_RS_CHANNEL_ID_INDEX             (uint8)5                      /* LCD RS */
#define DioConf_LED2_CHANNEL_ID_INDEX               (uint8)6                      /* led pc13*/





/* DIO Configured Port ID's */




/** LCD **/
#define DioConf_LCD_D4_PORT_NUM              (Dio_PortType)1 /* PortB */
#define DioConf_LCD_D5_PORT_NUM              (Dio_PortType)1 /* PortB */
#define DioConf_LCD_D6_PORT_NUM              (Dio_PortType)0 /* PortA */
#define DioConf_LCD_D7_PORT_NUM              (Dio_PortType)0 /* PortA */
#define DioConf_LCD_EN_PORT_NUM              (Dio_PortType)1 /* PortB */
#define DioConf_LCD_RS_PORT_NUM              (Dio_PortType)1 /* PortB */
   
#define DioConf_LED2_PORT_NUM                (Dio_PortType)2 /* PORTC */

/** LCD **/
#define DioConf_LCD_D4_CHANNEL_NUM              (Dio_ChannelType)1      /* PINA11 */
#define DioConf_LCD_D5_CHANNEL_NUM              (Dio_ChannelType)0      /* PINA12 */
#define DioConf_LCD_D6_CHANNEL_NUM              (Dio_ChannelType)7      /* PINC15 */
#define DioConf_LCD_D7_CHANNEL_NUM              (Dio_ChannelType)6      /* PINC14 */
                                                                            
#define DioConf_LCD_EN_CHANNEL_NUM              (Dio_ChannelType)12     /* PINB12 */
#define DioConf_LCD_RS_CHANNEL_NUM              (Dio_ChannelType)13     /* PINB13 */

#define DioConf_LED2_CHANNEL_NUM                (Dio_ChannelType)13     /* Pin 13 in PORTC */
#endif /* DIO_CFG_H */
