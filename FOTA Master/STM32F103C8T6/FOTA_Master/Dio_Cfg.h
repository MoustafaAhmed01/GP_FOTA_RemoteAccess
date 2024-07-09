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
#define DIO_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES              (16U)
/* Channel Index in the array of structures in Dio_PBcfg.c */

/** LED **/
#define DioConf_LED1_CHANNEL_ID_INDEX           (uint8)0
#define DioConf_LED2_CHANNEL_ID_INDEX           (uint8)1

/** Keypad & LCD **/
#define DioConf_KEYPAD_C1_CHANNEL_ID_INDEX      (uint8)2                       /* Keypad ROW1 */
#define DioConf_KEYPAD_C2_CHANNEL_ID_INDEX      (uint8)3                       /* Keypad ROW2 */
#define DioConf_KEYPAD_C3_CHANNEL_ID_INDEX      (uint8)4                       /* Keypad ROW3 */
#define DioConf_KEYPAD_C4_CHANNEL_ID_INDEX      (uint8)5                       /* Keypad ROW4 */
#define DioConf_KEYPAD_R1_CHANNEL_ID_INDEX      (uint8)6                       /* Keypad COL1 */
#define DioConf_KEYPAD_R2_CHANNEL_ID_INDEX      (uint8)7                       /* Keypad COL2 */
#define DioConf_KEYPAD_R3_CHANNEL_ID_INDEX      (uint8)8                       /* Keypad COL3 */
#define DioConf_KEYPAD_R4_CHANNEL_ID_INDEX      (uint8)9                       /* Keypad COL4 */
#define DioConf_LCD_D4_CHANNEL_ID_INDEX         (uint8)10                      /* LCD D4 */
#define DioConf_LCD_D5_CHANNEL_ID_INDEX         (uint8)11                      /* LCD D5 */
#define DioConf_LCD_D6_CHANNEL_ID_INDEX         (uint8)12                      /* LCD D6 */
#define DioConf_LCD_D7_CHANNEL_ID_INDEX         (uint8)13                      /* LCD D7 */
#define DioConf_LCD_EN_CHANNEL_ID_INDEX         (uint8)14                      /* LCD EN */
#define DioConf_LCD_RS_CHANNEL_ID_INDEX         (uint8)15                      /* LCD RS */

/* DIO Configured Port ID's  */

/** LED **/
#define DioConf_LED1_PORT_NUM                (Dio_PortType)0 /* PORTA */        
#define DioConf_LED2_PORT_NUM                (Dio_PortType)2 /* PORTA */

/** Keypad **/
#define DioConf_KEYPAD_R4_PORT_NUM           (Dio_PortType)0 /* PORTA NEW */
#define DioConf_KEYPAD_R3_PORT_NUM           (Dio_PortType)0 /* PortA NEW */
#define DioConf_KEYPAD_R2_PORT_NUM           (Dio_PortType)0 /* PortA NEW */
#define DioConf_KEYPAD_R1_PORT_NUM           (Dio_PortType)2 /* PortC */

#define DioConf_KEYPAD_C4_PORT_NUM           (Dio_PortType)0 /* PortA */
#define DioConf_KEYPAD_C3_PORT_NUM           (Dio_PortType)0 /* PORTA */
#define DioConf_KEYPAD_C2_PORT_NUM           (Dio_PortType)1 /* PortB */
#define DioConf_KEYPAD_C1_PORT_NUM           (Dio_PortType)1 /* PortB */

/** LCD **/
#define DioConf_LCD_D4_PORT_NUM              (Dio_PortType)1 /* PortB */
#define DioConf_LCD_D5_PORT_NUM              (Dio_PortType)1 /* PortB */
#define DioConf_LCD_D6_PORT_NUM              (Dio_PortType)0 /* PortA */
#define DioConf_LCD_D7_PORT_NUM              (Dio_PortType)0 /* PortA */

#define DioConf_LCD_EN_PORT_NUM              (Dio_PortType)1 /* PortB */
#define DioConf_LCD_RS_PORT_NUM              (Dio_PortType)1 /* PortB */


/* DIO Configured Channel ID's */ 

/** LED **/
#define DioConf_LED1_CHANNEL_NUM                (Dio_ChannelType)0      /* Pin 1 in PORTA */
#define DioConf_LED2_CHANNEL_NUM                (Dio_ChannelType)13     /* Pin 1 in PORTC */

/** Keypad **/
#define DioConf_KEYPAD_R4_CHANNEL_NUM           (Dio_ChannelType)0      /* PA0 NEW  */
#define DioConf_KEYPAD_R3_CHANNEL_NUM           (Dio_ChannelType)1      /* PA1 NEW  */
#define DioConf_KEYPAD_R2_CHANNEL_NUM           (Dio_ChannelType)2      /* PA2 NEW  */
#define DioConf_KEYPAD_R1_CHANNEL_NUM           (Dio_ChannelType)15     /* PC15 NEW  */
                                                                    
#define DioConf_KEYPAD_C4_CHANNEL_NUM           (Dio_ChannelType)5      /* PA5   */
#define DioConf_KEYPAD_C3_CHANNEL_NUM           (Dio_ChannelType)4      /* PA4   */
#define DioConf_KEYPAD_C2_CHANNEL_NUM           (Dio_ChannelType)11     /* PB11  */
#define DioConf_KEYPAD_C1_CHANNEL_NUM           (Dio_ChannelType)10     /* PB10  */

/** LCD **/
#define DioConf_LCD_D4_CHANNEL_NUM              (Dio_ChannelType)1      /* PINB1 */
#define DioConf_LCD_D5_CHANNEL_NUM              (Dio_ChannelType)0      /* PINB0 */
#define DioConf_LCD_D6_CHANNEL_NUM              (Dio_ChannelType)7      /* PINA7 */
#define DioConf_LCD_D7_CHANNEL_NUM              (Dio_ChannelType)6      /* PINA6 */
                                                                            
#define DioConf_LCD_EN_CHANNEL_NUM              (Dio_ChannelType)12     /* PINB12 */
#define DioConf_LCD_RS_CHANNEL_NUM              (Dio_ChannelType)13     /* PINB13 */

#endif /* DIO_CFG_H */