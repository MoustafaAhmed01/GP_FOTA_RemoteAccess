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
#include "Fan.h"


/*********************************************************************************************/
/*Description : INITIALIZE FAN PIN */
/*********************************************************************************************/
 void Fan_init(void)
{
    /*
     *SET DIRECTION OF PINS
     */
    /*Port_SetPinDirection( FAN_PORT_PIN_1_ID_INDEX,PORT_PIN_OUT,PIN_PUSH_PULL,Default);
    Port_SetPinMode( FAN_PORT_PIN_1_ID_INDEX, PORT_PIN_MODE_DIO);
    Port_SetPinDirection( FAN_PORT_PIN_2_ID_INDEX,PORT_PIN_OUT,PIN_PUSH_PULL,Default);
    Port_SetPinMode( FAN_PORT_PIN_2_ID_INDEX, PORT_PIN_MODE_DIO);*/
    /*
     *INTIALIZE PINS AS STOP STATE
     */
    Dio_WriteChannel(DioConf_FAN_CHANNEL_1_ID_INDEX, FAN_OFF);
}
/*********************************************************************************************/
/*Description : ROTATE FAN BY STATE OF FAN .*/
/*********************************************************************************************/
void Fan_Rotate(Fan_State state,uint8 TIM_ID)
{
  switch(state)
  {
  case STOP_FAN:GPT_SET_DUTY_CYCLE(TIM_ID,STOP_FAN);                 /*CALCULATE DUTY CYCLE*/
            Dio_WriteChannel(DioConf_FAN_CHANNEL_1_ID_INDEX, FAN_OFF);
            break;
  case LOW:GPT_SET_DUTY_CYCLE(TIM_ID,LOW);                 /*CALCULATE DUTY CYCLE*/
           Dio_WriteChannel(DioConf_FAN_CHANNEL_1_ID_INDEX, FAN_OFF);
           break;
  case MEDIUM:GPT_SET_DUTY_CYCLE(TIM_ID,MEDIUM);                 /*CALCULATE DUTY CYCLE*/
              Dio_WriteChannel(DioConf_FAN_CHANNEL_1_ID_INDEX, FAN_OFF);
              break;
  case HIGH:GPT_SET_DUTY_CYCLE(TIM_ID,HIGH);                 /*CALCULATE DUTY CYCLE*/
            Dio_WriteChannel(DioConf_FAN_CHANNEL_1_ID_INDEX, FAN_OFF);
            break;
  }
  

}
