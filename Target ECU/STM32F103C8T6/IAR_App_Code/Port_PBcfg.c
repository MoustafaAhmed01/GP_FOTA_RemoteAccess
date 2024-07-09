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
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

 Port_ConfigType Port_Configuration = {
                                             PORT_PORT_A , PORT_PIN_0,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,/* NEW KEYPAD R1 */
                                             PORT_PORT_A , PORT_PIN_1,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,/* NEW KEYPAD R2 */
                                             PORT_PORT_A , PORT_PIN_2,  PORT_PIN_IN, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_Changeable,/* UART2*/
                                             PORT_PORT_A , PORT_PIN_3,  PORT_PIN_IN, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_Changeable,/* UART2*/
                                             PORT_PORT_A , PORT_PIN_4,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* Keypad C2*/
                                             PORT_PORT_A , PORT_PIN_5,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* Keypad C1*/
                                             PORT_PORT_A , PORT_PIN_6,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* LCD */
                                             PORT_PORT_A , PORT_PIN_7,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* LCD */
                                             PORT_PORT_A , PORT_PIN_8,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_A , PORT_PIN_9,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable,
                                             PORT_PORT_A , PORT_PIN_10, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_Changeable ,Mode_Changeable,
                                             PORT_PORT_A , PORT_PIN_11, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_Changeable, /* Can Rx */
                                             PORT_PORT_A , PORT_PIN_12, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_Changeable, /* CAN Tx */
                                             PORT_PORT_A , PORT_PIN_15, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, 
                                                                                                                                                                                                                          
                                             PORT_PORT_B , PORT_PIN_0,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* LCD */
                                             PORT_PORT_B , PORT_PIN_1,  PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* lCD */
                                             PORT_PORT_B , PORT_PIN_3,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_B , PORT_PIN_4,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_B , PORT_PIN_5,  PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_B , PORT_PIN_6,  PORT_PIN_OUT,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_B , PORT_PIN_7,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_B , PORT_PIN_8,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_B , PORT_PIN_9,  PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_B , PORT_PIN_10, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* Keypad C4*/
                                             PORT_PORT_B , PORT_PIN_11, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* Keypad C3*/
                                             PORT_PORT_B , PORT_PIN_12, PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* LCD */
                                             PORT_PORT_B , PORT_PIN_13, PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* LCD */
                                             PORT_PORT_B , PORT_PIN_14, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_B , PORT_PIN_15, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                                                                                                                                                                                                         
                                             PORT_PORT_C , PORT_PIN_13, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_C , PORT_PIN_14, PORT_PIN_IN,  LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable,
                                             PORT_PORT_C , PORT_PIN_15, PORT_PIN_OUT, LEVEL_LOW, PORT_PIN_UNLOCKED, PORT_PIN_MODE_DIO , PORT_GP_PIN_PUSH_PULL, PORT_PIN_10MHz_SPEED ,PULL_DOWN ,Direction_UnChangeable ,Mode_UnChangeable, /* Keypad R4 */
                                        };

