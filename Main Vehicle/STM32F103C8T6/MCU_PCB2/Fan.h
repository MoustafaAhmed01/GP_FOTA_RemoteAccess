/******************************************************************************
 *
 * Module: FAN
 *
 * File Name: FAN.h
 *
 * Description: Header file for STM32F103xx Microcontroller - FAN Driver
 *
 * Author: Esraa Ali
 ******************************************************************************/

#ifndef FAN_H
#define FAN_H

#include "Dio.h"
//#include "pwm.h"
#include "Std_Types.h"
#include "Port.h"
#include "GPT.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	STOP_FAN=0,LOW=30,MEDIUM=60,HIGH=100
}Fan_State;
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Set the FAN Port */
#define FAN_PORT_ID       DioConf_FAN_PORT_NUM
/* Set the FAN Pin Number */
#define FAN_PIN_1_ID      DioConf_FAN_CHANNEL_1_NUM
#define FAN_PIN_2_ID      DioConf_FAN_CHANNEL_2_NUM
/* Port Indicies */
#define FAN_PORT_PIN_1_ID_INDEX        PORTA_PIN_7
#define FAN_PORT_PIN_2_ID_INDEX        PORTA_PIN_6
/* Set the FAN ON/OFF according to its configuration Positive logic or negative logic */
#define FAN_ON  STD_HIGH
#define FAN_OFF STD_LOW

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Description : INITIALIZE FAN PIN */
/*******************************************************************************/
void Fan_init(void);
/*******************************************************************************/
/*Description : ROTATE FAN BY STATE OF FAN.*/
/*******************************************************************************/
void Fan_Rotate(Fan_State state,uint8 TIM_ID);
#endif /* FANOUT_H_ */
