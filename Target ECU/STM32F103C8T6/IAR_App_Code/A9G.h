/***************************************************************************************************************************************************
* Author: Shady Alaa ~ GP 2024
* 
* File name : A9G.h
*
* Description : Implementation of A9G H-file to interface with stm32f103c8t6-Bluepill
*
*                                                         *Latest version is on 4/16/2024** 
***************************************************************************************************************************************************/
#include "DMA.h"
#include "Delay.h"
#include "UART2.h"
#include "Platform_Types.h"
#include "sys_timer.h"
#include "LCD.h"
#include "UART_Regs.h"  
#define  GPS_TOPIC                    0
#define  SPEED_TOPIC                  1
#define  CHECK_ENGINE                 2
#define  EMERGENCY_CALL               3
#define  ACCEPTED                     1
#define  NOT_ACCEPTED                 0
#define  DATA_SIZE                    500
#define  MILLISECONDS                 71999
#define  ENABLED                      1
#define  DISABLED                     0
#define  DOOR_CTRL                    0
#define  AC_STATE                     1
#define  AC_LEVEL                     2
#define  SPEED_LIMIT                  3
extern uint8 data[DATA_SIZE];
extern uint8 Limiter_State_Cmd[60];
extern uint8 Speed_Limit_Cmd[60];
extern uint8 Car_Speed_Cmd[60];
extern uint8 AC_Level_Cmd[60];
extern uint8 AC_State_Cmd[60];
extern uint8 Door_Ctrl_Cmd[60];
extern uint8 Emergency_State_Cmd[50];
extern uint8 Car_Engine_Cmd[50];
extern uint8 Emergency_State_Flag;
extern uint8 Car_Engine_Flag;
extern uint8 Limiter_State_Flag;
extern uint8 AC_State_Flag;
extern uint8 AC_Level_Flag;
extern uint8 Door_Control_Flag;
extern uint8 Speed_Limit_Flag;
extern uint8 Car_Engine_ACK;
boolean A9G_Init();
boolean A9GtoNetwork();
boolean A9G_Brokerconnect();
boolean A9G_CheckEngine();
void A9G_MQTTread( uint8 *response);
void A9G_PublishSpeed(uint8 *speed);
void A9G_PublishGPS(void);
void A9G_PublishEmergency(uint8 *state);
void A9G_PublishEngine(uint8 *state);
void A9G_GPS();
void A9G_EmergencyActs();
void A9G_GPS_OFF(void);
void Str_Cat(uint8 *str1,uint8 *str2,uint8 *dest);
boolean response_compare(const uint8 *str1 ,const uint8 *str2,const uint8 size);
