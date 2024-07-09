/***************************************************************************************************************************************************
* Author: Shady Alaa ~ GP 2024
* 
* File name : A9G.c
*
* Description : Implementation of A9G Src-file to interface with stm32f103c8t6-Bluepill
*
*                                                      **Latest version is on 4/17/2024** 
***************************************************************************************************************************************************/
/**********************************************Header File Include*******************************************************/
#include "A9G.h"
#include "DMA.h"
uint8 count=1;
/***********************************************Global Variables********************************************************/
uint8 gps_buffer[100]={0};
uint8 check_Res=NOT_ACCEPTED;
volatile uint8 Stop_Flag=0;
volatile uint8 wait_flag=1;
extern uint8 ix;
extern uint8 iy;
//extern uint8 reset_flag;
uint8 GPS_Flag=0;
/***********************************************STATIC Functions*******************************************************/
STATIC void A9G_Sendcmd(const uint8 *cmd,uint32 response_delay);
// void A9G_MQTTread( uint8 *response);
volatile  void A9G_SystickHandler();
//void A9G_DMA1Handler();
//STATIC void A9G_DisableEcho();
STATIC uint8 A9G_checkResponse(uint8 *cmd);
//STATIC void A9G_ERRORmessage();
STATIC void A9G_getTopicData(uint8 *response);
STATIC boolean A9G_Subscribe();
STATIC boolean NMEAtoGPS(uint8 *NMEA_Out ,uint8 *Location);
STATIC void Data_Ready(uint8 Data);
STATIC void resetBuffer(uint8 *buffer_start);
STATIC void resetNMEA(uint8 *buff,uint8 size);
/*************************************************Helpful Functions****************************************************/
//STATIC void reset_dataarr(uint8 *data,uint8 data_size);
STATIC void insert_string(uint8 *str,uint8 start,uint8 *sub_str);
STATIC void get_string(uint8 *str,uint8 *sub_str,uint8 start_char,uint8 end_char);
STATIC void get_strFromEnd(uint8 *str,uint8 start_char,uint8 *sub_str);
STATIC void strCPY(uint8 *source,uint8 *dest);
STATIC void convertToMaps(uint8 *str);
STATIC void strConnect(uint8 *src1 ,uint8 *src2,uint8 *dest);
/*********************************************************************************************************************/
volatile void A9G_SystickHandler()
{
  Stop_Flag=1;
  
}
/********************************************************************************************************************
* Function Name : A9G_Init
* Return value  : Void
*Description    :Wait for A9G to start up, then we check that everything is OK by passing AT command 
                ;if OK received we Disable Echo Mode.

*********************************************************************************************************************/
boolean A9G_Init()
{
  if(BKP_DR3== 0x0000)
  {
 CLEAR_BIT( USART_2_CR1_REG , RXNEIE );
 SysTick_delay(26000);
 SET_BIT( USART_2_CR1_REG , RXNEIE );

 A9G_Sendcmd("ATE0\r\n",60);
 check_Res=A9G_checkResponse("ATE0\r\n");
 if(check_Res)
 { 
  A9G_Sendcmd("AT\r\n",60);
  check_Res=A9G_checkResponse("AT\r\n");
  if(check_Res){
 LCD_clearScreen();
 LCD_displayStringRowColumn(1,0,"Initialized");
 LCD_displayStringRowColumn(0,0,"Successfully");
 Delay_MS(1000);
 return TRUE;
  }
  else
  {
     LCD_clearScreen();
     LCD_displayString("Init Failed");
     LCD_displayStringRowColumn(1,0,"Reboot");
     Delay_MS(1000);
     return FALSE;
  }
 }
  else{
     LCD_clearScreen();
     LCD_displayString("Init Failed");
     LCD_displayStringRowColumn(1,0,"Reboot");
     Delay_MS(1000);
     return FALSE;
  }
    
  }
  else
  {
    return TRUE;
  }
}
/********************************************************************************************************************
* Function Name : A9G_DisableEcho
* Return value  : Void
*Description    :Switching Off Echo Mode to reduce delay and facilitate process of checking on received data .

*********************************************************************************************************************/
//STATIC void A9G_DisableEcho()
//{
//  
//  A9G_Sendcmd("ATE0\r\n",40);
//  check_Res=A9G_checkResponse("ATE0\r\n");
//  switch(check_Res)
//  {
//  case NOT_ACCEPTED : A9G_Sendcmd("ERROR",40);
//               break;
//  case ACCEPTED  : break; /*Do nothing*/
//  
//  }
//
//  
//}
/********************************************************************************************************************
* Function Name : A9G_ERRORmessage
* Return value  : Void
*Description    :Enabling Echo Mode to Receive what i send to the A9G module so if Error Occured i send and
                 receive ERROR which is helpful to take action then.

*********************************************************************************************************************/
//STATIC void A9G_ERRORmessage(uint8 *cmd)
// {
//              A9G_Sendcmd("ATE1\r\n",20);
//              check_Res=A9G_checkResponse("ATE1\r\n");
//                if(check_Res)
//                {
//                          
//                    A9G_Sendcmd("ERROR\r\n",20);
//                }
//            
// }
/********************************************************************************************************************
* Function Name : A9G_Sendcmd
* Return value  : Void
*Description    :Sending AT commands and Receiving response to and from A9G via UART and storing received data in
                 static array of characters called data.  

*********************************************************************************************************************/

STATIC void A9G_Sendcmd(const uint8 *cmd,uint32 response_delay)
{    ix=0;
  
    if(response_compare(cmd,"ERROR",5))
      {
        for(uint8 i=0;i<5;i++)
        {
          data[i]=cmd[i];
        }
        data[5]='\0';
   }
else  {
    
      uint8 count=0;
      SysTick_SetCallBack(A9G_SystickHandler);   /*Pointer to function points to handler which stop waiting for response*/
      UART2_sendString(cmd);     
      SysTick_Init(&Systick_Configurations,response_delay*MILLISECONDS);     
      while(Stop_Flag==0)
      {
//       data[count]=UART_recieveByte();
//        break;
        count++;
      }
      SysTick_DeInit();
      count =0;
      Stop_Flag=0;
     
      }  
 
}


/********************************************************************************************************************
* Function Name : A9G_checkResponse
* Return value  : un-signed integer of 1 byte [received_is].
*Description    : Casually checking on response received from A9G and make decision to prevent any unintended errors.

*********************************************************************************************************************/
STATIC uint8 A9G_checkResponse(uint8* cmd)
{
    uint8 received_is=NOT_ACCEPTED;
   
    if((response_compare(cmd , "AT\r\n",4))   || (response_compare(cmd , "ATE1\r\n",6)) 
       ||   (response_compare(cmd ,"AT+CGACT=1\r\n",12))|| (response_compare(cmd , "AT+CREG=1\r\n",11))
       ||   (response_compare(cmd,"AT+MQTTCONN=",12))   ||(response_compare( cmd,"AT+CMGF=0\r\n",11))
       ||   (response_compare( cmd,"ATD+201006425048\r\n",18)) ||(response_compare( cmd,"AT+CMGF=1\r\n",11)))

    {
    if(response_compare(data , "\r\nOK\r\n",6) || response_compare(data, "\r\n\r\nOK\r\n",8) ||  response_compare(data, "\r\n\r\nOK\r\n\r\n",10))
    {
      received_is=ACCEPTED;     
    }
    else
    {
      received_is=NOT_ACCEPTED;
    }
    }
    else if ((response_compare(cmd,"AT+MQTTSUB=",11)))
    {
      if(response_compare(data , "\r\nOK\r\n",6)       || response_compare(data,"\r\n+MQTTPUBLISH:",14)
         || response_compare(data, "\r\n\r\nOK\r\n",8) || response_compare(data,"+MQTTPUBLISH:",12)
         ||  response_compare(data, "\r\n\r\nOK\r\n\r\n",10) ||  response_compare(data,"\r\n\r\n+MQTTPUBLISH:",16))
     {
      received_is=ACCEPTED;    
     }
      else
     {
       received_is=NOT_ACCEPTED;
     }
    }
    else if(response_compare(cmd,"AT+CGATT=1\r\n",12))
    {
      if(response_compare(data,"\r\n+CGATT:1\r\n\r\nOK\r\n",18) || response_compare(data,"\r\n\r\n+CGATT:1\r\n\r\nOK\r\n",20) 
                                                                || response_compare(data,"\r\n\r\n+CGATT:1\r\n\r\nOK\r\n\r\n",22))
      {
        received_is =ACCEPTED;
      }
      else
      {
        received_is=NOT_ACCEPTED;
      }
    }
       
    else if(response_compare(cmd , "ATE0\r\n",6))
    {
    if(response_compare(data , "\r\nOK\r\n",6) || response_compare(data , "ATE0\r\n\r\nOK\r\n",12) || response_compare(data , "ATE0\r\nOK\r\n",10))
    {
     received_is=ACCEPTED;
    }
    else
    {
      received_is=NOT_ACCEPTED;
    }
    }
   else if(response_compare(cmd ,"AT+CGDCONT=1,\"IP\",\"Etisalat\"\r\n",33))
    {
      if(response_compare(data,"\r\nOK\r\n",6) || response_compare(data,"\r\n\r\nOK\r\n",8))
      {
         received_is=ACCEPTED;
      }
      else
      {
         received_is=NOT_ACCEPTED;
      }
    }
    else if(response_compare(cmd ,"Emergency Detected\x1A",19))
    {
      if(response_compare(data,"\r\nOK\r\n",6) || (response_compare(data,"\r\n\r\nOK\r\n",8)) || (response_compare(data,"+CMGS:",6)) 
         || (response_compare(data,"\r\n+CMGS:",8))  || (response_compare(data,"\r\n\r\n+CMGS:",10)) )
      {
         received_is=ACCEPTED;
      }
      else
      {
         received_is=NOT_ACCEPTED;
      }
    }

    return received_is;
}
/********************************************************************************************************************
* Function Name : A9GtoNetwork
* Return value  : Void
*Description    : Connecting to Etisalat Network 
*Steps          :
                 1-Connect to Network
                 2-CGATT ensures that access to network is attached 
                 3-CGACT establish communication with network service
                 4-CGDCONT determining PDP used and AP of network 
                 5-CREG checks registeration to network
*********************************************************************************************************************/   
boolean A9GtoNetwork()
{ if(BKP_DR3==0x0000)
 {
  LCD_clearScreen();
   LCD_displayString("Accessing Network..");
  // Delay_MS(1000);
   A9G_Sendcmd("AT+CREG=1\r\n",20);
   check_Res=A9G_checkResponse("AT+CREG=1\r\n");
   if(check_Res == ACCEPTED)
  { 
  A9G_Sendcmd("AT+CGATT=1\r\n",40);  
  check_Res=A9G_checkResponse("AT+CGATT=1\r\n");
  if(check_Res == ACCEPTED)
  { A9G_Sendcmd("AT+CGDCONT=1,\"IP\",\"Etisalat\"\r\n",100);    /*client id , IP,Access point*/
    check_Res=A9G_checkResponse("AT+CGDCONT=1,\"IP\",\"Etisalat\"\r\n");
    
     if(check_Res == ACCEPTED)
     {
       A9G_Sendcmd("AT+CGACT=1\r\n",20);
     check_Res=A9G_checkResponse("AT+CGACT=1\r\n"); /*This command enables transfering data over the APN*/
       if(check_Res == ACCEPTED)
       {     A9G_Sendcmd("AT+CNMI=0,0,0,0,0\r\n",30);
             LCD_clearScreen();
             LCD_displayString("Network Accessed");
             Delay_MS(500);
         if(A9G_Brokerconnect())
         {
          return TRUE;
         }
         else
         {
          return FALSE;
         }
       }
       else
       {
         return FALSE;
       }
     }
     else
     {
       return FALSE;
     }
  }
  else
  {
    return FALSE;
  }
  }
   else{
     return FALSE;
     
   }
 }
else
{
                  //resetNMEA(data,DATA_SIZE);
                  SET_BIT(USART_2_CR1_REG,IDLEIE);    
                  DMA_Init(&DMA_7_Configurations);
                  DMA_resetBuffer(Data_Array);
             //     return TRUE;
//                   if(A9G_Subscribe())
//                   {
//                   return TRUE;
//                   }
//                   else
//                   {
//                     return FALSE;
//                   }
//                  
                  return TRUE;
}
 
}
/********************************************************************************************************************
* Function Name : A9G_BrokerConnect
* Return value  : boolean
*Description    :Through This Function we Connect to broker and subscribe to different Topics assigned on the Broker.
***Steps MQTT:
               1-MQTTCONN
               2-MQTTSUBUNSUB
               3-MQTTPUB
               4-MQTTDISCONN                 All return OK in case of succession.
*********************************************************************************************************************/
boolean A9G_Brokerconnect()
{
             LCD_clearScreen();
             LCD_displayString("Accessing emqx..");
          //   Delay_MS(500);
  /*Connect to a MQTT broker*/
  A9G_Sendcmd("AT+MQTTCONN=\"broker.emqx.io\",1883,\"A9G_ID\",60,0,\"fotateam\",\"123456\"\r\n",4000); 
  check_Res=A9G_checkResponse("AT+MQTTCONN=");
  /*Subscribe to each topic */
 
  if(check_Res == ACCEPTED)
  {                     
                  SET_BIT(USART_2_CR1_REG,IDLEIE);    
                  DMA_Init(&DMA_7_Configurations);
                  DMA_resetBuffer(Data_Array);
                   if(A9G_Subscribe())
                   {
                   return TRUE;
                   }
                   else
                   {
                     return FALSE;
                   }
  }
  else
  {
                  return FALSE;
  } 
}

STATIC boolean A9G_Subscribe()  
{
  A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/RemoteAccess/SpeedControl/SpeedLimit/value\",1,0\r\n",400);
  check_Res=A9G_checkResponse("AT+MQTTSUB=");
  if(check_Res==ACCEPTED)
  { 
  A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/RemoteAccess/SpeedControl/SpeedLimit/State\",1,0\r\n",400);
  check_Res=A9G_checkResponse("AT+MQTTSUB=");
  if(check_Res)
  {

    A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/RemoteAccess/ACcontrol/FanSpeed\",1,0\r\n",400);
check_Res=A9G_checkResponse("AT+MQTTSUB=");
  if(check_Res)
  {

    A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/RemoteAccess/ACcontrol/type\",1,0\r\n",400);
 check_Res=A9G_checkResponse("AT+MQTTSUB=");
  if(check_Res)
  {

    A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/service/location\",1,0\r\n",400);
  check_Res=A9G_checkResponse("AT+MQTTSUB=");
  if(check_Res)
  {

     A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/RemoteAccess/DoorControl\",1,0\r\n",400);
 check_Res=A9G_checkResponse("AT+MQTTSUB=");
  if(check_Res)
  {

    A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/RemoteAccess/SpeedControl/CarSpeed\",1,0\r\n",400);
check_Res=A9G_checkResponse("AT+MQTTSUB=");
  if(check_Res)
  {

    A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/Emergency/State\",1,0\r\n",400);
  check_Res=A9G_checkResponse("AT+MQTTSUB=");
 if(check_Res)
{
A9G_Sendcmd("AT+MQTTSUB=\"FOTA/Car/Engine\",1,0\r\n",400);
check_Res=A9G_checkResponse("AT+MQTTSUB=");
if(check_Res)
{
 A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/RemoteAccess/Engine\",1,0\r\n",400);
 check_Res=A9G_checkResponse("AT+MQTTSUB=");
 if(check_Res)
 {
   A9G_Sendcmd("AT+MQTTSUB=\"FOTA/Car/Emergency/State\",1,0\r\n",400);
 check_Res=A9G_checkResponse("AT+MQTTSUB=");
 if(check_Res)
 {
   A9G_Sendcmd("AT+MQTTSUB=\"FOTA/MobileApp/Emergency/State\",1,0\r\n",400);
 check_Res=A9G_checkResponse("AT+MQTTSUB=");
 if(check_Res)
 {
    LCD_clearScreen();
    LCD_displayString("Broker Accessed");
  //  Delay_MS(1000);
    return TRUE;
 }
 else
 {
  return FALSE;
 }
 }
 else
 {
  return FALSE;
 }
 }
 else
 {
  return FALSE;
 }
}
else
{
 return FALSE;
}
}
else
{
 return FALSE;
}
  }
  else
  {
    return FALSE;
  }
  
  }
  else
  {
    return FALSE;
  }
  }
  else
  {
    return FALSE;
  }
  }
  else
  {
    return FALSE;
  }
  }
  else
  {
    return FALSE;
  }
  }
  else
  {
    return FALSE;
  }
  }
  else
  {
    return FALSE;
  }
  
}   


/****************************************************************************************************************
*Function Name :A9G_getTopicData
*Return Value  :Void
*Descripton    :In this function we are buffering the responded data and topic if any data published on a certain topic.
*Parameters description : info--> Message carried on this transition
*****************************************************************************************************************/
void A9G_getTopicData(uint8 *response)
{ 

  uint8 topic_name[100]={0};
  uint8 info[30]={0};
  get_string(response,topic_name,',',',');
  get_strFromEnd(response,',',info);

  /*************************************************READING SECTION***********************************************/
//  if(response_compare(topic_name,"FOTA/MobileApp/RemoteAccess/SpeedControl/SpeedLimit/value",57) && (response_compare(Limiter_State,"true",4)) )
//  {
//   strCPY(info,Speed_Limit);
//  }
  if(response_compare(topic_name,"FOTA/MobileApp/RemoteAccess/SpeedControl/SpeedLimit/value",57))
  {
    resetBuffer(Speed_Limit_Cmd);
    Str_Cat("Speed_Limit=",info,Speed_Limit_Cmd);
    Speed_Limit_Flag=1;
  }
  else if(response_compare(topic_name,"FOTA/MobileApp/RemoteAccess/SpeedControl/SpeedLimit/State",57))
  {
     resetBuffer(Limiter_State_Cmd);
     Str_Cat("Limiter_State=",info,Limiter_State_Cmd);
     Limiter_State_Flag=1;
  }
  else if(response_compare(topic_name,"FOTA/MobileApp/RemoteAccess/ACcontrol/FanSpeed",46))
  {
     resetBuffer(AC_Level_Cmd);
     Str_Cat("AC_Level=",info,AC_Level_Cmd);
      AC_Level_Flag=1;
  }
  else if(response_compare(topic_name,"FOTA/MobileApp/RemoteAccess/ACcontrol/type",42))
  {
     resetBuffer(AC_State_Cmd);
     Str_Cat("AC_State=",info,AC_State_Cmd);
     AC_State_Flag=1;
  }
   else if(response_compare(topic_name,"FOTA/MobileApp/RemoteAccess/DoorControl",39))
  {
     resetBuffer(Door_Ctrl_Cmd);
     Str_Cat("Door_Control=",info,Door_Ctrl_Cmd);
     Door_Control_Flag=1;
  }
  /******************************************Read "ENABLED" OR "DISABLED"*************************************/
  else if(response_compare(topic_name,"FOTA/MobileApp/Emergency/State",30))
  {
     resetBuffer(Emergency_State_Cmd);
     Str_Cat("Emergency_State=",info,Emergency_State_Cmd);
     Emergency_State_Flag=1;
  }
  else if(response_compare(topic_name,"FOTA/MobileApp/RemoteAccess/Engine",34))
  {
     resetBuffer(Car_Engine_Cmd);
     Str_Cat("Car_Engine=",info,Car_Engine_Cmd); 
     Car_Engine_ACK=1;
  }
}
/****************************************************************************************************************
*Function Name :A9G_MQTTread
*Return Value  :Void
*Descripton    :In this function we are reading the responded data if any data published by another client (Mobile App.).
*****************************************************************************************************************/
void A9G_MQTTread( uint8 *response)
{
  if(response_compare(response,"\r\n+MQTTPUBLISH:",15)    ||  response_compare(response,"\n+MQTTPUBLISH:",14) 
     || response_compare(response,"\r+MQTTPUBLISH:",14)   ||  response_compare(response,"+MQTTPUBLISH:",13))
  {
    A9G_getTopicData(response);
  }
  if(response_compare(response,"\r\n+GPSRD:",9)    ||  response_compare(response,"\n+GPSRD:",8) 
     || response_compare(response,"\r+GPSRD:",8)   ||  response_compare(response,"+GPSRD:",7))
  {
       //Configured for no \r\n
//     if(NMEAtoGPS(response ,gps_buffer))
//     {
//     A9G_PublishGPS();
//     }
    if(NMEAtoGPS(response ,gps_buffer))
    {
      GPS_Flag=1;
    }
  }
  if(   response_compare(response,"+MQTTDISCONNECTED:",18)   ||  response_compare(response,"\n+MQTTDISCONNECTED:",19)
     || response_compare(response,"\r+MQTTDISCONNECTED:",19) ||  response_compare(response,"\r\n+MQTTDISCONNECTED:",20))
  {
    LCD_clearScreen();
    LCD_displayStringRowColumn(0,0,"Broker");
    LCD_displayStringRowColumn(1,0,"Disconnected");
    Delay_MS(1000);
    A9G_Brokerconnect();
  }
  
}

/****************************************************************************************************************
*
*
*                           P U B L I S H I N G       D A T A         S E C T I O N
*
*
*****************************************************************************************************************/
/****************************************************************************************************************
*Function Name :A9G_PublishSpeed
*Descripton:Accessed in main.c based on an action i publish car speed on a certain topic.
*****************************************************************************************************************/
void A9G_PublishSpeed(uint8 *speed)
{ //A9G_GPS_OFF(); 
  uint8 command[200]="AT+MQTTPUB=\"FOTA/MobileApp/RemoteAccess/SpeedControl/CarSpeed\",\"\",0,0,0\r\n";
  insert_string(command,64,speed);  /*************BASED ON TOPIC NAME SIZE***********/
  CLEAR_BIT( USART_2_CR1_REG , IDLEIE );
  A9G_Sendcmd(command,300);
  SET_BIT( USART_2_CR1_REG , IDLEIE );
//  A9G_GPS();
}

/**********************************************************************************************************************
* Name        : A9G_CheckEngine 
* Return value: boolean
* Description : Polling on it till mobile application check engine or manually checked by the client .
* Related Topics: 
"FOTA/Car/Engine"  (Write only with RETAIN). 
"FOTA/MobileApp/RemoteAccess/Engine"  (Read only from mobile app). 
************************************************************************************************************************/
boolean A9G_CheckEngine()
{
  if(Car_Engine_Flag==1)
  {
    Car_Engine_Flag=0;
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}
void A9G_PublishEngine(uint8 *state)
{
  // A9G_GPS_OFF();
   uint8 command[150]="AT+MQTTPUB=\"FOTA/Car/Engine\",\"\",0,0,1\r\n";  //with retain
   CLEAR_BIT( USART_2_CR1_REG , IDLEIE );
   insert_string(command,30,state); /*************BASED ON TOPIC NAME SIZE***********/ //state either true or false
   A9G_Sendcmd(command,200);
   SET_BIT( USART_2_CR1_REG , IDLEIE );
  // A9G_GPS();
}
/**********************************************************************************************************************
* Name        : A9G_EmergencyActs   (Not finished Yet)
* Return value: void
* Description : In case of Emergency the Module automatically    1-Publishing "ENABLED" on EmergencyState Topic.
                                                                 2-call the client's Emergency number.
                                                                 3-Send SMS to the client
                                                                 4-Continue retreiving location 
                                                                 5-Speed limit is set 0 .
"FOTA/Car/Emergency/State"   (Write only send ENABLED , DISABLED With retain).
"FOTA/MobileApp/Emergency/State" (Read only , ENABLED DISABLED)  READ FORM MOBILE APP.
"FOTA/Car/Engine"  (Write only with RETAIN). 
"FOTA/MobileApp/RemoteAccess/Engine"  (Read only from mobile app). 
************************************************************************************************************************/
void A9G_EmergencyActs()
 {
   //A9G_GPS_OFF();  
   A9G_Sendcmd("AT+CMGF=1\r\n",30);       //Send SMS to client
   check_Res=A9G_checkResponse("AT+CMGF=1\r\n");
   if(check_Res)
   {
   A9G_Sendcmd("AT+CMGS=\"+201006425048\"\r\n",30);   
   A9G_Sendcmd("Emergency Detected\x1A",70);  
   check_Res=A9G_checkResponse("Emergency Detected\x1A");
   if(check_Res)
   {
   A9G_Sendcmd("AT+CMGF=0\r\n",30);
   check_Res=A9G_checkResponse("AT+CMGF=0\r\n");
   if(check_Res)
   {
   A9G_Sendcmd("ATD+201006425048\r\n",30); //Call Clients number dont send command till user hang up 
   }
   }
   }
   //A9G_GPS();
   
 }
void A9G_PublishEmergency(uint8 *state)
{  
   uint8 command[150]="AT+MQTTPUB=\"FOTA/Car/Emergency/State\",\"\",0,0,1\r\n";  //with retain
   CLEAR_BIT( USART_2_CR1_REG , IDLEIE );
   insert_string(command,39,state); /*************BASED ON TOPIC NAME SIZE***********/ //state either ENABLED or DISABLED
   A9G_Sendcmd(command,200);
   SET_BIT( USART_2_CR1_REG , IDLEIE );
}
/***********************************************************************************************************************
*Function name: A9G_PublishGPS
*Descripton: Passing on a specific MQTT Topic.
************************************************************************************************************************/
void A9G_PublishGPS(void)
{ 
  uint8 command[300]="AT+MQTTPUB=\"FOTA/MobileApp/service/location\",\"\",0,0,0\r\n";
  insert_string(command,46,gps_buffer); /*************BASED ON TOPIC NAME SIZE***********/
  CLEAR_BIT( USART_2_CR1_REG , IDLEIE );
  A9G_Sendcmd(command,300);
  SET_BIT( USART_2_CR1_REG , IDLEIE );
//This check is useless as we can monitor dash-board on Mobile app screen 
//  check_Res=A9G_checkResponse(command);
//  switch(check_Res)
//  {
//  case ACCEPTED:
//                
//                break;
//  case NOT_ACCEPTED: 
//                     
//                     break;
//  }
  
}
/**************************************************************
*Function enables GPS by a special AT command  
***************************************************************/
void A9G_GPS(void)
{
   A9G_Sendcmd("AT+GPS=1\r\n",30);   /*Enables GPS*/
   A9G_Sendcmd("AT+GPSRD=10\r\n",60); /*responds with ok and after "10" sec it responds GPS coordinates*/
   
}
/**************************************************************
*Function disables GPS by a special AT command  
***************************************************************/
void A9G_GPS_OFF(void)
{
   A9G_Sendcmd("AT+GPS=0\r\n",30);   /*Disables GPS*/
   
}
/********************************************************************************************************************
*Function name: NMEAtoGPS
*Descripton: Converting NMEA 0183 Format into Lat,Long format then buffering
             the gps in an array of characters to be then published on a specific MQTT Topic.
*********************************************************************************************************************/
STATIC boolean NMEAtoGPS(uint8 *NMEA_Out ,uint8 *Location)
{ //+GPSRD:$GNGGA,000638.262,3009.7818,N,03122.0447,E,0,0,,133.2,M,16.8,M,,*53
  uint8 i=0;
  uint8 i2=0;
  uint8 j=25;
  uint8 j2=37; //i:Gps_buffer ,,,,j: just for distribution
  uint8 Longtitude[15];
  uint8 Lattitude[15];
  resetBuffer(Location);
  if((NMEA_Out==NULL_PTR) || (response_compare(NMEA_Out,"+GPSRD",6) == FALSE))
  {
    resetNMEA(NMEA_Out,73);
    return FALSE;
  }
  else if ((NMEA_Out!=NULL_PTR) && (response_compare(NMEA_Out,"+GPSRD",6) == TRUE))
  {
                              
  while(NMEA_Out[j]!=',')
  { 
    Lattitude[i]=NMEA_Out[j];
    i++;
    j++;
  }  
  Lattitude[i]='\0';
   while(NMEA_Out[j2]!=',')
  { 
    Longtitude[i2]=NMEA_Out[j2];
    i2++;
    j2++;
  }  
  Longtitude[i2]='\0';
  convertToMaps(Lattitude);
  convertToMaps(Longtitude);
  strConnect(Lattitude,Longtitude,Location);
  resetNMEA(NMEA_Out,73);
  return TRUE;
  }
  else
  {
    LCD_clearScreen();
    LCD_displayString("UNEXCPECTED");
    Delay_MS(1000);
    return FALSE;
  }
}
STATIC void convertToMaps(uint8 *str)
{ uint8 i=0;
  uint8 count=0;
  uint8 tmp;
  for(i=0;str[i]!='.';i++)
  {
  }
 while(count<2)
 {
  tmp=str[i];
  str[i]=str[i-1];
  str[i-1]=tmp;
  i--;
  count++;
 }
}
/*************************************************Helpful Functions****************************************************/
boolean response_compare(const uint8 *str1 ,const uint8 *str2,const uint8 size)
{  /* Compare status */
  boolean cmpStatus = TRUE;

  /* Check null pointers */
  if( (NULL_PTR != str1) && (NULL_PTR != str2) )
  {
    /* Start comparing */
    for (int idx = 0; idx < size; idx++)
    {
      /* When not equal set the return status */
      if(str1[idx] != str2[idx])
      {
        cmpStatus = FALSE;
      }
      else
      {
        /* Do nothing */
      }
    }
  }
  else
  {
   cmpStatus = FALSE;
  }
  return cmpStatus;
}
STATIC void insert_string(uint8 *str,uint8 start,uint8 *sub_str)
{
 uint8 str_len=0,sub_len=0;
 while(str[str_len] !='\0')
 {
   str_len++;
 }
 while(sub_str[sub_len] !='\0')
 {
   sub_len++;
 }
 if (start > str_len) {
        
        
        for (uint8 i = 0; i < sub_len; i++) {
            str[str_len + i] = sub_str[i];
        }
        // Null-terminate the string
        str[str_len + sub_len] = '\0';
 }
else{
 for (uint8 i = str_len; i >= start; i--) {
        str[i + sub_len] = str[i];
    }
}
    for (uint8 i = 0; i < sub_len; i++) {
        str[start + i] = sub_str[i];
    }

}
STATIC void get_string(uint8 *str,uint8 *sub_str,uint8 start_char,uint8 end_char)
{
    uint8 i=0,j=0;
    while(str[i] !=start_char)
    {
      i++;
    }
    i++;
    while(str[i]!=end_char)
    {
     sub_str[j]=str[i];
     i++;
     j++;      
    }    
}
/**Working only if the string ends with \r\n then Null terminator**/
STATIC void get_strFromEnd(uint8 *str,uint8 start_char,uint8 *sub_str)
{ uint8 i=0,j=0,len=0;
  while(str[len]!='\r')
  {
    len++;
  }
  i=len-1;
  while(str[i]!=start_char)
  {
    i--;
  }
  i++;
  while(str[i]!='\r')
  {
    sub_str[j]=str[i];
    i++;
    j++;
  }
  sub_str[j]='\0';
}
 STATIC void strCPY(uint8 *source,uint8 *dest)
 {
   uint8 len1=0;
   uint8 len2=0;
   while(source[len1]!='\0')
   {
     len1++;
   }
   while(dest[len2]!='\0')
   {
     len2++;
   }
   for(uint8 i=0;source[i]!='\0';i++)
   {
     dest[i]=source[i];
     
   }
   
   
 }

STATIC void strConnect(uint8 *src1 ,uint8 *src2,uint8 *dest)
{
  uint8 i=0;
  uint8 j=0;
  while(src1[i]!='\0')
  {
    dest[i]=src1[i];
    i++;
  }
  dest[i]=',';
  i++;
  while(src2[j]!='\0')
  {
    dest[i]=src2[j];
    i++;
    j++;
  }
  dest[i]='\0';
  
}
STATIC void resetBuffer(uint8 *buffer_start)
{
  for(uint8 i=0;buffer_start[i]!='\0';i++)
  {
    buffer_start[i]='\0';
    
  }
  
}
STATIC void resetNMEA(uint8 *buff,uint8 size)
{
  for(uint8 i=0;i<size;i++)
  {
    buff[i]='\0';
    
  }
  
  
 
}
void Str_Cat(uint8 *str1,uint8 *str2,uint8 *dest)
{
  
  uint8 i=0;
  uint8 j=0;
  while(str1[i]!='\0')
  {
    dest[i]=str1[i];
    i++;
  }
  while(str2[j]!='\0')
  {
    dest[i]=str2[j];
    i++;
    j++;
  }
  dest[i]='\0';
  
}

