/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: PCB2.c
 *
 * Description: types for ARM
 *
 * Date Created: 15/6/2024
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/
/**-------------------------INCLUDES Section------------------------**/
#include "Port.h"
#include "Dio.h"
#include "UART.h"
#include "LCD.h"
#include "PLL.h"
#include "Delay.h"
#include "adc.h"
#include "potentiometer.h"
#include "GPT.h"
#include "dc_motor.h"
#include "Fan.h"
#include "sys_timer.h"
#include "LPWAN.h"
#include "servo_motor.h"
#include "DMA.h"
#include "TIM8_PWM.h"
#define SAFETY_FACTOR 15
#define NONE 2

   /******************************************************************/
#define FAN_COLD            1
#define FAN_HOT             2
#define FAN_NORMAL          3
#define FAN_STOP            0
#define FAN_HIGH            1
#define FAN_LOW             2
#define FAN_MEDIUM          3
#define ENGINE_ON           1
#define ENGINE_OFF          2
#define DOOR_LOCK           1
#define DOOR_UNLOCK         2
#define DISABLED            2
#define ENABLED             1
#define LIGHTS_ON           1
#define LIGHTS_OFF          0
   /******************************************************************/
/**-------------------------Macros----------------------------------**/
/* Used to Sync UART in Polling method */
#define CONTROL_READY 10

#define MEGA 1000000
/**-------------------------Global Variables Section----------------**/
/* Global variable to receive UART data inside */
uint8 g_LPWAN_RECEIVE_DATA  ;
/* Variable to receive the lpwan ID */
uint8 g_LPWAN_RECEIVE_ID;
/* If it was the first time to receive then receive the ID first */
//uint8 g_LPWAN_ID_FLAG = 0;
/* If the ID was correct SET flag */
uint8 g_LPWAN_CORRECT_ID =0;
/* Used to know if we have received DATA or NOT */
//uint8 g_UART_RECEIVE_FLAG = 0;
/*Global flags to store updated info and display it on dashboard*/
uint8 Door_Flag=DOOR_UNLOCK;
uint8 AC_LVL_Flag=FAN_STOP;
uint8 AC_State_Flag=FAN_NORMAL;
uint8 Emergency_Flag=DISABLED;
uint8 Engine_Flag=ENGINE_OFF;
uint8 Lights_Flag=LIGHTS_OFF;
uint8 speed_display[3]={0};
uint16 speed_carrier=0;
uint16 Speed_limit_carrier=330;
uint8 speed_limit_display[3]={"330"};
/*Global array */
uint8 g_LPWAN_RECEIVE_STRING[100]="AC_State=Hot";
uint16 g_reset_speed_limit=0;
volatile uint8 Time_flag=0; //For handling Timer
void Timer1_ISR_Handler();
/**-------------------------Configuration Section-------------------**/
/* Config systick timer */
 SYS_TIMER_ConfigType Systick_config = {Processor_clock_AHB,not_assert_SysTick_request,enabled};
 
/**-------------------------Function Dec.Section-------------------**/
 ///////////////////////////////////////////////////////////////////////////////////////////
 /*
 * Description :
 * Read string from DMA
 */
///////////////////////////////////////////////////////////////////////////////////////////
void DMA_Data_Read (void );
///////////////////////////////////////////////////////////////////////////////////////////
 /*
 * Description :
 * The Interrupt Service Routine to handle the received data in the UART data register
 */
///////////////////////////////////////////////////////////////////////////////////////////
void USART1_IRQHandler( void );
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * Initializing everything
 */
///////////////////////////////////////////////////////////////////////////////////////////
void Drivers_Init(void);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * find certain character in string 
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint8 * strChr (uint8 * data , uint8 sign);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * copy string to another 
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC void strCPY(uint8 *dest,uint8 *source);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * compare 2 strings from start to limit 
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint8 strnCMP (uint8* str1 ,uint8* str2, uint8 limit);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * compare 2 strings  
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint8 strCMP (uint8* str1 ,uint8* str2);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * convert string to intger  
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint16 atoi(uint8* data);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  A static function used to reverse the passed string
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC void reverse(uint8* str, uint8 length);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  A static function used to convert integer to strings
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint8* itoa(uint16 num, uint8* str, uint8 base);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  reset string
 */
///////////////////////////////////////////////////////////////////////////////////////////
void reset_string (uint8* string, uint8 length);
void reset_arr(uint8* string, uint8 length);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  senstivitiy of potentiometer (if saftey factor =15 and initial value=100 then if it become 102 it doesnot change but if it become 115 will change) 
 */
///////////////////////////////////////////////////////////////////////////////////////////
boolean If_Senstivity_reduced(uint16 num1,uint16 num2);
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  concatinate 2 string to be in one string
 */
///////////////////////////////////////////////////////////////////////////////////////////
void Str_Cat(uint8 *str1,uint8 *str2,uint8 *dest);
void Emergency_display();
void Dashboard_Display();
void Emergency_clear();
void reset_app(void);

/**-------------------Function Dec. Section END---------------------**/


/**------------------------------MAIN-------------------------------**/
int main()
{
  
  /**-----------------------Local Variables----------------------**/
  uint8 *equalSign;
  uint8 length=0;
  uint8 flag=0;
  uint16 Speed_Limit=330;
  //uint8 car_speed=0;
  uint16 res_value_new=0;
  uint16 res_value_old=0;
  Dio_LevelType engine_state=NONE;
  
  /*array of strings*/
  uint8 Remote_access[13][30]=
  {
    "Speed_Limiter=",
    "Car_Speed=",
    "AC_Level=",
    "AC_State=",
    "Door_Control=",
    "Emergency_Ack=ENABLED#",
    "Emergency_State=ENABLED", //6->length=22
    "Emergency_Ack=DISABLED#",
    "Emergency_State=DISABLED",//8->length=23
    "Car_Engine=true",         //9->length=14
    "Car_Engine=false",       //10->length=15
    "Car_State=ON#",
    "Car_State=OFF#"
    
  };
  uint8 Door_State[2][10]=
  {
    "unlock",
    "lock"
  };
  uint8 AC_Level[4][10]=
  {
    "Stop",
    "Low",
    "Medium",
    "High"
  };
   uint8 AC_State[3][10]=
  {
    "Cold",
    "Normal",
    "Hot"
  };
  /*stored strings*/
  uint8 data [10]={0};  //
  uint8 result [30]={0};
  uint8 Speed_Limiter[10]={0}; 
  uint8 Door_Control[10]={0};
  uint8 AC_Level_Control[10]={0};
  uint8 AC_State_Control[10]={0};
  /**-----------------------Main Section-------------------------**/
  /* Initializing Drivers at first */
  Drivers_Init(); 
  /* Welcome intro */
  LCD_clearScreen();
  LCD_displayString("Welcome");
  Delay_MS(1000);
  LCD_clearScreen();
 // LCD_displayString("Getting start...");
    

    while(1)
    { 
      /*****************************************Engine State update manually*******************************************************************/
       if(Dio_ReadChannel(DioConf_ENGINEPB_CHANNEL_ID_INDEX))
      {
        Delay_MS(100);
        engine_state = Dio_FlipChannel(DioConf_ENGINE_CHANNEL_ID_INDEX);
        if(engine_state==STD_LOW)
        {
          Engine_Flag=OFF;
        }
        else if (engine_state==STD_HIGH)
        {
          if(Emergency_Flag==ENABLED)
          {
            engine_state=STD_LOW;
            Engine_Flag=OFF;
            Dio_WriteChannel(DioConf_ENGINE_CHANNEL_ID_INDEX,STD_LOW);
          }
          else
          {
            flag=1;
            Engine_Flag=ENGINE_ON;
          }
        }
      }

      /***********************************************Engine State update remotely*************************************************************/
      if(((strnCMP(g_LPWAN_RECEIVE_STRING,Remote_access[9] , 13) == 0) && (g_LPWAN_CORRECT_ID == 1) && (Emergency_Flag==DISABLED)) )
      {
        engine_state=STD_HIGH;
        flag=1;
        Engine_Flag=ENGINE_ON;
        Dio_WriteChannel(DioConf_ENGINE_CHANNEL_ID_INDEX,STD_HIGH);
        g_LPWAN_CORRECT_ID =0;
        reset_string(g_LPWAN_RECEIVE_STRING,30);
      }
      if (((strnCMP(g_LPWAN_RECEIVE_STRING,Remote_access[10] , 14) == 0) && (g_LPWAN_CORRECT_ID == 1))) // flag=0?
      {
        engine_state=STD_LOW;
        Engine_Flag=ENGINE_OFF;
        Dio_WriteChannel(DioConf_ENGINE_CHANNEL_ID_INDEX,STD_LOW); 
        g_LPWAN_CORRECT_ID =0;
        reset_string(g_LPWAN_RECEIVE_STRING,30);
      }
      if (engine_state==STD_HIGH)
      {
         
         //send by lpwan
         if (flag==1)
         {
           LPWAN_SendFrame(Remote_access[11]);
           flag=0;
         }
         
         
      /**************************************************Car Headlights*************************************************************************/
      if(Dio_ReadChannel(DioConf_HLPB_CHANNEL_ID_INDEX))
      {
        Delay_MS(100);
        Dio_LevelType state1 = Dio_FlipChannel(DioConf_HL1_CHANNEL_ID_INDEX);
        Dio_LevelType state2 = Dio_FlipChannel(DioConf_HL2_CHANNEL_ID_INDEX);
        Lights_Flag=state2;
      }
      
      /****************************************************Car Speed sensing and publishing*****************************************************/
      res_value_new= potentiometer_write(ADC1 ,ADC_CHANNEL_1_); 
      if (If_Senstivity_reduced(res_value_new,res_value_old))   
      { uint8 index=0;
        if (res_value_new<Speed_Limit)
        {       
        DcMotor_Rotate(CW,res_value_new,Speed_Limit,TIM_3);  //Ex:DcMotor_Rotate(CW,150,330,TIM_3);
        speed_carrier=res_value_new;
       // LCD_intgerToString(res_value_new);
        res_value_old=res_value_new;
        //send by lpwan
        itoa(res_value_new,data,10);
        strCPY(speed_display,data);
        Str_Cat(Remote_access[1],data,result);
        Str_Cat(result,"#",result);
        if(Time_flag==1)
        {
        CLEAR_BIT(TIM4_DIER_REG,0);
      //  LCD_displayStringRowColumn(1,0,result);
        LPWAN_SendFrame(result);
        TIM4_CNT_REG =0;
        SET_BIT(TIM4_DIER_REG,0);
        Time_flag=0;
        }
        
        }
        else if((res_value_new>=Speed_Limit)) 
        {
        DcMotor_Rotate(CW,Speed_Limit,Speed_Limit,TIM_3);
        //LCD_intgerToString(res_value_new);
        res_value_old=Speed_Limit; //res_value_old = res_value new
        speed_carrier=Speed_Limit;
        //send by lpwan
        itoa(Speed_Limit,data,10);
        strCPY(speed_display,data);
         Str_Cat(Remote_access[1],data,result);
         Str_Cat(result,"#",result);
         if(Time_flag==1)
        {
        CLEAR_BIT(TIM4_DIER_REG,0);
      //  LCD_displayStringRowColumn(1,0,result);
        LPWAN_SendFrame(result);
        TIM4_CNT_REG =0;
        SET_BIT(TIM4_DIER_REG,0);
        Time_flag=0;
        }
        }
        else
        {
          /*Do nothing*/
        }
        index=0;
        reset_arr(data,3);
        reset_arr(result,30);
      }
      /*****************************************Parsing received data to take actions***********************************************************/
      if(g_LPWAN_CORRECT_ID == 1)
      {
        // Find the '=' character in the g_LPWAN_RECEIVE_STRING string
        equalSign = strChr(g_LPWAN_RECEIVE_STRING, '=');
        length=equalSign-g_LPWAN_RECEIVE_STRING;
        
        //Compare the characters of str1 and str2 to equalSign
       if (strnCMP(g_LPWAN_RECEIVE_STRING,Remote_access[0] , length) == 0) //Checkkkkkkkk
        {
          strCPY(Speed_Limiter, equalSign + 1);
//          LCD_clearScreen();
//          LCD_displayString("Limit Became");
//          LCD_displayStringRowColumn(1,0,Speed_Limiter);
          Delay_MS(100);
          strCPY(speed_limit_display,Speed_Limiter);
          Speed_Limit=atoi(Speed_Limiter);
          Speed_limit_carrier=Speed_Limit;
          g_reset_speed_limit=Speed_Limit;       //for reset_app()
          if (Speed_Limit>330)
          {
            Speed_Limit=330;
            Speed_limit_carrier=330;
            itoa(330,speed_limit_display,10);
          }
          if (Speed_Limit<res_value_old)
          {
           // DcMotor_Rotate(CW,Speed_Limit,TIM_3);
            res_value_new=Speed_Limit;
          }
          reset_string(Speed_Limiter,10);
          g_LPWAN_CORRECT_ID = 0;
          reset_string(g_LPWAN_RECEIVE_STRING,30);
        }
        else if(strnCMP(g_LPWAN_RECEIVE_STRING,Remote_access[2] ,length) == 0)
        {
          strCPY(AC_Level_Control, equalSign + 1);
//          LCD_clearScreen();
//          LCD_displayString("AC Level=");
//          LCD_displayStringRowColumn(1,0,AC_Level_Control);
          Delay_MS(100);
          for (uint8 i =0 ; i<4 ; i++)
          {
            if (strCMP(AC_Level_Control,AC_Level[i] )==0)
            {
              switch (i)
              {
              case 0 :Fan_Rotate(STOP_FAN,TIM_2);
                      AC_LVL_Flag=FAN_STOP;
                      Dio_WriteChannel(DioConf_COLD_CHANNEL_ID_INDEX,STD_HIGH); //BLUE
                      Dio_WriteChannel(DioConf_MED_CHANNEL_ID_INDEX,STD_HIGH); 
                      Dio_WriteChannel(DioConf_HOT_CHANNEL_ID_INDEX,STD_HIGH);
                      break;
              case 1 :Fan_Rotate(LOW,TIM_2);
                      AC_LVL_Flag=FAN_LOW;
                      break;
              case 2 :Fan_Rotate(MEDIUM,TIM_2);
                      AC_LVL_Flag=FAN_MEDIUM;
                      break;
              case 3 :Fan_Rotate(HIGH,TIM_2);
                      AC_LVL_Flag=FAN_HIGH;
                      break;
              }
              
            }
          
          }
          reset_string(AC_Level_Control,10);
          g_LPWAN_CORRECT_ID = 0;
          reset_string(g_LPWAN_RECEIVE_STRING,30);
        }
        else if(strnCMP(g_LPWAN_RECEIVE_STRING,Remote_access[3] ,length) == 0)
        {
          strCPY(AC_State_Control, equalSign + 1);
//          LCD_clearScreen();
//          LCD_displayString("AC State=");
//          LCD_displayStringRowColumn(1,0,AC_State_Control);
          Delay_MS(100);
          for (uint8 i =0 ; i<3 ; i++)
          {
            if (strCMP(AC_State_Control,AC_State[i] )==0)
            {
              switch (i)
              {
              case 0 : Dio_WriteChannel(DioConf_COLD_CHANNEL_ID_INDEX,STD_LOW); //BLUE
                       Dio_WriteChannel(DioConf_MED_CHANNEL_ID_INDEX,STD_HIGH); 
                       Dio_WriteChannel(DioConf_HOT_CHANNEL_ID_INDEX,STD_HIGH); 
                       AC_State_Flag=FAN_COLD;
                      break;
              case 1 :Dio_WriteChannel(DioConf_MED_CHANNEL_ID_INDEX,STD_LOW); //YELLOW
                      Dio_WriteChannel(DioConf_COLD_CHANNEL_ID_INDEX,STD_HIGH); 
                      Dio_WriteChannel(DioConf_HOT_CHANNEL_ID_INDEX,STD_HIGH); 
                      AC_State_Flag=FAN_NORMAL;
                      break;
              case 2 :Dio_WriteChannel(DioConf_HOT_CHANNEL_ID_INDEX,STD_LOW); //RED
                      Dio_WriteChannel(DioConf_MED_CHANNEL_ID_INDEX,STD_HIGH); 
                      Dio_WriteChannel(DioConf_COLD_CHANNEL_ID_INDEX,STD_HIGH); 
                      AC_State_Flag=FAN_HOT;
                      break;
            
              }
              
            }
          
          }
          reset_string(AC_State_Control,10);
          g_LPWAN_CORRECT_ID = 0;
          reset_string(g_LPWAN_RECEIVE_STRING,30);
        }
        else if(strnCMP(g_LPWAN_RECEIVE_STRING,Remote_access[4] ,length) == 0)
        {
           strCPY(Door_Control, equalSign + 1);
//          LCD_clearScreen();
//          LCD_displayString("Door State=");
//          LCD_displayStringRowColumn(1,0,Door_Control);
          Delay_MS(100);
          if(strCMP(Door_Control,Door_State[0] )==0)
          {
            Servo_Rotate(90);
            Door_Flag=DOOR_UNLOCK;
          }
          else 
          {
            Servo_Rotate(0);
            Door_Flag=DOOR_LOCK;
          }
          reset_string(Door_Control,10);
          g_LPWAN_CORRECT_ID = 0;
          reset_string(g_LPWAN_RECEIVE_STRING,30);
         }
        
        
      }
         }
       /******************************************Engine is OFF *******************************************************************************/
        else if (engine_state==STD_LOW)
        {
          //send by lpwan
            LPWAN_SendFrame(Remote_access[12]);
            reset_app();
            engine_state=NONE;
            Engine_Flag=ENGINE_OFF;
            Delay_MS(100);
        }
       else
       {
              /*Do nothing*/
       }
      /************************************************Emergency handling************************************************************************/ 
      //Enable EMERGENCY swa2 l engine start aw stopped
      if((Dio_ReadChannel(DioConf_EMERGENCYPB_CHANNEL_ID_INDEX)) || ((strnCMP(g_LPWAN_RECEIVE_STRING,Remote_access[6] , 22) == 0) && (g_LPWAN_CORRECT_ID == 1)) )
      {
        Delay_MS(100);
        Emergency_Flag=ENABLED;       
        Dio_WriteChannel(DioConf_EMERGENCY_CHANNEL_ID_INDEX,STD_LOW);
        Speed_Limit=0;
        Dio_WriteChannel(DioConf_BUZZER_CHANNEL_ID_INDEX,STD_HIGH); 
        LPWAN_SendFrame(Remote_access[5]);
        g_LPWAN_CORRECT_ID = 0;
        reset_string(g_LPWAN_RECEIVE_STRING,30);
        //send by lpwan to close engine if it was opened
        if (engine_state==STD_HIGH)
        {
         engine_state=STD_LOW;
         Engine_Flag=ENGINE_OFF;
         //Dio_WriteChannel(DioConf_ENGINE_CHANNEL_ID_INDEX,STD_LOW); 
         //LCD_clearScreen();
         //LCD_displayString(Remote_access[12]); 
//         LPWAN_SendFrame(Remote_access[12]);
         
        }
        
      }
      //Disable EMERGENCY swa2 l engine start aw stopped
     if(((strnCMP(g_LPWAN_RECEIVE_STRING,Remote_access[8] , 23) == 0) && (g_LPWAN_CORRECT_ID == 1)) )
     {
       Emergency_Flag=DISABLED;
       Emergency_clear();
       Dio_WriteChannel(DioConf_EMERGENCY_CHANNEL_ID_INDEX,STD_HIGH);
       Dio_WriteChannel(DioConf_BUZZER_CHANNEL_ID_INDEX,STD_LOW);
       LPWAN_SendFrame(Remote_access[7]);
       g_LPWAN_CORRECT_ID = 0;
       reset_string(g_LPWAN_RECEIVE_STRING,30);
     }
    Dashboard_Display();
}
  
}
/**-------------------------End Main-------------------**/

/**-------------------------Function Section-------------------**/
///////////////////////////////////////////////////////////////////////////////////////////
 /*
 * Description :
 * Read string from DMA
 */
///////////////////////////////////////////////////////////////////////////////////////////
void DMA_Data_Read (void )
{ 
  if (Data_Array[0]==LPWAN_ID)
  {
   uint8 array_index ;
   g_LPWAN_RECEIVE_ID=Data_Array[0];
      //strcpy(g_LPWAN_RECEIVE_STRING, &Data_Array[1]);
   for (array_index =0;Data_Array[array_index]!='#';array_index ++)
       {
         g_LPWAN_RECEIVE_STRING[array_index]=Data_Array[array_index+1];
       }
  }
  else 
  {
    /* Do nothing */
  }
}
/************************************************************************Handlers****************************************************/
///////////////////////////////////////////////////////////////////////////////////////////
 /*
 * Description :
 * The Interrupt Service Routine to handle the received data in the UART data register
 */
///////////////////////////////////////////////////////////////////////////////////////////
void USART1_IRQHandler( void )
{
    /* Check if the USART1 Idle interrupt is pending */
    if ( BIT_IS_SET(USART_1_SR_REG , IDLE) )
    {
    //  LCD_clearScreen();
      volatile uint8 tmp_read=0;
        /* Clear Register Manually */
        CLEAR_BIT(USART_1_SR_REG , IDLE);
        tmp_read=USART_1_SR_REG;
        tmp_read=USART_1_DR_REG;

        DMA_Disable(&DMA_Configurations);
        DMA_resetCNDTR(&DMA_Configurations);
        DMA_Data_Read ( );
        DMA_Enable(&DMA_Configurations);
        
        /* Check on the received ID */
        if(LPWAN_ReceiveCheck(g_LPWAN_RECEIVE_ID))
         {
           g_LPWAN_CORRECT_ID = 1;
         }
         else
         {
           g_LPWAN_CORRECT_ID = 0;
         }
          
    }
    else
    {
      /* Do nothing */
    }
}
// Jumps here when counter reaches 1 sec
void Timer1_ISR_Handler()
{
  Time_flag=1;
}
/***********************************************************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * Initializing everything
 */
///////////////////////////////////////////////////////////////////////////////////////////
void Drivers_Init(void)
{
  /* Initialize PORT Driver */
  Port_Init(&Port_Configuration);
  
  /* Initialize DIO Driver */
  Dio_Init(&Dio_Configuration);
  
    /* Setting MCU clock to 72 MHz */
  SystemClockInit();
  /* Initialize LPWAN */
  LPWAN_Init();
   /* Initializing DMA */
  DMA_Init(&DMA_Configurations); 
  /* Initializing LCD */
  LCD_init();
  
  /* Initializing GPT */
  const GPT_ConfigType GPT_Configuration ={
        /*FAN_OUT*/                          TIM_2,72*MEGA,PWM,channel_1,1000,Counter_enabled,UEV_disabled,any_event,Counter_is_not_stopped_at_UEV,upcounter,Edge_aligned_mode,TIMx_ARR_register_is_buffered,tCK_INT,                                                  
                                            };
 
   GPT_INIT(&GPT_Configuration);
   TIM1_Init(); 
   TIM3_Init();
   TIM4_Init();
   Timer_SetCallBack(Timer1_ISR_Handler);
  /* ADC Config */
 ADC_Config  ADC_PBcfg;
 ADC_PBcfg.ADC_num=ADC1;
 ADC_PBcfg.channel_index=ADC_CHANNEL_0_;
 ADC_PBcfg.ADC_prescaler=PRESCALE_2_;
 ADC_PBcfg.wd_en=DISABLE;
 ADC_PBcfg.dual_mode=Independent_Mode;
 ADC_PBcfg.disc_count=ONE_CHANNEL;
 ADC_PBcfg.disc_mode=DISABLE;  /*modified*/
 ADC_PBcfg.wd_channelIndex=ADC_CHANNEL_0_;
 ADC_PBcfg.wd_single=ALL;
 ADC_PBcfg.scan_mode=DISABLE;
 ADC_PBcfg.wdi_en=DISABLE_INTERRUPT;
 ADC_PBcfg.eoc_en=DISABLE_INTERRUPT;
 ADC_PBcfg.allign_mode=RIGHT;
 ADC_PBcfg.DMA_req=DISABLE;
 ADC_PBcfg.wdj_en=DISABLE;
 ADC_PBcfg.discj_mode=DISABLE;
 ADC_PBcfg.jauto_mode=DISABLE;
 ADC_PBcfg.intj_en=DISABLE_INTERRUPT;
 ADC_PBcfg.external_trig_mode=SW_START;
 ADC_PBcfg.external_trig=ENABLE;
 ADC_PBcfg.externalj_trig=DISABLE;
 ADC_PBcfg.sample_select=T_1_PERIOD; /*1.5 cycle*/
 ADC_init(&ADC_PBcfg);

 /* Initializing DC Motor */
 DCMOTOR_init();
 /* Initializing FAN */
 Fan_init();
}

void reset_app(void)
{
   //CAR HEADLIGHTS
   Dio_WriteChannel(DioConf_HL1_CHANNEL_ID_INDEX,STD_HIGH); 
   Dio_WriteChannel(DioConf_HL2_CHANNEL_ID_INDEX,STD_HIGH);
   //car speed
    uint16 res_value_new=0;
   DcMotor_Rotate(CW,res_value_new, g_reset_speed_limit,TIM_3);
   //fan
   Fan_Rotate(STOP_FAN,TIM_2);
   //AC_State_Control
   Dio_WriteChannel(DioConf_COLD_CHANNEL_ID_INDEX,STD_HIGH); 
   Dio_WriteChannel(DioConf_MED_CHANNEL_ID_INDEX,STD_HIGH); 
   Dio_WriteChannel(DioConf_HOT_CHANNEL_ID_INDEX,STD_HIGH); 
   // door control
 //  Servo_Rotate(0);
   Dio_WriteChannel(DioConf_ENGINE_CHANNEL_ID_INDEX,STD_LOW); 
}
void Dashboard_Display()
{ 
  if(Emergency_Flag==DISABLED){
     
  if(speed_carrier<10)
  {
      LCD_displayStringRowColumn(1, 0, "Speed="); // Clear the area completely
      LCD_displayStringRowColumn(1,6,speed_display);
      LCD_displayCharRowColumn(1,8,' ');
      LCD_displayCharRowColumn(1,7,' ');
      reset_arr(speed_display,3);
  }
   else if(speed_carrier<100 &&speed_carrier>=10)
    {
       LCD_displayStringRowColumn(1, 0, "Speed="); // Clear the area completely
       LCD_displayStringRowColumn(1,6,speed_display);
       LCD_displayCharRowColumn(1,8,' ');
       reset_arr(speed_display,3);
    }
    else if (speed_carrier>=100)
    {
       LCD_displayStringRowColumn(1, 0, "Speed="); // Clear the area completely
      LCD_displayStringRowColumn(1,6,speed_display);
      reset_arr(speed_display,3);
    }
    if(Speed_limit_carrier<10)
    {
      LCD_displayStringRowColumn(2,0,"Max:");
      LCD_displayStringRowColumn(2,4,speed_limit_display);
      LCD_displayCharRowColumn(2,5,' ');
      LCD_displayCharRowColumn(2,6,' ');
      LCD_displayCharRowColumn(2,7,' ');
      reset_arr(speed_limit_display,3);
    }
    else if(Speed_limit_carrier<100 && Speed_limit_carrier>=10)
    {
      LCD_displayStringRowColumn(2,0,"Max:");
      LCD_displayStringRowColumn(2,4,speed_limit_display);
      LCD_displayCharRowColumn(2,6,' ');
      LCD_displayCharRowColumn(2,7,' ');
      reset_arr(speed_limit_display,3);
    }
    else if(Speed_limit_carrier>=100)
    {
      LCD_displayStringRowColumn(2,0,"Max:");
      LCD_displayStringRowColumn(2,4,speed_limit_display);
      LCD_displayCharRowColumn(2,7,' ');
      reset_arr(speed_limit_display,3);
    }
   
  switch(Engine_Flag)
  {
  case ENGINE_ON:
    LCD_displayStringRowColumn(0, 0, "Engine=");
    LCD_displayStringRowColumn(0, 7, "ON");
    LCD_displayCharRowColumn(0,9,' ');
    break;
  case ENGINE_OFF:
    LCD_displayStringRowColumn(0, 0, "Engine=");
    LCD_displayStringRowColumn(0, 7, "OFF");
    break;
    
  }
   switch(Door_Flag)
  {
  case DOOR_LOCK:
    LCD_displayStringRowColumn(3,5,"Door:");
    LCD_displayStringRowColumn(3,10,"Lock");
    LCD_displayCharRowColumn(3,14,' ');
    LCD_displayCharRowColumn(3,15,' ');
    break;
  case DOOR_UNLOCK:
   LCD_displayStringRowColumn(3,5,"Door:");
    LCD_displayStringRowColumn(3,10,"Unlock");
    break;
    
  }
    switch(AC_LVL_Flag)
  {
  case FAN_MEDIUM:
    LCD_displayStringRowColumn(1,11,"AC:");
    LCD_displayStringRowColumn(1,14,"Medium");
    break;
  case FAN_STOP:
    LCD_displayStringRowColumn(1,11,"AC:");
    LCD_displayStringRowColumn(1,14,"Stop");
    LCD_displayCharRowColumn(1,18,' ');
    LCD_displayCharRowColumn(1,19,' ');
    break;
  case FAN_HIGH:
    LCD_displayStringRowColumn(1,11,"AC:");
    LCD_displayStringRowColumn(1,14,"High");
    LCD_displayCharRowColumn(1,18,' ');
    LCD_displayCharRowColumn(1,19,' ');
    break;
    
  }
    switch(AC_State_Flag)
  {
  case FAN_COLD:
    LCD_displayStringRowColumn(2,9,"Mode:");
    LCD_displayStringRowColumn(2,14,"Cold");
    LCD_displayCharRowColumn(2,18,' ');
    LCD_displayCharRowColumn(2,19,' ');
    break;
  case FAN_HOT:
    LCD_displayStringRowColumn(2,9,"Mode:");
    LCD_displayStringRowColumn(2,14,"Hot");
    LCD_displayCharRowColumn(2,17,' ');
    LCD_displayCharRowColumn(2,18,' ');
    LCD_displayCharRowColumn(2,19,' ');
    break;
  case FAN_NORMAL:
    LCD_displayStringRowColumn(2,9,"Mode:");
    LCD_displayStringRowColumn(2,14,"Normal");
    break;
    
  }
   switch(Lights_Flag)
  {
  case LIGHTS_ON:
    LCD_displayStringRowColumn(0,11,"Light:");
    LCD_displayStringRowColumn(0,17,"ON");
    LCD_displayCharRowColumn(0,19,' ');
    break;
  case LIGHTS_OFF:
    LCD_displayStringRowColumn(0,11,"Light:");
    LCD_displayStringRowColumn(0,17,"OFF");
    break;
 
  }
  
  }
  else{
  switch(Emergency_Flag)
  {
  case ENABLED:
    LCD_displayStringRowColumn(1,5,"EMERGENCY");
    LCD_displayStringRowColumn(2,5,"ENABLED");
    Emergency_display();
    break;
  case DISABLED:
    /*Do nothing*/
    break;
 
  }
  }
     
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * find certain character in string 
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint8 * strChr (uint8 * data , uint8 sign)
{
  uint8 i=0;
  while (data[i]!='\0')
  {
    if (data[i]== sign )
    {
      return &data[i];
    }
    else 
    {
      i++;
    }
    
  }
  return NULL_PTR;
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * copy string to another 
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC void strCPY(uint8 *dest,uint8 *source)
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
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * compare 2 strings from start to limit 
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint8 strnCMP (uint8* str1 ,uint8* str2, uint8 limit)
{
  uint8 i=0;
  while (i!=limit)
  {
    if (str1[i]==str2[i])
    {
      i++;
    }
    else 
    {
      return 1;
    }
    
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * compare 2 strings  
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint8 strCMP (uint8* str1 ,uint8* str2)
{
  uint8 i=0;
  while (str1[i]!='\0' && str2[i]!='\0')
  {
    if (str1[i]==str2[i])
    {
      i++;
    }
    else 
    {
      return 1;
    }
    
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 * convert string to intger  
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint16 atoi(uint8* data)
{
    uint16 result = 0;  // Initialize result
    uint8 sign = 1;    // Initialize sign as positive
    uint8 i = 0;       // Index for iterating through the string

    // Handle whitespace characters
    while (data[i] == ' ' || data[i] == '\t' || data[i] == '\n') {
        i++;
    }

    // Handle optional sign
    if (data[i] == '-') {
        sign = -1;
        i++;
    } else if (data[i] == '+') {
        i++;
    }

    // Process each digit character
    while (data[i] >= '0' && data[i] <= '9') {
        result = result * 10 + (data[i] - '0');
        i++;
    }

    // Apply sign
    result *= sign;

    return result;

}
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  A static function used to reverse the passed string
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC void reverse(uint8* str, uint8 length)
{
	uint8 i, j;
	char temp;

	for (i = 0, j = length - 1; i < j; i++, j--) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  A static function used to convert integer to strings
 */
///////////////////////////////////////////////////////////////////////////////////////////
STATIC uint8* itoa(uint16 num, uint8* str, uint8 base)
{
	uint8 i = 0;

	/* Handle 0 explicitly */
	if (num == 0)
	{
		str[i] = '0';
		str[i + 1] = '\0';
		return str;
	}

	/* Add the null terminator */
	str[i] = '\0';

	/* Convert the number to the corresponding base */
	while (num != 0)
	{
		i = i + 1;
		uint8 rem = num % base;
		str[i] = rem + '0';
		num = num / base;
	}

	// Reverse the string
	reverse(str, i + 1);

	return str;
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  reset string
 */
///////////////////////////////////////////////////////////////////////////////////////////
void reset_string (uint8* string, uint8 length)
{
  uint8 i=0;
  while (string[i]!='\0')
  {
    string[i]='\0';
    i++;
  }
}
void reset_arr(uint8* string, uint8 length)
{
  uint8 i=0;
  for(uint8 i=0;i<length;i++)
  {
    string[i]='\0';
    
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  Senstitvity reduction of potentiometer (if saftey factor =15 and initial value=100 then if it become 102 it doesnot change but if it become 115 will change) 
 */
///////////////////////////////////////////////////////////////////////////////////////////
boolean If_Senstivity_reduced(uint16 num1,uint16 num2)
{
  
  if(num1>num2)
  {
  return ((num1-num2)>SAFETY_FACTOR);
  }
  else if(num1<num2)
  {
    return ((num2-num1)>SAFETY_FACTOR);
  }
  else
  {
    return FALSE;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Description :
 *  concatinate 2 string to be in one string
 */
///////////////////////////////////////////////////////////////////////////////////////////
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
void Emergency_display()
{
  uint8 cond=0;
  for(uint8 row_i=0;row_i<4;row_i++)
  {
    for(uint8 col_i=0;col_i<20;col_i++)
    {
      cond=0;
      if(((row_i==1) && (col_i>=5) && (col_i <14)) 
         ||((row_i==2) && (col_i>=5) && (col_i <12)))
      {
        cond=1;
      }
      if(cond==0)
      {
        LCD_displayCharRowColumn(row_i,col_i,' ');
      }
    }
  }
  
}
void Emergency_clear()
{
  uint8 cond=0;
  for(uint8 row_i=0;row_i<4;row_i++)
  {
    for(uint8 col_i=0;col_i<20;col_i++)
    {
      cond=0;
      if(((row_i==1) && (col_i>=5) && (col_i <14)) 
         ||((row_i==2) && (col_i>=5) && (col_i <12)))
      {
         LCD_displayCharRowColumn(row_i,col_i,' ');
      }
      if(cond==0)
      {
       
      }
    }
  }
  
}

/**-------------------Function Dec. Section END---------------------**/

