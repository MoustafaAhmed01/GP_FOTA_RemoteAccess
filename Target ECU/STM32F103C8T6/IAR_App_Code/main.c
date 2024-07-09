/***************************************************************************************************************************
*
* Module: Application Code - new
*
* File Name: main.c
*
* Description: Application code for Target ECU .
*
* Author: Shady Alaa
*
* Date: 7/2/2024
***************************************************************************************************************************/
#include "A9G.h"
#include "PLL.h"
#include "Dio.h"
#include "Port.h"
#include "Common_Macros.h"
#include "DMA.h"
#include "LPWAN.h"
#include "UART.h"
#include "UART2.h"
#include "CAN.h"
#define RESET_ENABLE 0x0001
/**-------------------------Macros----------------------------------**/
#define START_BOOTLOADER        'S'
#define BOOTLOADER_FLAG         0x424C  // 'BL' in ASCII
#define BOOTLOADER_ADDRESS      0x08000000
/**-------------------------Configuration Section-------------------**/
/* Initializing CAN as Interrupt
*
* MailBox_Number: MailBox_0                                   
* DLC: 4 Byte                                                    
* Identifier_Extention_Type: Standard
* Identifier: FIRMWARE_FILTER_Bank_ID                                       
* RTR: Data Frame
* Data_To_Be_Sent: 0x149C                               
*
*/
CAN_Frame_Ptr CAN_Transmitted_Data = { MailBox_1, FOUR_BYTE, Standard, FIRMWARE_Master_FILTER_ID, Dara_Frame, 0x149C};

/**-------------------------Global Variables Section----------------**/
/**-------------------------Function Dec. Section-------------------**/
//#include "TIM8_PWM.h"
/*-------------------------------------------------------------------*/
/*
* Description :
* Resets the stack pointer to the top of the stack
*/
void __set_MSP(uint32 topOfMainStack);
/*-------------------------------------------------------------------*/


/*
* Description :
* CAN1 receiver interrupt HANDLER
*/
void CAN1_RX0_IRQHandler(void);
/*-------------------------------------------------------------------*/
/*
* Description :
* Start the bootloader
*/
static void JumpToBootloaderHandler(uint32 Address);
/*-------------------------------------------------------------------*/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void Timer_4_ISR_Handler();
void Drivers_init(void);
void BKP_Init();

uint8 data[DATA_SIZE]={0};
uint8 lp_data[50]={0};
uint8 ix=0;
uint8 iy=0;
/* Bootloader Variables */
uint8 BootloaderActivate_Flag = FALSE;
/***Received arrays from A9G bus**/
uint8 Limiter_State_Cmd[60]="Limiter_State=false";
uint8 Speed_Limit_Cmd[60]="Speed_Limit=100";
uint8 Car_Speed_Cmd[60]={0};
uint8 AC_Level_Cmd[60]="AC_Level=Stop";
uint8 AC_State_Cmd[60]="AC_State=Normal";
uint8 Door_Ctrl_Cmd[60]="Door_Control=lock";
uint8 Emergency_State_Cmd[50]="ENABLED";
uint8 Car_Engine_Cmd[50]="ENABLED";
uint8 Emergency_State_Flag=0;
uint8 Car_Engine_Flag=0;
uint8 Car_Engine_ACK=0;
uint8 Limiter_State_Flag=0;
uint8 AC_State_Flag=0;
uint8 AC_Level_Flag=0;
uint8 Door_Control_Flag=0;
uint8 Speed_Limit_Flag=0;
//uint8 reset_flag=0;
extern uint8 GPS_Flag;

/********************************************Functions Declaration*******************************************************/
/***********************************************************************************************************************
*Function Id: Send_Data
*Description: Senses if any data updated via Mobile App (Door control , AC state , AC Level , Speed Limit)
*             by reading a specific flag for each feature , if setted then send command control through the
*             LPWAN.
************************************************************************************************************************/
void Send_Data();
/***********************************************************************************************************************
*Function Id: LPWAN_Read
*Description: Responds for a speed change sent by the slave microcontroller that handles the whole features
*             ,Separates the carried information from the string which is delimited by a hash symbol. 
*             
************************************************************************************************************************/
void LPWAN_Read(uint8 *str);
/*******************************************Helpful functions used ****************************************************/
STATIC void strCPY(uint8 *source,uint8 *dest);
STATIC void resetBuffer(uint8 *buffer_start);
STATIC void get_string(uint8 *str,uint8 *sub_str,uint8 start_char,uint8 end_char);
/*********************************************************************************************************************/
/* Global variable to receive Car Speed inside */
uint8 g_LPWAN_RECEIVE_SPEED[50];
/* Variable to receive the lpwan ID */
uint8 g_LPWAN_RECEIVE_ID;
/* If it was the first time to receive then receive the ID first */
uint8 g_LPWAN_ID_FLAG = 0;
/* If the ID was correct SET flag */
uint8 g_LPWAN_CORRECT_ID =0;
/* Used to know if we have received DATA or NOT */
uint8 g_UART_RECEIVE_FLAG = 0;
/********************************************************************************************************************/

int main(void)
{   
  Drivers_init();
  
  if(A9G_Init())
  {  
    if(A9GtoNetwork())
    {
      //  A9G_GPS();  //Switching On GPS   
      LCD_clearScreen();
      LCD_displayString("Have a");
      LCD_displayStringRowColumn(1,1,"Nice Ride");
      Delay_MS(500);
      
      while(1)
      {
        Send_Data();  
        
         /* Check on the bootloader */
        if(BootloaderActivate_Flag == TRUE)
        {
          BKP_DR3 = RESET_ENABLE;
          LCD_clearScreen();
          LCD_displayString("Jumping to bootloader");
          BootloaderActivate_Flag = FALSE;
          JumpToBootloaderHandler(BOOTLOADER_ADDRESS);
        }
        else
        {
          /* Do nothing */
        }
      }
    }
    else
    {
      LCD_clearScreen();  
      LCD_displayString("Network Error");
      while(1){}
    }
    
  }
  else
  {
    LCD_clearScreen(); 
    LCD_displayString("Init error");
    while(1){}
  }
  
}

/*-------------------------------------------------------------------*/

/*
* Description :
* CAN1 receiver interrupt HANDLER
*/
void CAN1_RX0_IRQHandler(void)
{
  /* Do Nothing */
  if( ( CAN1_RF0R & (0x00000003) ) != 0 )
  {
    uint32 Filter_Bank_ID = CAN1_RDT0R >> FMI;
    uint32 DLC_Length = CAN1_RDT0R >> DLC;
    uint8 CAN_RECEIVED = 0;
    
    /* Check if this is the required filter */
    if( Filter_Bank_ID == FIRMWARE_Target_FILTER_Bank_Number )
    {
      CAN_RECEIVED = CAN1_RDL0R;
      if(CAN_RECEIVED == START_BOOTLOADER)
      {
        BootloaderActivate_Flag = TRUE;
      }
      
    }
    else
    {
      /* Do Nothing */
    }
    /* Release the mailbox */
    SET_BIT(CAN1_RF0R,RFOM0);
  }
}

void USART2_IRQHandler(void)
{  
  if(BIT_IS_SET(USART_2_SR_REG,RXNE))
  {
    CLEAR_BIT(USART_2_SR_REG,RXNE);
    data[ix]=USART_2_DR_REG;
    ix++;
    
  }
  else if (BIT_IS_SET(USART_2_SR_REG,IDLE))
  {
    volatile uint32 tmp_read=0;
    /* Clear Register Manually */
    CLEAR_BIT(USART_2_SR_REG , IDLE);
    tmp_read=USART_2_SR_REG;   
    tmp_read=USART_2_DR_REG;
    /* Re-init the DMA again */
    DMA_Disable(&DMA_7_Configurations);
    DMA_resetCNDTR(&DMA_7_Configurations);
    A9G_MQTTread(Data_Array);
    DMA_Enable(&DMA_7_Configurations);     
  }
  
}
void USART1_IRQHandler(void)
{ 
  if (BIT_IS_SET(USART_1_SR_REG,IDLE))
  {
    volatile uint32 tmp_read=0;
    /* Clear Register Manually */
    tmp_read=USART_1_SR_REG;   
    tmp_read=USART_1_DR_REG;
    CLEAR_BIT(USART_1_SR_REG , IDLE);
    /* Re-init the DMA again */
    DMA_Disable(&DMA_Configurations);
    LPWAN_Read(LPWAN_Data);
    DMA_resetCNDTR(&DMA_Configurations);
    DMA_Enable(&DMA_Configurations);     
  }              
}
void LPWAN_Read(uint8 *str)
{
  if(str[0]==LPWAN_ID)
  {
    uint8 *str_ptr=str+1;
    if(response_compare(str_ptr,"Car_Speed=",10))
    {
      resetBuffer(Car_Speed_Cmd);   
      get_string(str_ptr,Car_Speed_Cmd,'=','#');  //'#' is the delimiter
      A9G_PublishSpeed(Car_Speed_Cmd);
    }
    else if(response_compare(str_ptr,"Emergency_Ack=",14))
    {
      
      if(response_compare(str_ptr,"Emergency_Ack=ENABLED",21))
      {
        A9G_PublishSpeed("0");
        A9G_PublishEmergency("ENABLED");
        A9G_PublishEngine("false");
        Car_Engine_Flag=0;
        A9G_EmergencyActs();
      }
      else if(response_compare(str_ptr,"Emergency_Ack=DISABLED",22))
      {
        A9G_PublishEmergency("DISABLED");
        
      }
    }
    else if(response_compare(str_ptr,"Car_State=",10))
    {   LCD_clearScreen();       //Testing
    LCD_displayString(str);  //Testing
    Delay_MS(1000);          //Testing
    Car_Engine_Flag=0;
    if(response_compare(str_ptr,"Car_State=ON",12))
    {
      A9G_PublishEngine("true");
      Car_Engine_Flag=1;
    }
    else if(response_compare(str_ptr,"Car_State=OFF",13))
    {
      A9G_PublishEngine("false");
      Car_Engine_Flag=0;
    }
    }
  }
  else
  {
    /* Do nothing*/
  }
  
}
void Send_Data()
{
 
  if(Car_Engine_Flag==1)
  {
    if(Speed_Limit_Flag==1)
    {
      LCD_clearScreen();
      LCD_displayString(Speed_Limit_Cmd);
      //    Delay_MS(1000);
      Str_Cat(Speed_Limit_Cmd,"#",Speed_Limit_Cmd);
      LPWAN_SendFrame(Speed_Limit_Cmd);  
      Speed_Limit_Flag=0;
    }
    if(AC_Level_Flag==1)
    {
      LCD_clearScreen();
      LCD_displayString(AC_Level_Cmd);
      //  Delay_MS(1000);
      Str_Cat(AC_Level_Cmd,"#",AC_Level_Cmd);
      LPWAN_SendFrame(AC_Level_Cmd);
      AC_Level_Flag=0;
    }
    if(AC_State_Flag==1)
    {
      LCD_clearScreen();
      LCD_displayString(AC_State_Cmd);
      //   Delay_MS(1000);
      Str_Cat(AC_State_Cmd,"#",AC_State_Cmd);
      LPWAN_SendFrame(AC_State_Cmd);   
      AC_State_Flag=0;
    }
    if(Door_Control_Flag==1)
    {
      LCD_clearScreen();
      LCD_displayString(Door_Ctrl_Cmd);
      //   Delay_MS(1000);
      Str_Cat(Door_Ctrl_Cmd,"#",Door_Ctrl_Cmd);
      LPWAN_SendFrame(Door_Ctrl_Cmd);    
      Door_Control_Flag=0;
    }   
  }
  if(Emergency_State_Flag==1)
  {
    LCD_clearScreen();
    LCD_displayString(Emergency_State_Cmd);
    //  Delay_MS(1000);
    Str_Cat(Emergency_State_Cmd,"#",Emergency_State_Cmd);
    LPWAN_SendFrame(Emergency_State_Cmd);
    Emergency_State_Flag=0;
  }
  if(Car_Engine_ACK==1)
  {
    LCD_clearScreen();
    LCD_displayString(Car_Engine_Cmd);
    //   Delay_MS(1000);
    Str_Cat(Car_Engine_Cmd,"#",Car_Engine_Cmd);
    LPWAN_SendFrame(Car_Engine_Cmd);
    Car_Engine_ACK=0;
  }
}
/***********************************************************************************************************************************************/
/***************************************************************Helpful Functions*****************************************************************/
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
  sub_str[j]='\0';
}
STATIC void strCPY(uint8 *source,uint8 *dest)
{
  uint8 len1=0;
  uint8 len2=0;
  resetBuffer(dest);
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
STATIC void resetBuffer(uint8 *buffer_start)
{
  for(uint8 i=0;buffer_start[i]!='\0';i++)
  {
    buffer_start[i]='\0';
    
  }
  
}
void BKP_Init()
{
 // Initialize the backup domain and access backup registers
  RCC_APB1ENR |=  (1<<28) | (1<<27); /* Activates the PWR control clock and BKP register*/
  
  /*
  * DBP: Disable backup domain write protection.
  * In reset state, the RTC and backup registers are protected against parasitic write access. 
  * This bit must be set to enable write access to these registers.
  * 0: Access to RTC and Backup registers disabled
  * 1: Access to RTC and Backup registers enabled
  */
  PWR_CR |= (1<<8);
}
/* Init all drivers */
void Drivers_init(void)
{
  Port_Init(&Port_Configuration);
  Dio_Init(&Dio_Configuration);
  SystemClockInit();
  UART2_ConfigType config2 = { INTERRUPT_2 , DATA_8_Bits_2 , Disable_2 , Even_Parity_2 , One_Stop_Bit_2 , IDLEI_DISABLE_2 ,DMA_RX_Enable_2, RXNEI_ENABLE_2 , TCI_DISABLE_2 ,TXEI_DISABLE_2 , PEI_DISABLE_2 , 115200 , 3};
  UART2_init(&config2);
  LPWAN_Init();
  DMA_Init(&DMA_Configurations);
  DMA_resetBuffer(LPWAN_Data);
  LCD_init();
  LCD_displayString("Init...");
  BKP_Init();
  CAN_Init(&CAN_Configurations);
}
/** ---------------------------- Bootloader section ------------------------------ **/

void JumpToBootloaderHandler(uint32 Address){
  
  // Initialize the backup domain and access backup registers
  RCC_APB1ENR |=  (1<<28) | (1<<27); /* Activates the PWR control clock and BKP register*/
  
  /*
  * DBP: Disable backup domain write protection.
  * In reset state, the RTC and backup registers are protected against parasitic write access. 
  * This bit must be set to enable write access to these registers.
  * 0: Access to RTC and Backup registers disabled
  * 1: Access to RTC and Backup registers enabled
  */
  PWR_CR |= (1<<8);
  
  // Set the bootloader flag
  BKP_DR2 = BOOTLOADER_FLAG;
  
  
  // Disable all interrupts
  __disable_irq();
  
  // Set the vector table location to the bootloader address
  SCB_VTOR = Address;
  
  // Load the stack pointer address from the bootloader's vector table
  __set_MSP(*((volatile uint32*)Address));
  
  // Get the reset handler address from the bootloader's vector table
  uint32 bootloader_reset_handler = *((volatile uint32*) (Address + 4));
  
  // Jump to the bootloader's reset handler
  ((void (*)(void))bootloader_reset_handler)();
  
  // If we ever return, disable all interrupts and enter an infinite loop
  __disable_irq();
  while (1);
}
/**------------------------------------------------------**/

// Function to set Main Stack Pointer (MSP)
void __set_MSP(uint32 topOfMainStack) {
  __asm volatile ("msr msp, %0" : : "r" (topOfMainStack) : );
}

/*************************************************Testing Section*******************************************************************************/
