/*AUTHOR:SEIF AYMAN
file: MAIN file for target mcu

 Includes ------------------------------------------------------------------*/

#include "Dio.h"
#include "bootloader.h"
#include "Port.h"
#include "watchdog.h"
#include "PLL.h"
#include "CAN.h"
/* Private includes ----------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/**-------------------------------Macros----------------------------------**/

/**-------------------------Global Variables Section----------------------**/


/**-------------------------Configuration Section-------------------**/

/**----------------------------Function Decleration--------------------------------**/
/*
 * Description :
 * The Interrupt Service Routine to handle the received data in the CAN FIFO 0
 */
void CAN1_RX0_IRQHandler(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Initializing everything
 */
void Drivers_Init(void);

/**-------------------------------MAIN---------------------------**/
int main(void)
{
  Drivers_Init();
  
  /* Tell the user that we are in the Bootloader */
  LCD_clearScreen();
  LCD_displayString("Bootloader Code!");
  Delay_MS(250);
  BL_fetchHostCommand();
  while (1)
  {
    
  }
}

/**-------------------------Function Definition Section-------------**/
void Drivers_Init(void)
{
  /* Initialize PORT Driver */
  Port_Init(&Port_Configuration);
  
  /* Initialize DIO Driver */
  Dio_Init(&Dio_Configuration);
  
  /* Setting MCU clock to 72 MHz */
  SystemClockInit();  
  
  /* Init the CAN BUS */
  CAN_Init(&CAN_Configurations);
  
  /* Init LCD */
  LCD_init();
  /* Stop the watchdog timer */
  IWDG_Stop();
}
/*-------------------------------------------------------------------*/
/*
 * Description :
 * The Interrupt Service Routine to handle the received data in the CAN FIFO 0
 */
void CAN1_RX0_IRQHandler(void)
{
  /* Do Nothing */
  if( ( CAN1_RF0R & (0x00000003) ) != 0 )
    {
      uint32 Filter_Bank_ID = CAN1_RDT0R >> FMI;
      uint32 DLC_Length = CAN1_RDT0R >> DLC;
      
      /* Check if this is the required filter */
      if( Filter_Bank_ID == FIRMWARE_Target_FILTER_Bank_Number )
      {
        /* This is the received data from the desired filter */
        //Rx_Data = CAN1_RDL0R;
      }
      else
      {
        /* Do Nothing */
      }
      /* Release the mailbox */
      SET_BIT(CAN1_RF0R,RFOM0);
    }
}
/*-------------------------------------------------------------------*/