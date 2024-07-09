/******************************************************************************
 *
 * Module: Servo motor [SG90 Micro_Servo Motor]
 *
 * File Name: servo_motor.c
 *
 * Description: source file for STM32F103xx Microcontroller - SG90 Motor Driver
 *
 * Author: Shady Alaa ~ FOTA Team
 ******************************************************************************/
#include "servo_motor.h"
/****************************************************************************
* Function Name: Servo_Rotate
* -Calls GPT_SET_DUTY_CYCLE Function to adjust position.
* -It takes Angle position in Degrees and returns nothing.
***************************************************************************/

void Servo_Rotate(uint8 angle)
{
  

   if (angle == 90)
  { 
    
   TIM1_SetDuty(2000);
 
  }
  else if(angle == 180)
  {  
   
   TIM1_SetDuty(1000);


  }
  else if(angle == 0)
  {
       TIM1_SetDuty(1500);
 

  }
  else
  {
    /*do nothing*/
  }
}
/*********************************************************************************************************
* Function Name: duty_cycleCalculate
* 
* -It takes pulse width , Period of Timer that generates pwm signal and returns Duty cycle in percent
**********************************************************************************************************/

