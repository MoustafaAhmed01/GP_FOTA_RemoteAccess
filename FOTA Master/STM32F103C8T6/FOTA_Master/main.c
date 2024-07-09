/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: FotaMaster.c
 *
 * Description: types for ARM
 *
 * Date Created: 12/5/2024
 *
 * Author: Ahmed/Moustafa
 *
 *******************************************************************************/
/**-------------------------INCLUDES Section------------------------**/
#include "Port.h"
#include "Dio.h"
#include "UART.h"
#include "LCD.h"
#include "PLL.h"
#include "Delay.h"
#include "DMA.h"
#include "keypad_enhanced.h"
#include "CAN.h"

/**-------------------------Macros----------------------------------**/
#define MEGA 1000000
#define DMA_Reception_Buffer_Size 200


#define Selected_Network_Accepted                 'B' 
#define No_Internet_Networks_Found                'C' 
#define Internnet_Connected_Successfuly           'D' 
#define Internnet_Connection_Failed               'E' 
#define Failed_To_Subscribe_To_Topics             'W'

#define New_Update_Is_Found                       'F' 
#define New_Update_Is_Not_Found                   'G' 

#define Confirm_Download_NewFirmware              'T' 

#define Ack_For_NextLine                          'A' 
#define Negative_ACK                              'u'

#define Failed_To_Open_The_File                   'L'
#define File_Exceeds_The_Max_File_Allowed         'M'
#define Connection_Lost_While_Downloading         'N'

#define NodeMcu_will_Send_Line                    'o'
#define FotaMaster_Is_Ready_to_Recieve_Line       'p'
#define End_Of_Transmitting                       'k'

#define Send_Target_Name                          'x'
#define Send_File_Size                            'h'
#define Start                                     'v'  
#define Ready                                     'R'

#define File_Is_Opened                            'y'

/* Bootloader */
#define HEX_Constant_Start              4
#define ACK_BL                          0xCD
#define NACK_BL                         0xAB
#define CBL_GET_VER_CMD                 0x10
#define CBL_GET_HELP_CMD                0x11
#define CBL_GET_CID_CMD                 0x12
#define CBL_GO_TO_ADDR_CMD              0x14
#define CBL_FLASH_ERASE_CMD             0x15
#define CBL_MEM_WRITE_CMD               0x16
#define CBL_BL_STOP_CMD                 0x36
#define TARGET_READY                    0x17
#define MASTER_READY                    0x18
/* Target main */                    
#define START_BOOTLOADER                'S'
#define CONTROL_READY                   0xF1

/* Vector table for bootloader */
#define Startup_Code                    0x27

/**-------------------------Global Variables Section----------------**/

/* Global variable to receive the data */
uint8 Start_Transmitting_FW = 0;       
//uint8 End_Of_Transmitting = 0;
uint8 Succefully_Installed = 0;
uint8 Data_Array[DMA_Reception_Buffer_Size] = {0};
uint8 Target_Name[5] = {0};
uint8 Internet_Connected = 0;
int c = 0;

/* Global variables used to Control the keypad mdoes */
uint8 Keypad_Mode = 'D'; /* Default mode */
uint8 Keypad_CAP = 'S'; /* S small letters / C Capital Letters */

/* Bootloader */
#define MAX_Buffer_Size 30
uint8 HEX_File_Data_Size = 0;
/* Buffer that will be sent to the Bootloader */
uint8 BL_BUFFER[MAX_Buffer_Size] = {0};
/* Fixing the vector table flag */
 uint16 vect_counter_handler = 0x00;
 uint8 BL_Flag = 0; /* Used to erase the target one time only */
 
 int z = 0;
 uint32 percentage = 0;
 uint32 Size = 0;
/**-------------------------Configuration Section-------------------**/


/* Initializing DMA 
* 
* DMA number : DMA 1
* Channel Number: 5
* Channel Priority: High (2)
* Memory Buffer Size: 8bits (0)
* Peripheral Buffer Size: 8bits (0)
* Memory Increament: Enable (1)
* Peripheral Increament: Disable (0)
* Circular Mode: Enable (1)
* DMA Direction: Read from peripheral 
* Transfer Number :16 
* Memory Buffer Address: which needs a casting of uint32
* Peripheral Buffer Address: which needs a casting of uint32
*/
DMA_ConfigType DMA_Configuration = { DMA_1, DMA_CHANNEL_5, Very_High, Bits_8, Bits_8, D_Enable, D_Disable, D_Disable, Read_From_Peripheral, 2048, (uint32)(Data_Array), (uint32)&USART_1_DR_REG };

/**-----------------------------------------------------------**/
/* Initializing UART as Interrupt
  *
  * UART_RECEIVE_INT : No
  * UART_TRANSMIT_INT : NO
  * UART_EMPTY_INT : No
  * UART_RECEIVER : Yes
  * UART_TRANSMITTER : Yes
  * UART_CharSize : 8-bit
  * UART_MODE_SELECT : A-sync
  * UART_PARITY_SELECT : No
  * UART_STOP_BIT_SELECT : 1-bit
  * UART_CLOCK_POLARITY : A-sync Rising
  * baud_rate : 115200
  *
  */
  UART_ConfigType Uart_configuration = { POLLING , DATA_8_Bits , Disable , Even_Parity , One_Stop_Bit , IDLEI_DISABLE, NO_DMA , RXNEI_DISABLE , TCI_DISABLE ,TXEI_DISABLE , PEI_DISABLE , 115200 , 3};
  
 /**-----------------------------------------------------------**/
/**-----------------------------------------------------------**/

/* Initializing CAN as Interrupt
  *
  * MailBox_Number: MailBox_0                                   
  * DLC: 1 Byte                                                    
  * Identifier_Extention_Type: Standard
  * Identifier: FIRMWARE_FILTER_Bank_ID                                       
  * RTR: Data Frame
  * Data_To_Be_Sent: 0x149C                               
  *
  */
CAN_Frame_Ptr CAN_Transmitted_Data = { MailBox_1, FOUR_BYTE, Standard, FIRMWARE_Target_FILTER_ID, Dara_Frame, 0x149C};
 
/**-------------------------Function Dec. Section-------------------**/
/*
 * Description :
 * The Interrupt Service Routine to handle the received data in the CAN FIFO 0
 */
void CAN1_RX0_IRQHandler(void);

/*-------------------------------------------------------------------*/
/*
 * Description :
 * Function is being called after receiving a line
 */
uint8 Received_HEX_Line_Handler(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Checksum
 */
uint8 HEX_CheckSum(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Request from the Bootloader to delete everything
 */
void BL_MAX_ERASE(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Request from the Bootloader to write the array
 */
uint8 BL_WRITE(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Request from the Bootloader to STOP
 */
uint8 BL_END_FILE(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Sends the buffer through the UART
 */
uint8 BL_Buffer_Send(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Generates the checksum for the required buffer
 */
void BL_Buffer_CheckSum(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Erase the Buffer
 */
void BL_Buffer_Clear(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Get the buffer size
 */
uint8 BL_Buffer_GET_SIZE(void);
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Handling Keypad UI
 */
uint8 Keypad_Handler(void);
  
/*
 * Description :
 * The Interrupt Service Routine to handle the received data in the UART data register which will be also used with DMA
 */
void USART1_IRQHandler(void);

/*-------------------------------------------------------------------*/

/*
 * Description :
 * Initializing everything
 */
void Drivers_Init(void);

/*
 * Description :
 * Used to remove the garbage sent by NodeMcu
 */
void Remove_File_Garbage(uint8* file);

/*
 * Description :
 * To show the menu in the LCD
 */
void Show_Menu_Options();

/*
 * Description :
 * Used to send a request to the NodeMcu to get the availabl Wifi networks in the surround
 */
void Request_For_Available_Networks();

/*
 * Description :
 * Used to show available wifi networks on the LCD screen
 */
void Show_Wifi_Networks();

/*
 * Description :
 * Used to Check for new updates
 */
void Check_For_Updates();

/*
 * Description :
 * Used to receive the new line
 */
void Receive_Line();
/**-------------------Function Dec. Section END---------------------**/


/**------------------------------MAIN-------------------------------**/
int main()
{ 
  /**-----------------------Main Section-------------------------**/
  /* Initializing Drivers at first */
  Drivers_Init();
  
  while(1)
  {
    /* Show all the menu option to the user */
    Show_Menu_Options();
  }
}

/**-------------------------Function Definition Section-------------**/

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
      if( Filter_Bank_ID == FIRMWARE_Master_FILTER_Bank_Number )
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
/*
 * Description :
 * The Interrupt Service Routine to handle the received data in the UART data register
 */
void USART1_IRQHandler( void )
{
    /* Check if the USART1 receive interrupt is pending */
    if ( BIT_IS_SET(USART_1_SR_REG , IDLE) )
    {
      /* Clear Register Manually */
      CLEAR_BIT(USART_1_SR_REG , IDLE);
      
      if(Start_Transmitting_FW == 1)
      {
        /* Call the line parsing function */
        /* in this function it should send via uart the ack as the nodemcu wait it */
        /* the ack should be sent after the function recieves confirmation from the target */
        /* then send send the ack to the NodeMcu */
        /* After full transmission or failure the function should set End_Of_Transmitting to 1 */
        /* Also it should set a flag that indicates for failure or succefull installing */
        //Delay_MS(1000);
      }
      
      /* Re init the DMA again */
      DMA_ReInit(DMA_Configuration);
    }
    else
    {
      /* Do nothing */
    }
}
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/

/*
 * Description :
 * Initializing everything
 */
void Drivers_Init(void)
{
  /* Initialize PORT Driver */
  Port_Init(&Port_Configuration);
  
  /* Initialize DIO Driver */
  Dio_Init(&Dio_Configuration);
  
    /* Setting MCU clock to 72 MHz */
  SystemClockInit();
  
  /* Initialize LPWAN */
  UART_init(&Uart_configuration);
  
  /* Initialize the CAN */
  CAN_Init(&CAN_Configurations);
  
  /* Initializing LCD */
  LCD_init();
}

/*
 * Description :
 * Used to receive the new line
 */
void Receive_Line()
{
  uint8 i = 0; 
  
  // : 02 00 00 04 08 00 F2
  // : 10 00 10 00 FB 1D 00 08 13 20 00 08 8F 22 00 08 00 00 00 00 CC
  
  while(1)
  {
    Data_Array[0] = UART_recieveByte();
    
    Data_Array[1] = UART_recieveByte();
    for( i = 2; i <= (Data_Array[1] + 4 + 1) ;i++)
    {
      Data_Array[i] = UART_recieveByte();
    }
    Data_Array[i] = '\0';
    return;
  }
}

/*
 * Description :
 * Used to remove the garbage sent by NodeMcu
 */
void Remove_File_Garbage(uint8* file)
{
  c = 0;
  int i = 0;  
  while(i<DMA_Reception_Buffer_Size)
  {
    if( file[i] == 's' && file[i+1] == 't' && file[i+2] == 'a' && file[i+3] == 'r' && file[i+4] == 't' )
      break;
    i++;
  }
  if ( file[i] != 's' || file[i+1] != 't' || file[i+2] != 'a' || file[i+3] != 'r' || file[i+4] != 't' )
  {
    return;
  }
  c = i;
  i=0;
  while(i < DMA_Reception_Buffer_Size-c)
  {
    if( file[i] == 'e' && file[i+1] == 'n' && file[i+2] == 'd' )
      break;
    else
    {
      file[i] = file[c];
      //file[c] = 0;
      i++;
      c++;
    }
  }  
  if( file[i] == 'e' && file[i+1] == 'n' && file[i+2] == 'd' )
  {
    file[i] = 0;
    file[i+1] = 0;
    file[i+2] = 0;
  }
}

void  Check_For_Updates()
{
  if(Internet_Connected == 1)
  {
    LCD_clearScreen();
    LCD_displayStringRowColumn(0,0,"Checking new ");
    LCD_displayStringRowColumn(1,0,"updates.....");
    Delay_MS(1500);
    
    UART_sendByte('B');
    uint8 New_Update_Found = UART_recieveByte();
    
    if( New_Update_Found == New_Update_Is_Found)
    {
      LCD_clearScreen();
      LCD_displayString("Update is found");
      Delay_MS(2000);
      
      while (1)
      {
        LCD_clearScreen();
        LCD_displayStringRowColumn(0,0,"Install Now ?");
        LCD_displayStringRowColumn(1,0,"A-Yes B-No C-Return");
        Delay_MS(1000);
        
        uint8 Selceted_Option = Keypad_Handler(); 
        if(Selceted_Option == 'A')
        {
          /* Erase all the stored elements in the array */
          uint16 i = 0;
          for(i = 0; i < DMA_Reception_Buffer_Size; i++)
          {
            Data_Array[i] = 0;
          }
          i = 0;
                    
          LCD_clearScreen();
          LCD_displayString("Installing...");
                              
          uint8 Ack_Button = 0;
          
          /* Send to NodeMcu to start transmitting */        
          UART_sendByte(Confirm_Download_NewFirmware);
          
          UART_sendByte(Send_Target_Name);
          UART_receiveString(Target_Name);
          LCD_displayStringRowColumn(1,0,"Target ECU is ");
          LCD_displayStringRowColumn(1,14,Target_Name);
          //LCD_displayString(Target_Name);
                    
          char x;
          
          x= UART_recieveByte();
          
          if(x == File_Is_Opened)
          {
            /* Do Nothing */
          }
          else if(x == Failed_To_Open_The_File)
          {
            LCD_clearScreen();
            LCD_displayString("Failed to open the file");
            Delay_MS(1000);
            return;
          }
          
          uint8 File_Size[10] = {0};
          UART_sendByte(Send_File_Size);
          UART_receiveString(File_Size);
          
          Size = ((File_Size[0] - '0')*1000)+((File_Size[1] - '0')*100)+((File_Size[2] - '0')*10)+((File_Size[3] - '0')*1);        
          LCD_displayStringRowColumn(2,0,"Installing...");
          UART_sendByte(Start); 
          
          while(1)
          {
            x = UART_recieveByte();
            if( x == NodeMcu_will_Send_Line)
            {
              //
              //UART_receiveString(Data_Array);
              //
              
              Receive_Line();
              /******************************************/
              Ack_Button = Received_HEX_Line_Handler();
              /******************************************/
              //Ack_Button = Keypad_Handler();
              
              if(Ack_Button == TRUE)
              {
                /* Erase all the stored elements in the array */
                for(i = 0; i < DMA_Reception_Buffer_Size; i++)
                {
                  Data_Array[i] = 0;
                }
                i = 0;
                percentage++;
                z = ( (percentage*100) /Size ) ;
                LCD_moveCursor(2,13);
                LCD_intgerToString(z);
                LCD_displayCharacter('%');
                      
                /* Change the array to hex then call the parsing function */
                UART_sendByte(Ack_For_NextLine);
              }
              else
              {
                /* Send
 to NodeMcu to end the transmitting */
                UART_sendByte(Negative_ACK);
                return;
              }
            }
            else if( x == End_Of_Transmitting)
            {
              Succefully_Installed = 1;
              LCD_displayStringRowColumn(2,0,"Installing...100%");
              Delay_MS(2000);
              break;
            }
            else if ( x == Failed_To_Open_The_File )
            {
              LCD_clearScreen();
              LCD_displayStringRowColumn(0,0,"Failed to open the File");
              Delay_MS(2000);
              break;
            }
          }
       
          if (Succefully_Installed == 1)
          {
            /* Show to the user that the transmission is done */
            LCD_clearScreen();
            LCD_displayString("Installing ");
            LCD_displayStringRowColumn(1,0,"is done !!");
            Delay_MS(5000);
            
            /* Set_transmitting flag to 0 */
            Start_Transmitting_FW = 0;
          }
          else
          {
            /* Show to the user that the installation has been failed */
            LCD_clearScreen();
            LCD_displayString("Failed to ");
            LCD_displayStringRowColumn(1,0,"install");
            Delay_MS(2000);
            
            /* Set_transmitting flag to 0 */
            Start_Transmitting_FW = 1;
            
          }
          return;
          
        }
        else if (Selceted_Option == 'B')
        {
          return;
        }
        else if (Selceted_Option == 'C')
        {
          return;
        }
        else
        {
          LCD_clearScreen();
          LCD_displayString("Select A or B");
          LCD_moveCursor(1,0);
          LCD_displayString("only");
          Delay_MS(2000);
        }
      }
    }
    else if( New_Update_Found == New_Update_Is_Not_Found)
    {
      LCD_clearScreen();
      LCD_displayString("Up to date");
      Delay_MS(2000);
      return;
    }
  }
  else
  {
    LCD_clearScreen();
    LCD_displayString("Wifi is not");
    LCD_displayStringRowColumn(1,0,"Connected");
    Delay_MS(2000);
    return;
  }
}

/*
 * Description :
 * Used to show available wifi networks on the LCD screen
 */
void Show_Wifi_Networks()
{
  LCD_clearScreen();
  uint8 i = 0;
  uint8 row = 0;
  LCD_displayCharRowColumn(0,0,'1');
  while (Data_Array[i] != '\0')
  {
    while(Data_Array[i] != '\n' && Data_Array[i] != '\r')
    {
      LCD_displayCharacter(Data_Array[i]);
      i++;
    }
    i++;
    if(Data_Array[i] =='\n')
    {
      row++;
      LCD_moveCursor(row,0);
    }
    if(row == 4 )
    {
      Delay_MS(2000);
      LCD_clearScreen();
      
      row = 0; 
    }
  }
  
  LCD_clearScreen();
  LCD_displayStringRowColumn(0,0,"Select from prev");
  LCD_displayStringRowColumn(1,0,"or # to reshow");
  
}

/*
 * Description :
 * Used to send a request to the NodeMcu to get the available Wifi networks in the surround
 */
void Request_For_Available_Networks()
{
  /* Show screen to the user indicates that scanning begun */
  LCD_clearScreen();
  LCD_displayStringRowColumn(0,0,"Scanning.....");
    
  while(1)
  {
    /* Erase all the stored elements in the array */
    uint16 i = 0;
    for(i = 0; i < DMA_Reception_Buffer_Size; i++)
    {
      Data_Array[i] = 0;
    }
    i=0;
    
    /* Send to NodeMcu the scan for available networks */
    UART_sendByte('A');
      
    char Networks_Found = UART_recieveByte();
    
    if(Networks_Found == No_Internet_Networks_Found)
    {
      LCD_clearScreen();
      LCD_displayString("No internet ");
      LCD_displayStringRowColumn(1,0,"is Found");
      return;
    }
    
    /* Receive the available network that the NodeMcu scanned them */
    UART_receiveString(Data_Array);
    Internet_Connected = 0;
        
    /* Show on the screen the received networks */
    Show_Wifi_Networks();
    
    /* Get from the user the desired network that he wants to connects to */
    uint8 Selected_Option = Keypad_Handler();

    if( Selected_Option == '#' )
    {
      /* Do nothing just stay in the loop and don't break */
      /* 
         Note that the FOTA Master will send 'A' via the UART and
         the NodeMcu expect to has a number from 1-8 else it will scan again 
         for available networks and resend it again 
      */   
    }
    else if( Selected_Option > '8' && Selected_Option < '0' )
    {
      /* If the user selects a wrong number rather than 1-8 */
      LCD_clearScreen();
      LCD_displayStringRowColumn(0,0,"press (1-8)");
      Delay_MS(1000);
      LCD_clearScreen();
      LCD_displayStringRowColumn(0,0,"Select from prev");
      LCD_displayStringRowColumn(1,0,"or # to reshow");
      
      /* 
          Note that also here when the user enters a wrong number 
          the FOTA Master will remain in the loop and resend 'A' which is not from 1-8 
          So the NodeMcu will scan once more and send the scanned wifi networks
      */
    }
    else if(Selected_Option <= '8' && Selected_Option > '0')
    {
      /* When the user enters a correct choice  */
      UART_sendByte(Selected_Option);
      /* Wait for the approval from the NodeMcu on the selected network */
      while (UART_recieveByte() != Selected_Network_Accepted);
      
      LCD_clearScreen();
      LCD_displayStringRowColumn(0,0,"Insert Password:");
      LCD_moveCursor(1,0);
       
       /* get password from user */
      uint8 pass[20] = {0};
      uint8 i = 0;
      uint8 cursor = 0;
      while(1)
      {
        //Delay_MS(150);
        pass[i] = Keypad_Handler();
        if(pass[i] == '#')
        {
          break;
        }
        else if (pass[i] == 'D')
        {
          i = i-1;
          cursor = cursor - 1;
          LCD_displayCharRowColumn(1,cursor,' ');
          LCD_moveCursor(1,cursor);
        }
        else
        {
          LCD_displayCharRowColumn(1,cursor,pass[i]);
          Delay_MS(150);
          LCD_moveCursor(1,cursor);
          LCD_displayCharacter('*');
          cursor++;
          i++;
        }
      }
      /* Send the Password */
      UART_sendString(pass);
      
      LCD_clearScreen();
      LCD_displayString("Connecting...");
      
      uint8 Connected = UART_recieveByte();
    
      if(Connected == Internnet_Connected_Successfuly)
      {
        LCD_clearScreen();
        LCD_displayString("     Connected");
        Internet_Connected = 1;
        Delay_MS(2000);
        break;
      }
      else if(Connected == Internnet_Connection_Failed)
      {
        LCD_clearScreen();
        LCD_displayString(" Wrong Password");
        Delay_MS(2000);
      }
    }
  }
}

/*
 * Description :
 * To show the menu in the LCD
 */
void Show_Menu_Options()
{
  LCD_clearScreen();
  LCD_displayStringRowColumn(0,0,"Select from the");
  LCD_displayStringRowColumn(1,0,"following options");
  LCD_displayStringRowColumn(2,0,"A-WiFi");
  LCD_displayStringRowColumn(3,0,"B-Check update");

  uint8 Selected_Option = Keypad_Handler();
  
  while(TRUE)
  {
    if( Selected_Option != 'A' && Selected_Option != 'B' )
    {
      LCD_clearScreen();
      LCD_displayStringRowColumn(0,0,"Select from shown");
      LCD_displayStringRowColumn(1,0,"options");
      LCD_displayStringRowColumn(2,0,"A-WiFi");
      LCD_displayStringRowColumn(3,0,"B-Check update");
      Delay_MS(2000);
      LCD_clearScreen();

      Selected_Option = Keypad_Handler();
    }
    else
    {
      break;
    }
  }
  if(Selected_Option == 'A')
   {
      Request_For_Available_Networks();
   }
   else if(Selected_Option == 'B')
   {
      Check_For_Updates();
   }
}

/*
 * Description :
 * Handling Keypad UI
 */
uint8 Keypad_Handler(void)
{
  /* Return the mode back to default */
  //Keypad_Mode = 'D';
   
  /* Local Variables */
  uint8 Keypad_Button = 0; /* Will take the input from the keypad */
  
  
  while(1)
  {
    /* Print the page number for the keypad */
    LCD_displayCharRowColumn(0,19,Keypad_Mode);
    
    /* Get key from the user */
    Delay_MS(250);
    Keypad_Button = Keypad_getPressedKey(Keypad_Mode,Keypad_CAP);
    Delay_MS(250);
    
      /* Handle the modes */
    if(Keypad_Mode == 'D')
    {
      if(Keypad_Button == '*')
      {
        /* Then we need to change the mode */
        Keypad_Mode = '1';
      }
      else{
        return Keypad_Button;
      } /* End internal IF-ELSE */
    }
    else if(Keypad_Mode == '1')
    {
      if(Keypad_Button == '*')
      {
        /* Then we need to change the mode */
        Keypad_Mode = '2';
      }
      else{
        if(Keypad_Button == '0')
        {
          /* Then we need to change the letters from capital to small or vice verse */
          if(Keypad_CAP == 'C')
          {
            Keypad_CAP='S';
          }
          else
          {
            Keypad_CAP='C';
          }
        }
        else
        {
          return Keypad_Button;
        }
      }/* End internal IF-ELSE */
    }
    else if(Keypad_Mode == '2')
    {
      if(Keypad_Button == '*')
      {
        /* Then we need to change the mode */
        Keypad_Mode = '3';        
      }
      else{
        if(Keypad_Button == '0')
        {
          /* Then we need to change the letters from capital to small or vice verse */
          if(Keypad_CAP == 'C')
          {
            Keypad_CAP='S';
          }
          else
          {
            Keypad_CAP='C';
          }
        }
        else
        {
          return Keypad_Button;
        }
      }/* End internal IF-ELSE */
    }
    else if(Keypad_Mode == '3')
    {
      if(Keypad_Button == '*')
      {
        /* Then we need to change the mode */
        Keypad_Mode = '4';        
      }
      else{
        if(Keypad_Button == '0')
        {
          /* Then we need to change the letters from capital to small or vice verse */
          if(Keypad_CAP == 'C')
          {
            Keypad_CAP='S';
          }
          else
          {
            Keypad_CAP='C';
          }
        }
        else
        {
          return Keypad_Button;
        }
      }/* End internal IF-ELSE */
    }
    else if(Keypad_Mode == '4')
    {
      if(Keypad_Button == '*')
      {
        /* Then we need to change the mode */
        Keypad_Mode = 'D';        
      }
      else{
        if(Keypad_Button == 'A')
        {
          return '*';
        }
        else
        {
        return Keypad_Button;
        }
      }/* End internal IF-ELSE */
    }
    else
    {
      /* Do nothing */
      return Keypad_Button;
    }
  }

}

/* Bootloader Stuff */
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Function is being called after receiving a line
 */
uint8 Received_HEX_Line_Handler(void)
{
  /* If it was the first time  */
  if(BL_Flag==0)
  {
    /* Start the bootloader must be received as interrupt of DMA anything from that kind can't be polling*/
    //UART2_sendByte(START_BOOTLOADER);
      
    
    CAN_Transmitted_Data.Data_To_Be_Sent = START_BOOTLOADER;
    CAN_Transmitte( &CAN_Transmitted_Data );
    LCD_displayStringRowColumn(3,0,"BL Activated");
    
    /* Ask the bootloader to Erase everything and get ready to receive the lines */
    BL_MAX_ERASE();
    /* Disable the flag 3shan mydkholsh l if cond da tany */
    BL_Flag=1;
  }
  
  
    /* At first we need to make sure that it's the start of the line */
  if(Data_Array[0] == ':')
  {
    /* Get the Data size at first */
    /* Checksum at first to make sure that the line is correct */
   if( HEX_CheckSum() == TRUE)
   {
     /* Check if it was DATA or not */
     if(Data_Array[4]==0x00) /*  */
     {
            /* We need to prepare our buffer to be sent */
     return BL_WRITE();
     }
     else if(Data_Array[4]==0x01)
     {
       /* END OF FILE */
       return BL_END_FILE();
     }
     else if(Data_Array[4]==0x02)
     {
       /* USELESS */
           /* Received ACK that the line was correct and waiting for the next line */
     //while(UART_recieveByte() != CONTROL_READY){}
     //UART_sendByte(ACK_BL);
       return TRUE;
     }
     else if(Data_Array[4]==0x04)
     {
       /* Upper Address */
           /* Received ACK that the line was correct and waiting for the next line */
     //while(UART_recieveByte() != CONTROL_READY){}
     //UART_sendByte(ACK_BL);
       return TRUE;
     }
     else if(Data_Array[4]==0x05)
     {
       /* all address */
           /* Received ACK that the line was correct and waiting for the next line */
     //while(UART_recieveByte() != CONTROL_READY){}
     //UART_sendByte(ACK_BL);
       return TRUE;
     }

   }
   else
   {
     /* Send NACK to let the ESP resend the same line again */
     //while(UART_recieveByte() != CONTROL_READY){}
     //UART_sendByte(NACK);
     return FALSE;
   }
  }
  else
  {
     /* Send NACK to let the ESP resend the same line again */
     //while(UART_recieveByte() != CONTROL_READY){}
     //UART_sendByte(NACK);
    return FALSE;
  }

}
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Request from the Bootloader to STOP
 */
uint8 BL_END_FILE(void)
{
    uint8 Received_Flag = NACK;
  /* Clear the buffer at first */
  BL_Buffer_Clear();
  
  /* The requried command of the Erase */
  BL_BUFFER[1] = CBL_BL_STOP_CMD;
  /* Add the Address 0xFF in the last byte */
  BL_BUFFER[2] = 0x00;
  BL_BUFFER[3] = 0x00;
  BL_BUFFER[4] = 0x00;
  BL_BUFFER[5] = 0x00;
  
  /* Get the size of the buffer and save it in the first byte*/
  BL_BUFFER[0] = 0x06;
  
  /* We need to get the Checksum of the new buffer and it should be added in the array*/
  BL_Buffer_CheckSum();
  
 while(1) /* It will leave the function only incase of getting ACK */
  {
  /* The buffer is now ready, we need to send it  */
  BL_Buffer_Send();
 
  /* We should get ACK */
  CAN_Transmitted_Data.Data_To_Be_Sent = MASTER_READY;
  CAN_Transmitte( &CAN_Transmitted_Data ); 
  
  Received_Flag = CAN_Receive_Message(FIRMWARE_Master_FILTER_Bank_Number);
  //UART2_sendByte(MASTER_READY);
  //send_flag = UART2_recieveByte();
  if(Received_Flag==ACK_BL)
  {
    return TRUE;
    break;
  }
  else
  {
    /* repeat the process again */
  }
  
}
}
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Checksum
 */
uint8 HEX_CheckSum(void)
{
  /* Initializing for the for loop */
  uint8 line_bytes = HEX_Constant_Start+Data_Array[1];
  uint8 line_counter = 1;
  
  /* Saving the summation here */
  uint8 Checksum_sum = 0;
  for(line_counter=1;line_counter<=line_bytes;line_counter++)
  {
    Checksum_sum = Checksum_sum + Data_Array[line_counter];
  }
  /* Get the 2's complement of it */
  Checksum_sum = ~Checksum_sum+1;
  
  /* Check on it */
  if(Checksum_sum == Data_Array[line_bytes + 1])
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
  
}
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Generates the checksum for the required buffer
 */
void BL_Buffer_CheckSum(void)
{
 /* We need to add everything inside that array and then get the 2's comp of it */
  uint8 Buffer_Counter = 0;
  uint8 Buffer_Checksum_Sum = 0;
  /* Make a loop to count till the Buffer Size  */
  for(Buffer_Counter=0;(Buffer_Counter<BL_BUFFER[0]);Buffer_Counter++)
  {
    Buffer_Checksum_Sum = Buffer_Checksum_Sum + BL_BUFFER[Buffer_Counter]; 
  }
  /* Get the 2's comp of it */
  Buffer_Checksum_Sum = ~Buffer_Checksum_Sum + 1;
  
  /* Add the checksum in the last byte*/
 BL_BUFFER[BL_BUFFER[0]]=Buffer_Checksum_Sum;
}
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Sends the buffer through the UART
 */
uint8 BL_Buffer_Send(void)
{
  uint8 BUFFER_Counter = 0;
  /* Wait for the target to be ready */
  while(CAN_Receive_Message(FIRMWARE_Master_FILTER_Bank_Number) != TARGET_READY){}
  
  CAN_Transmitted_Data.Data_To_Be_Sent = BL_BUFFER[0];
  CAN_Transmitte( &CAN_Transmitted_Data ); 
  
  //UART2_sendByte(BL_BUFFER[0]);
  /* Wait again */
  while(CAN_Receive_Message(FIRMWARE_Master_FILTER_Bank_Number) != TARGET_READY){}
  //while(UART2_recieveByte() != TARGET_READY){}
  /* Send everything on UART2 */
  for (BUFFER_Counter=1;BUFFER_Counter<=BL_BUFFER[0];BUFFER_Counter++)
  {
    CAN_Transmitted_Data.Data_To_Be_Sent = BL_BUFFER[BUFFER_Counter];
    CAN_Transmitte( &CAN_Transmitted_Data ); 
     //UART2_sendByte(BL_BUFFER[BUFFER_Counter]);
  }
}
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Erase the Buffer
 */
void BL_Buffer_Clear(void)
{
  /* We need to refresh the buffer again and write in all of it null char */
  uint8 Buffer_Counter=0;
  for(Buffer_Counter=0;Buffer_Counter<MAX_Buffer_Size;Buffer_Counter++)
  {
    BL_BUFFER[Buffer_Counter] = '#';
  }
}
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Request from the Bootloader to delete everything
 */
void BL_MAX_ERASE(void)
{
  uint8 Received_Flag = NACK;
  /* Clear the buffer at first */
  BL_Buffer_Clear();
  
  /* The requried command of the Erase */
  BL_BUFFER[1] = CBL_FLASH_ERASE_CMD;
  /* Add the Address 0xFF in the last byte */
  BL_BUFFER[2] = 0x00;
  BL_BUFFER[3] = 0x00;
  BL_BUFFER[4] = 0x00;
  BL_BUFFER[5] = 0xFF;
  /* Number of pages */
  BL_BUFFER[6] = 0x0C;
  
  /* Get the size of the buffer and save it in the first byte*/
  BL_BUFFER[0] = 0x07;
  
  /* We need to get the Checksum of the new buffer and it should be added in the array*/
  BL_Buffer_CheckSum();
  
  while(1) /* It will leave the function only incase of getting ACK */
  {
  /* The buffer is now ready, we need to send it  */
  BL_Buffer_Send();
 
  /* We should get ACK */
  CAN_Transmitted_Data.Data_To_Be_Sent = MASTER_READY;
  CAN_Transmitte( &CAN_Transmitted_Data ); 
  
  Received_Flag = CAN_Receive_Message(FIRMWARE_Master_FILTER_Bank_Number);
  //UART2_sendByte(MASTER_READY);
  //Received_Flag = UART2_recieveByte();
  if(Received_Flag==ACK_BL)
  {
    break;
  }
  else
  {
    /* repeat the process again */
  }
  
}
  
  
}
/*-------------------------------------------------------------------*/
/*
 * Description :
 * Request from the Bootloader to write the array
 */
uint8 BL_WRITE(void)
{
  uint8 vect_low = 0;
  uint16 vect_high = 0;
  uint8 vect_counter_low = 0;
  uint16 vect_counter_high = 0;
  
  uint8 Received_Flag = NACK;
  uint8 Counter = 0;
  /* Clear the buffer at first */
  BL_Buffer_Clear();
  
  /* The requried command TO WRITE in flash */
  BL_BUFFER[1] = CBL_MEM_WRITE_CMD;
  
  /* You need to set the required address */
  BL_BUFFER[2] = 0x08;
  BL_BUFFER[3] = 0x00;
  BL_BUFFER[4] = 0x00 + Data_Array[2];
  BL_BUFFER[5] = 0x00 + Data_Array[3];
  
  /* Send the data size */
  BL_BUFFER[6] = Data_Array[1];
  
  /* Add the data */
  for(Counter = 5;Counter<(5+BL_BUFFER[6]);Counter++)
  {
    BL_BUFFER[Counter+2] = Data_Array[Counter];
  }
  
  /* Get the size of the buffer and save it in the first byte*/
  BL_BUFFER[0] = 0x07+BL_BUFFER[6];
  
  /* We need to get the Checksum of the new buffer and it should be added in the array*/
  BL_Buffer_CheckSum();
  
  while(1) /* It will leave the function only incase of getting ACK */
  {
  /* The buffer is now ready, we need to send it  */
  BL_Buffer_Send();
  
  /* We should get ACK */
  CAN_Transmitted_Data.Data_To_Be_Sent = MASTER_READY;
  CAN_Transmitte( &CAN_Transmitted_Data ); 
  
  Received_Flag = CAN_Receive_Message(FIRMWARE_Master_FILTER_Bank_Number);
  //UART2_sendByte(MASTER_READY);
  //Received_Flag = UART2_recieveByte();
  
  if(Received_Flag == ACK_BL)
  {
    /* Received ACK that the line was correct and waiting for the next line */
    
    // while(UART_recieveByte() != CONTROL_READY){}
    // UART_sendByte(ACK_BL);
    return TRUE;
     /* get out of this loop */
     break;
  }
  else if(Received_Flag == NACK)
  {
    /* Do nothing */
  }
}
}

/*-------------------------------------------------------------------*/