/******************************************************************************
 *
 * Module: Servo motor [SG90 Micro_Servo Motor]
 *
 * File Name: servo_motor.h
 *
 * Description: Header file for STM32F103xx Microcontroller - SG90 Motor Driver
 *
 * Author: Shady Alaa ~ FOTA Team
 ******************************************************************************/


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

#include "TIM8_PWM.h"
#define PWM_PERIOD      20    /*For a PWM 50Hz input--> 20msec period*/
#define POS_ZERO        1500 /*taken from datasheet of SG90*/
#define POS_NORMAL      2000    /*taken from datasheet of SG90*/
#define POS_FLIP        1000    /*taken from datasheet of SG90*/
void Servo_Rotate(uint8 angle);


#endif