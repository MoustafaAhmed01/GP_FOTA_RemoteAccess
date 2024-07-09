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
#define DIO_CONFIGURED_CHANNLES                 (30U)
/* Channel Index in the array of structures in Dio_PBcfg.c */
/**DCMOTOR1**/
#define DioConf_DCMOTOR_1_CHANNEL_1_ID_INDEX         (uint8)0                 
#define DioConf_DCMOTOR_1_CHANNEL_2_ID_INDEX         (uint8)1
/**DCMOTOR2**/
#define DioConf_DCMOTOR_2_CHANNEL_1_ID_INDEX         (uint8)2                 
#define DioConf_DCMOTOR_2_CHANNEL_2_ID_INDEX         (uint8)3


/** lCD **/

#define DioConf_LCD_D4_CHANNEL_ID_INDEX             (uint8)4                      /* LCD D4 */
#define DioConf_LCD_D5_CHANNEL_ID_INDEX             (uint8)5                      /* LCD D5 */
#define DioConf_LCD_D6_CHANNEL_ID_INDEX             (uint8)6                      /* LCD D6 */
#define DioConf_LCD_D7_CHANNEL_ID_INDEX             (uint8)7                      /* LCD D7 */
#define DioConf_LCD_EN_CHANNEL_ID_INDEX             (uint8)8                      /* LCD EN */
#define DioConf_LCD_RS_CHANNEL_ID_INDEX             (uint8)9                      /* LCD RS */
/** LED **/
//AC LEDS   
#define DioConf_COLD_CHANNEL_ID_INDEX               (uint8)10
#define DioConf_MED_CHANNEL_ID_INDEX               (uint8)11
#define DioConf_HOT_CHANNEL_ID_INDEX               (uint8)12
//CAR HEADLIGHTS
#define DioConf_HL1_CHANNEL_ID_INDEX               (uint8)13
#define DioConf_HL2_CHANNEL_ID_INDEX               (uint8)14
//START/STOP ENGINE
#define DioConf_ENGINE_CHANNEL_ID_INDEX               (uint8)15  
//EMERGENCY
#define DioConf_EMERGENCY_CHANNEL_ID_INDEX               (uint8)16
/**FAN**/
#define DioConf_FAN_CHANNEL_1_ID_INDEX              (uint8)17
/**PUSH BUTTON**/
#define DioConf_HLPB_CHANNEL_ID_INDEX        (uint8)18   //CAR HEADLIGHTS
#define DioConf_ENGINEPB_CHANNEL_ID_INDEX        (uint8)19   //START/STOP ENGINE
#define DioConf_EMERGENCYPB_CHANNEL_ID_INDEX        (uint8)20   //EMERGENCY
/**BUZZER**/ 
#define DioConf_BUZZER_CHANNEL_ID_INDEX              (uint8)21 
/* DIO Configured Port ID's */

/**DCMOTOR1**/
#define DioConf_DC_MOTOR_1_PORT_NUM          (Dio_PortType)0 /* PortA */
/**DCMOTOR2**/
#define DioConf_DC_MOTOR_2_PORT_NUM          (Dio_PortType)0 /* PortA */

/**LED**/
//AC LEDS
#define DioConf_COLD_PORT_NUM                (Dio_PortType)1 /*PORTB5*/
#define DioConf_MED_PORT_NUM                (Dio_PortType)1 /*PORTB6*/
#define DioConf_HOT_PORT_NUM                (Dio_PortType)1 /*PORTB7*/
//CAR HEADLIGHTS
#define DioConf_HL1_PORT_NUM                (Dio_PortType)1 /*PORTB3*/
#define DioConf_HL2_PORT_NUM                (Dio_PortType)1 /*PORTB10*/
//START/STOP ENGINE
#define DioConf_ENGINE_PORT_NUM                (Dio_PortType)1 /*PORTB9*/
//EMERGENCY
#define DioConf_EMERGENCY_PORT_NUM                (Dio_PortType)1 /*PORTB15*/   
   
/**FAN**/
#define DioConf_FAN_PORT_NUM                 (Dio_PortType)1 /* PortB */

/**PUSH BUTTON**/
#define DioConf_HLPB_PORT_NUM               (Dio_PortType)0 /* PortA3 */  //CAR HEADLIGHTS
#define DioConf_ENGINEPB_PORT_NUM               (Dio_PortType)2 /* PortC13 */  //START/STOP ENGINE
#define DioConf_EMERGENCYPB_PORT_NUM               (Dio_PortType)0 /* PortA2 */  //EMERGENCY

/**BUZZER**/ 
#define DioConf_BUZZER_PORT_NUM              (Dio_PortType)1 /* PortB14 */
   
/** LCD **/
#define DioConf_LCD_D4_PORT_NUM              (Dio_PortType)0 /* PortA11 */
#define DioConf_LCD_D5_PORT_NUM              (Dio_PortType)0 /* PortA12 */
#define DioConf_LCD_D6_PORT_NUM              (Dio_PortType)2 /* PortC14 */
#define DioConf_LCD_D7_PORT_NUM              (Dio_PortType)2 /* PortC15 */
#define DioConf_LCD_EN_PORT_NUM              (Dio_PortType)1 /* PortB12 */
#define DioConf_LCD_RS_PORT_NUM              (Dio_PortType)1 /* PortB13 */

/**DCMOTOR1**/
#define DioConf_DC_MOTOR_1_CHANNEL_1_NUM          (Dio_ChannelType)4     /* PINA4 */
#define DioConf_DC_MOTOR_1_CHANNEL_2_NUM          (Dio_ChannelType)5     /* PINA5 */

/**DCMOTOR2**/
#define DioConf_DC_MOTOR_2_CHANNEL_1_NUM          (Dio_ChannelType)6     /* PINA6 */
#define DioConf_DC_MOTOR_2_CHANNEL_2_NUM          (Dio_ChannelType)7     /* PINA7 */

/** LCD **/
#define DioConf_LCD_D4_CHANNEL_NUM              (Dio_ChannelType)11      /* PINA11 */
#define DioConf_LCD_D5_CHANNEL_NUM              (Dio_ChannelType)12      /* PINA12 */
#define DioConf_LCD_D6_CHANNEL_NUM              (Dio_ChannelType)15      /* PINC14 */
#define DioConf_LCD_D7_CHANNEL_NUM              (Dio_ChannelType)14      /* PINC15 */
                                                                            
#define DioConf_LCD_EN_CHANNEL_NUM              (Dio_ChannelType)12     /* PINB12 */
#define DioConf_LCD_RS_CHANNEL_NUM              (Dio_ChannelType)13     /* PINB13 */

/**FAN**/
#define DioConf_FAN_CHANNEL_1_NUM               (Dio_ChannelType)8      /* PINB8 */
/**LED**/
//AC LEDS
#define DioConf_COLD_CHANNEL_NUM                (Dio_ChannelType)5 /* Pin 5 in PORTB */  //blue
#define DioConf_MED_CHANNEL_NUM                (Dio_ChannelType)6 /* Pin 6 in PORTB */  //yellow
#define DioConf_HOT_CHANNEL_NUM                (Dio_ChannelType)7 /* Pin 7 in PORTB */  //red
//CAR HEADLIGHTS
#define DioConf_HL1_CHANNEL_NUM                 (Dio_ChannelType)3 /* Pin 3 in PORTB */
#define DioConf_HL2_CHANNEL_NUM                 (Dio_ChannelType)10 /* Pin 10 in PORTB */
//START/STOP ENGINE
#define DioConf_ENGINE_CHANNEL_NUM                 (Dio_ChannelType)9 /* Pin 9 in PORTB */
//EMERGENCY
#define DioConf_EMERGENCY_CHANNEL_NUM                 (Dio_ChannelType)15 /* Pin 15 in PORTB */   
/**PUSH BUTTON**/
#define DioConf_HLPB_CHANNEL_NUM             (Dio_ChannelType)3 /* Pin 3 */
#define DioConf_ENGINEPB_CHANNEL_NUM             (Dio_ChannelType)13 /* Pin 13 */
#define DioConf_EMERGENCYPB_CHANNEL_NUM             (Dio_ChannelType)2 /* Pin 2 */
/**BUZZER**/ 
#define DioConf_BUZZER_CHANNEL_NUM               (Dio_ChannelType)14 /* Pin 14 */
   
#endif /* DIO_CFG_H */
