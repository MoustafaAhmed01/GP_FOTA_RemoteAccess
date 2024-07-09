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
                                              DioConf_DC_MOTOR_1_PORT_NUM,DioConf_DC_MOTOR_1_CHANNEL_1_NUM,
                                              DioConf_DC_MOTOR_1_PORT_NUM,DioConf_DC_MOTOR_1_CHANNEL_2_NUM,
                                              DioConf_DC_MOTOR_2_PORT_NUM,DioConf_DC_MOTOR_2_CHANNEL_1_NUM,
                                              DioConf_DC_MOTOR_2_PORT_NUM,DioConf_DC_MOTOR_2_CHANNEL_2_NUM,
                                              DioConf_LCD_D4_PORT_NUM,DioConf_LCD_D4_CHANNEL_NUM,
                                              DioConf_LCD_D5_PORT_NUM,DioConf_LCD_D5_CHANNEL_NUM,
                                              DioConf_LCD_D6_PORT_NUM,DioConf_LCD_D6_CHANNEL_NUM,
                                              DioConf_LCD_D7_PORT_NUM,DioConf_LCD_D7_CHANNEL_NUM,
                                              DioConf_LCD_EN_PORT_NUM,DioConf_LCD_EN_CHANNEL_NUM,
                                              DioConf_LCD_RS_PORT_NUM,DioConf_LCD_RS_CHANNEL_NUM,
                                              DioConf_COLD_PORT_NUM, DioConf_COLD_CHANNEL_NUM,   //AC LEDS //blue
                                              DioConf_MED_PORT_NUM, DioConf_MED_CHANNEL_NUM,             //yellow
                                              DioConf_HOT_PORT_NUM, DioConf_HOT_CHANNEL_NUM,             //red
                                              DioConf_HL1_PORT_NUM, DioConf_HL1_CHANNEL_NUM,
                                              DioConf_HL2_PORT_NUM, DioConf_HL2_CHANNEL_NUM,
                                              DioConf_ENGINE_PORT_NUM, DioConf_ENGINE_CHANNEL_NUM,
                                              DioConf_EMERGENCY_PORT_NUM, DioConf_EMERGENCY_CHANNEL_NUM,
                                              DioConf_FAN_PORT_NUM,DioConf_FAN_CHANNEL_1_NUM,
                                              DioConf_HLPB_PORT_NUM,DioConf_HLPB_CHANNEL_NUM,
                                              DioConf_ENGINEPB_PORT_NUM,DioConf_ENGINEPB_CHANNEL_NUM,
                                              DioConf_EMERGENCYPB_PORT_NUM,DioConf_EMERGENCYPB_CHANNEL_NUM,
                                              DioConf_BUZZER_PORT_NUM,DioConf_BUZZER_CHANNEL_NUM,
};
