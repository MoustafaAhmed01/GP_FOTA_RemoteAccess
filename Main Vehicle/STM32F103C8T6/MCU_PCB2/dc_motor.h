/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: DC_MOTOR.h
 *
 * Description: Header file for STM32F103xx Microcontroller - DC_MOTOR Driver
 *
 * Author: Esraa Ali
 ******************************************************************************/

#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include "Dio.h"
#include "Std_Types.h"
#include "Port.h"
#include "TIM8_PWM.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	STOP,A_CW,CW
}DcMotor_State;
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Set the DCMOTOR Port */
#define DCMOTOR_PORT_ID       DioConf_DC_MOTOR_PORT_NUM
/* Set the DCMOTOR Pin Number */
#define DCMOTOR_PIN_1_ID      DioConf_DC_MOTOR_CHANNEL_1_NUM
#define DCMOTOR_PIN_2_ID      DioConf_DC_MOTOR_CHANNEL_2_NUM
/* Port Indicies */
#define DCMOTOR_PORT_PIN_1_ID_INDEX        PORTA_PIN_2
#define DCMOTOR_PORT_PIN_2_ID_INDEX        PORTA_PIN_3
/* Set the DCMOTOR ON/OFF according to its configuration Positive logic or negative logic */
#define DCMOTOR_ON  STD_HIGH
#define DCMOTOR_OFF STD_LOW
//#define TIM_X   2
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Description : INITIALIZE DCMOTOR PIN */
/*******************************************************************************/
void DCMOTOR_init(void);
/*******************************************************************************/
/*Description : ROTATE DCMOTOR BY STATE OF MOTOR AND ITS SPEED.*/
/*******************************************************************************/
void DcMotor_Rotate(DcMotor_State state,uint16 speed,uint16 speed_limit,uint8 TIMx);
#endif /* DC_MOTOR_H_ */
