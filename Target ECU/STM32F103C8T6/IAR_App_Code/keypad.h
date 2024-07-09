/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: keypad.h
 *
 * Description: types for ARM STM32F103C8T6
 *
 * Date Created: 11/9/2023
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/**-------------------------INCLUDES Section------------------------**/
#include "Std_Types.h"

/**-------------------------Definitions & Config Section------------**/


/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW1_PORT_ID                DioConf_KEYPAD_R1_PORT_NUM
#define KEYPAD_ROW2_PORT_ID                DioConf_KEYPAD_R2_PORT_NUM
#define KEYPAD_ROW3_PORT_ID                DioConf_KEYPAD_R3_PORT_NUM
#define KEYPAD_ROW4_PORT_ID                DioConf_KEYPAD_R4_PORT_NUM
                                                             
#define KEYPAD_COL1_PORT_ID                DioConf_KEYPAD_C1_PORT_NUM
#define KEYPAD_COL2_PORT_ID                DioConf_KEYPAD_C2_PORT_NUM
#define KEYPAD_COL3_PORT_ID                DioConf_KEYPAD_C3_PORT_NUM
#define KEYPAD_COL4_PORT_ID                DioConf_KEYPAD_C4_PORT_NUM

/* Keypad Channel Configuations */

#define KEYPAD_ROW1_PIN_ID                DioConf_KEYPAD_R1_CHANNEL_NUM
#define KEYPAD_ROW2_PIN_ID                DioConf_KEYPAD_R2_CHANNEL_NUM
#define KEYPAD_ROW3_PIN_ID                DioConf_KEYPAD_R3_CHANNEL_NUM
#define KEYPAD_ROW4_PIN_ID                DioConf_KEYPAD_R4_CHANNEL_NUM
                                                        
#define KEYPAD_COL1_PIN_ID                DioConf_KEYPAD_C1_CHANNEL_NUM
#define KEYPAD_COL2_PIN_ID                DioConf_KEYPAD_C2_CHANNEL_NUM
#define KEYPAD_COL3_PIN_ID                DioConf_KEYPAD_C3_CHANNEL_NUM
#define KEYPAD_COL4_PIN_ID                DioConf_KEYPAD_C4_CHANNEL_NUM

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

   /* Port Indicies */
#define KEYPAD_ROW1_PORT_ID_INDEX        PORTA_PIN_0 /* NEW */
#define KEYPAD_ROW2_PORT_ID_INDEX        PORTB_PIN_1 /* NEW */
#define KEYPAD_ROW3_PORT_ID_INDEX        PORTB_PIN_2 /* NEW */
#define KEYPAD_ROW4_PORT_ID_INDEX        PORTB_PIN_5 /* OLD */

#define KEYPAD_COL1_PORT_ID_INDEX        PORTA_PIN_5
#define KEYPAD_COL2_PORT_ID_INDEX        PORTA_PIN_4
#define KEYPAD_COL3_PORT_ID_INDEX        PORTB_PIN_11
#define KEYPAD_COL4_PORT_ID_INDEX        PORTB_PIN_10   
/**-------------------------Function Dec. Section-------------------**/
/* Public functions prototypes: */
uint8 Keypad_getPressedKey();

/**---------------------------------END-----------------------------**/

#endif /* KEYPAD_H_ */
