/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for STM32F401RCT6 Microcontroller - Port Driver
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)


/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION)) //PORT_AF_PIN_PUSH_PULL
  #error "The SW version of PBcfg.c does not match the expected version"
#endif
//A15,B4 Not CONNECTED
//7 leds : PB3[Head light 1],[PB5,PB6,PB7]AC,PB10[Headlight 2],PB14[BUZZER],PB9(ENGINE)OnBoard,[PA2 emergency,PA3 Headlight] PUSH BUTTONS,PB15[Emergency LED],PC13[PUSH BUTTON FOR START/STOP ENGINE]
 Port_ConfigType Port_Configuration = {
                                             PORT_PORT_A , PORT_PIN_0,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_ANALOG , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable, /*Pot1*/
                                             PORT_PORT_A , PORT_PIN_1,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_ANALOG , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable, /*Pot2*/
                                             PORT_PORT_A , PORT_PIN_2,  PORT_PIN_IN, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable,/* PUSH BUTTON FOR EMERGENCY*/
                                             PORT_PORT_A , PORT_PIN_3,  PORT_PIN_IN, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable,/* PUSH BUTTON FOR CAR HEADLIGHTS*/
                                             PORT_PORT_A , PORT_PIN_4,  PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN   ,Direction_Changeable ,Mode_Changeable, /*DC Motor1*/
                                             PORT_PORT_A , PORT_PIN_5,  PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN  ,Direction_Changeable ,Mode_Changeable, /*DC Motor1*/
                                             PORT_PORT_A , PORT_PIN_6,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable, /* Motor_2 */
                                             PORT_PORT_A , PORT_PIN_7,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable, /* Motor_2 */
                                             PORT_PORT_A , PORT_PIN_8,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_FUNC_ALT_PWM , PORT_AF_PIN_PUSH_PULL, PORT_PIN_50MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable,  /*SERVO_Motor PWM signal*/
                                             PORT_PORT_A , PORT_PIN_9,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_Changeable,/*UART1*/
                                             PORT_PORT_A , PORT_PIN_10, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_Changeable,/*UART1*/
                                             PORT_PORT_A , PORT_PIN_11, PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,/* lcd D4*/
                                             PORT_PORT_A , PORT_PIN_12, PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,/* lcd D5*/
                                             PORT_PORT_A , PORT_PIN_15, PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable,  /*NC*/ 
                                                                                                                                                                                                                          
                                             PORT_PORT_B , PORT_PIN_0,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_FUNC_ALT_PWM , PORT_AF_PIN_PUSH_PULL, PORT_PIN_50MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable,  /*DC_Motor1 PWM signal*/
                                             PORT_PORT_B , PORT_PIN_1,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_AF_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable, /*DC_Motor2 PWM signal*/
                                             PORT_PORT_B , PORT_PIN_3,  PORT_PIN_OUT, LEVEL_HIGH, PORT_PIN_UNLOCKED,PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable, /*Headlights 1*/ 
                                             PORT_PORT_B , PORT_PIN_4,  PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_UnChangeable, /*NC*/
                                             PORT_PORT_B , PORT_PIN_5,  PORT_PIN_OUT,  LEVEL_HIGH, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_UnChangeable,  /*LED1*/ //AC LED
                                             PORT_PORT_B , PORT_PIN_6,  PORT_PIN_OUT,  LEVEL_HIGH, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,/*LED2*/ //AC LED
                                             PORT_PORT_B , PORT_PIN_7,  PORT_PIN_OUT,  LEVEL_HIGH, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,/*LED3*/ //AC LED
                                             PORT_PORT_B , PORT_PIN_8,  PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* fan */
                                             PORT_PORT_B , PORT_PIN_9,  PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /*Engine LED*/
                                             PORT_PORT_B , PORT_PIN_10, PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /*HEADLIGHTS 2*/
                                             PORT_PORT_B , PORT_PIN_12, PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* lcd EN */
                                             PORT_PORT_B , PORT_PIN_13, PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* lcd RS*/
                                             PORT_PORT_B , PORT_PIN_14, PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable, /* Buzzer*/
                                             PORT_PORT_B , PORT_PIN_15, PORT_PIN_OUT,  LEVEL_HIGH, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /*Emergency LED*/
                                                                                                                                                                                                                         
                                             PORT_PORT_C , PORT_PIN_13, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,/* PUSH BUTTON FOR START/STOP ENGINE*/ 
                                             PORT_PORT_C , PORT_PIN_14, PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,// LCD D7
                                             PORT_PORT_C , PORT_PIN_15, PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,// LCD D6
                                        };

