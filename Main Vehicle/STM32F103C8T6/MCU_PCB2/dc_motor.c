/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: DC_MOTOR.h
 *
 * Description: Header file for STM32F103x8 Microcontroller - DC_MOTOR Driver
 *
 * Author: Esraa Ali
 ******************************************************************************/
#include "dc_motor.h"


/*********************************************************************************************/
/*Description : INITIALIZE DCMOTOR PIN */
/*********************************************************************************************/
 void DCMOTOR_init(void)
{
    Dio_WriteChannel(DioConf_DCMOTOR_1_CHANNEL_1_ID_INDEX, DCMOTOR_OFF);
    Dio_WriteChannel(DioConf_DCMOTOR_1_CHANNEL_2_ID_INDEX, DCMOTOR_OFF);
}
/*********************************************************************************************/
/*Description : ROTATE DCMOTOR BY STATE OF MOTOR AND ITS SPEED.*/
/*********************************************************************************************/
void DcMotor_Rotate(DcMotor_State state,uint16 speed,uint16 speed_limit,uint8 TIMx)
{ 
 /* if(speed == 0)
   {
   Dio_WriteChannel(DioConf_DCMOTOR_CHANNEL_1_ID_INDEX, DCMOTOR_OFF);
   Dio_WriteChannel(DioConf_DCMOTOR_CHANNEL_2_ID_INDEX, DCMOTOR_OFF);
  
  } */
  if (state == CW )                            /*WRITE STATE IN THE DC MOTOR PINS*/
  {
   Dio_WriteChannel(DioConf_DCMOTOR_1_CHANNEL_1_ID_INDEX, DCMOTOR_ON);
   Dio_WriteChannel(DioConf_DCMOTOR_1_CHANNEL_2_ID_INDEX, DCMOTOR_OFF);
  }
  else if(state == A_CW)
  {
   
   Dio_WriteChannel(DioConf_DCMOTOR_1_CHANNEL_1_ID_INDEX, DCMOTOR_OFF);
   Dio_WriteChannel(DioConf_DCMOTOR_1_CHANNEL_2_ID_INDEX, DCMOTOR_ON);
   
  }
  else 
  {
   Dio_WriteChannel(DioConf_DCMOTOR_1_CHANNEL_1_ID_INDEX, DCMOTOR_OFF);
   Dio_WriteChannel(DioConf_DCMOTOR_1_CHANNEL_2_ID_INDEX, DCMOTOR_OFF);
  
  }
     speed=((speed*100)/speed_limit); //in percentage
     TIM3_SetDuty(speed);

}

