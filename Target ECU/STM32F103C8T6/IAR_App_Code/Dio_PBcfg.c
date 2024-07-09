 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_PBcfg.c
 *
 * Description: Post Build Configuration Source file for STM32F103C8T6 Microcontroller - Dio Driver
 *
 * Author: Moustafa Ahmed
 ******************************************************************************/

#include "Dio.h"

/*
 * Module Version 1.0.0
 */
#define DIO_PBCFG_SW_MAJOR_VERSION              (1U)
#define DIO_PBCFG_SW_MINOR_VERSION              (0U)
#define DIO_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Dio_Init API */
   const Dio_ConfigType Dio_Configuration = {
                                              DioConf_LED1_PORT_NUM, DioConf_LED1_CHANNEL_NUM,
                                              DioConf_LED2_PORT_NUM, DioConf_LED2_CHANNEL_NUM,
                                              DioConf_KEYPAD_R1_PORT_NUM,DioConf_KEYPAD_R1_CHANNEL_NUM,
                                              DioConf_KEYPAD_R2_PORT_NUM,DioConf_KEYPAD_R2_CHANNEL_NUM,
                                              DioConf_KEYPAD_R3_PORT_NUM,DioConf_KEYPAD_R3_CHANNEL_NUM,
                                              DioConf_KEYPAD_R4_PORT_NUM,DioConf_KEYPAD_R4_CHANNEL_NUM,
                                              DioConf_KEYPAD_C1_PORT_NUM,DioConf_KEYPAD_C1_CHANNEL_NUM,
                                              DioConf_KEYPAD_C2_PORT_NUM,DioConf_KEYPAD_C2_CHANNEL_NUM,
                                              DioConf_KEYPAD_C3_PORT_NUM,DioConf_KEYPAD_C3_CHANNEL_NUM,
                                              DioConf_KEYPAD_C4_PORT_NUM,DioConf_KEYPAD_C4_CHANNEL_NUM,
                                              DioConf_LCD_D4_PORT_NUM,DioConf_LCD_D4_CHANNEL_NUM,
                                              DioConf_LCD_D5_PORT_NUM,DioConf_LCD_D5_CHANNEL_NUM,
                                              DioConf_LCD_D6_PORT_NUM,DioConf_LCD_D6_CHANNEL_NUM,
                                              DioConf_LCD_D7_PORT_NUM,DioConf_LCD_D7_CHANNEL_NUM,
                                              DioConf_LCD_EN_PORT_NUM,DioConf_LCD_EN_CHANNEL_NUM,
                                              DioConf_LCD_RS_PORT_NUM,DioConf_LCD_RS_CHANNEL_NUM,
};
