/*file name: bootloader.c
* author : seif ayman
* date ; 29/2/2024
*/
#include "bootloader.h"

/**--------------------------------------------------------------------------**/
/* Normal Functions */
uint8  BL_CHECK_SUM_verify(uint8 *Host_buffer,uint8 Host_check_sum);
uint32 bootloader_reset_handler= 0;
uint8 MyBank_Flash_Array[24] = {0x17,FLASH_WRITE_BANK_CMD,0x08,0x00,0xFF,0xF0,0x10,BL_BANK1_USED,BL_STATE_FALSE,BL_APP_ERASED_FALSE,BL_APP_ERASED_TRUE,BL_APP_WRITE_FALSE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01};/* Fixing the vector table flag */
uint8 MyBank_Backup_Flash_Array[24] = {0x17,FLASH_WRITE_BANK_CMD,0x08,0x00,0xFF,0xF0,0x10,BL_BANK1_USED,BL_STATE_FALSE,BL_APP_ERASED_FALSE,BL_APP_ERASED_TRUE,BL_APP_WRITE_FALSE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01};/* Fixing the vector table flag */
uint8 Flash_Read_Verify[24] = {0x17,FLASH_WRITE_BANK_CMD,0x08,0x00,0x94,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01};/* Fixing the vector table flag */
/* Static Functions */
void Received_Buffer_Address_Verify();
static void JumpToMainHandler(uint32 Address);
static void BL_Send_ACK();
static void BL_Send_NACK();
static void BL_Get_Version(uint8 *Host_buffer);
static void CheckBootloaderEN(void);
static void BL_Write_Data(uint8 *Host_buffer);
static uint8 BL_Address_verification (uint32 Address);
static uint8 FlashMemory_Payload_Write(uint16 * pdata,uint32 StartAddress,uint8 Payload_length);
static void BL_Get_Help(uint8 *Host_buffer);
static void BL_Get_Chip_Id_number(uint8 *Host_buffer);
static void BL_Flash_Erase(uint8 *Host_buffer);
static uint8 Perform_flash_erase(uint32 PageAddress,uint8 Page_Number);
static uint8 Host_buffer[HOST_MAX_SIZE];


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
/*--------------------------------Bootloader-----------------------------------*/
/*
* Description :
* Check if we should start the bootloader or skip to the application main
*/
void CheckBootloaderEN(void)
{
  // Enable the power and backup interface clocks
  RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;
  // Enable access to the backup domain
  PWR->CR |= PWR_CR_DBP;
  

  
  for (int i = 0; i < 16; i++)
  {
    MyBank_Flash_Array[7+i] = *(uint32_t*)(FLASH_READ_ADDRESS + i);
  }
  if(MyBank_Flash_Array[7] == 0xFF || MyBank_Flash_Array[8] == 0xFF || MyBank_Flash_Array[9] == 0xFF || MyBank_Flash_Array[10] == 0xFF || MyBank_Flash_Array[11] == 0xFF)
  {
    /* Save this values in the memory */
    Perform_flash_erase(FLASH_READ_ADDRESS,0x01);
    BL_Write_Data(MyBank_Backup_Flash_Array);
    
    for (int i = 0; i < 16; i++)
    {
      MyBank_Flash_Array[7+i] = *(uint32_t*)(FLASH_READ_ADDRESS + i);
    }
  }
  if(BKP_DR2 != 0x00)
  {
    if(BKP_DR2 == BOOTLOADER_FLAG)
    {
      MyBank_Flash_Array[BL_STATE] = BL_STATE_TRUE;
    }
    else
    {
      MyBank_Flash_Array[BL_STATE] = BL_STATE_FALSE;
    }
  }
  else if(BKP_DR2 == 0x00 )
  {
    if(MyBank_Flash_Array[BL_STATE] == BL_STATE_TRUE)
    {
      /* Do nothing */
    }
    else
    {
      /* Do nothing */
    }
  }
  /* Save this values in the memory */
  Perform_flash_erase(FLASH_READ_ADDRESS,0x01);
  BL_Write_Data(MyBank_Flash_Array);
  
  /**----------------------------------------------------------------------x**/
  // Check the bootloader flag
  if ( MyBank_Flash_Array[BL_STATE] == BL_STATE_TRUE) 
  {
    if(MyBank_Flash_Array[BL_APP1_ERASED] == BL_APP_ERASED_TRUE && MyBank_Flash_Array[BL_APP2_ERASED] == BL_APP_ERASED_TRUE)
    {
      while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
      return;
    }
    else if(MyBank_Flash_Array[BL_APP_WRITE] == BL_APP_WRITE_TRUE)
    {
      if(MyBank_Flash_Array[BL_APP1_ERASED] == BL_APP_ERASED_TRUE && MyBank_Flash_Array[BL_APP2_ERASED] == BL_APP_ERASED_TRUE)
      {
        while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
        return;
      }
      else
      {
        if(MyBank_Flash_Array[BL_BANK_USED] == BL_BANK1_USED && MyBank_Flash_Array[BL_APP1_ERASED] == BL_APP_ERASED_FALSE)
        {
          /* We need to check another condition */
          for (int i = 0; i < 16; i++)
          {
            Flash_Read_Verify[7+i] = *(uint32_t*)(BANK1_ADDRESS + i);
          }
          
          /* Corner Case */
          if(Flash_Read_Verify[7] == 0xFF || Flash_Read_Verify[8] == 0xFF || Flash_Read_Verify[9] == 0xFF || Flash_Read_Verify[10] == 0xFF || Flash_Read_Verify[11] == 0xFF)
          {
            if(MyBank_Flash_Array[BL_APP2_ERASED] == BL_APP_ERASED_FALSE)
            {
              /* We are checking that incase the address was wrong of the new firmware not starting at 0x0800 0000 then incase the old firmware still found then jump to it */
              MyBank_Flash_Array[BL_APP1_ERASED] = BL_APP_ERASED_TRUE;
              JumpToMainHandler(BANK2_ADDRESS);
            }
            else
            {
              while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
              return;
            }
          }
          // If the flag is not set, jump to the application bank 1
          JumpToMainHandler(BANK1_ADDRESS);
        }
        else if(MyBank_Flash_Array[BL_BANK_USED] == BL_BANK2_USED && MyBank_Flash_Array[BL_APP2_ERASED] == BL_APP_ERASED_FALSE){
          /* We need to check another condition */
          for (int i = 0; i < 16; i++)
          {
            Flash_Read_Verify[7+i] = *(uint32_t*)(BANK2_ADDRESS + i);
          }
          
          /* Corner Case */
          if(Flash_Read_Verify[7] == 0xFF || Flash_Read_Verify[8] == 0xFF || Flash_Read_Verify[9] == 0xFF || Flash_Read_Verify[10] == 0xFF || Flash_Read_Verify[11] == 0xFF)
          {
            if(MyBank_Flash_Array[BL_APP1_ERASED] == BL_APP_ERASED_FALSE)
            {
              /* We are checking that incase the address was wrong of the new firmware not starting at 0x0800 0000 then incase the old firmware still found then jump to it */
              MyBank_Flash_Array[BL_APP2_ERASED] = BL_APP_ERASED_TRUE;
              JumpToMainHandler(BANK1_ADDRESS);
            }
            else
            {
              while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
              return;
            }
          }
          // If the flag is not set, jump to the application bank 2
          JumpToMainHandler(BANK2_ADDRESS);        
        }
        else
        {
          /* This case shouldn't be reached but just added incase */
          while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
          return;
        }
      }
    }
    else
    {
      return;
    }
  }
  else if(MyBank_Flash_Array[BL_APP1_ERASED] == BL_APP_ERASED_TRUE && MyBank_Flash_Array[BL_APP2_ERASED] == BL_APP_ERASED_TRUE){
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    return;
  }
  else
  {
    if(MyBank_Flash_Array[BL_BANK_USED] == BL_BANK1_USED && MyBank_Flash_Array[BL_APP1_ERASED] == BL_APP_ERASED_FALSE){
      /* We need to check another condition */
      for (int i = 0; i < 16; i++)
      {
        Flash_Read_Verify[7+i] = *(uint32_t*)(BANK1_ADDRESS + i);
      }
      
      /* Corner Case */
      if(Flash_Read_Verify[7] == 0xFF || Flash_Read_Verify[8] == 0xFF || Flash_Read_Verify[9] == 0xFF || Flash_Read_Verify[10] == 0xFF || Flash_Read_Verify[11] == 0xFF)
      {
        if(MyBank_Flash_Array[BL_APP2_ERASED] == BL_APP_ERASED_FALSE)
        {
          /* We are checking that incase the address was wrong of the new firmware not starting at 0x0800 0000 then incase the old firmware still found then jump to it */
          MyBank_Flash_Array[BL_APP1_ERASED] = BL_APP_ERASED_TRUE;
          JumpToMainHandler(BANK2_ADDRESS);
        }
        else
        {
          while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
          return;
        }
      }
      // If the flag is not set, jump to the application bank 1
      JumpToMainHandler(BANK1_ADDRESS);
    }
    else if(MyBank_Flash_Array[BL_BANK_USED] == BL_BANK2_USED && MyBank_Flash_Array[BL_APP2_ERASED] == BL_APP_ERASED_FALSE){
      /* We need to check another condition */
      for (int i = 0; i < 16; i++)
      {
        Flash_Read_Verify[7+i] = *(uint32_t*)(BANK2_ADDRESS + i);
      }
      
      /* Corner Case */
      if(Flash_Read_Verify[7] == 0xFF || Flash_Read_Verify[8] == 0xFF || Flash_Read_Verify[9] == 0xFF || Flash_Read_Verify[10] == 0xFF || Flash_Read_Verify[11] == 0xFF)
      {
        if(MyBank_Flash_Array[BL_APP1_ERASED] == BL_APP_ERASED_FALSE)
        {
          /* We are checking that incase the address was wrong of the new firmware not starting at 0x0800 0000 then incase the old firmware still found then jump to it */
          MyBank_Flash_Array[BL_APP2_ERASED] = BL_APP_ERASED_TRUE;
          JumpToMainHandler(BANK1_ADDRESS);
        }
        else
        {
          while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
          return;
        }
      }
      // If the flag is not set, jump to the application bank 2
      JumpToMainHandler(BANK2_ADDRESS);        
    }
    else
    {
      /* This case shouldn't be reached but just added incase */
      while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != START_BOOTLOADER) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
      return;
    }
    
  }
}
/*-----------------------------------------------------------------*/
/*
* Description :
* Calls back the application main
*/

void JumpToMainHandler(uint32 Address)
{
  /*  After receive anyline this means that the bootloader had received something so no need to use it anymore*/
  IWDG_Stop();
  
  /* Modify the bank in the flash */
  if(Address == BANK1_ADDRESS){
    MyBank_Flash_Array[BL_BANK_USED] = BL_BANK1_USED;
    MyBank_Flash_Array[BL_APP1_ERASED] = BL_APP_ERASED_FALSE;
  }else if(Address == BANK2_ADDRESS){
    MyBank_Flash_Array[BL_BANK_USED] = BL_BANK2_USED;
    MyBank_Flash_Array[BL_APP2_ERASED] = BL_APP_ERASED_FALSE;
  }
  /* return back the BL state and ERASED */
  MyBank_Flash_Array[BL_STATE] = BL_STATE_FALSE;
  
  /* return the default value for the write register */
  MyBank_Flash_Array[BL_APP_WRITE] = BL_APP_WRITE_FALSE;  
  
  /* Erase the location 0x0800 FFF0 and the rewrite again in it */
  Perform_flash_erase(FLASH_READ_ADDRESS,0x01);
  BL_Write_Data(MyBank_Flash_Array);
  
  // Disable all interrupts
  __disable_irq();
  
  // Set the vector table location to the bootloader address
  SCB_VTOR = Address;
  
  // Load the stack pointer address from the bootloader's vector table
  __set_MSP(*((volatile uint32*)Address));
  
  // Get the reset handler address from the bootloader's vector table
  bootloader_reset_handler = *((volatile uint32*) (Address + 4));
  
  /* Clear the backup register */
  BKP_DR2 = 0x0000;
  
  // Jump to the bootloader's reset handler
  ((void (*)(void))bootloader_reset_handler)();
  
  // If we ever return, disable all interrupts and enter an infinite loop
  __disable_irq();
  while (1);
}

/*-----------------------------------------------------------------------------*/
void BL_SendMessage(const uint8 *format)
{
  
}

/* Check on the received address if it's correct or not based on the bank currently in-use */
void Received_Buffer_Address_Verify()
{
  /* We need to check at first the required address needed  */
  if(MyBank_Flash_Array[BL_BANK_USED]==BL_BANK1_USED)
  {
    if(Host_buffer[2] == 0x08 && Host_buffer[3] == 0x00 && Host_buffer[4] >= 0x94 && Host_buffer[4] <= 0xF4)
    {
      return;
    }
    else
    {
      /* The Address is incorrect  */
      LCD_clearScreen();
      LCD_displayString("B1 USED, B.E. !");
      /* Reset the MCU maybe it's stucked */
      IWDG_Init();
      while (1);
    }
  }
  else if(MyBank_Flash_Array[BL_BANK_USED]==BL_BANK2_USED)
  {
    if(Host_buffer[2] == 0x08 && Host_buffer[3] == 0x00 && Host_buffer[4] >= 0x30 && Host_buffer[4] <= 0x90)
    {
      return;
    }
    else
    {
      /* The Address is incorrect  */
      LCD_clearScreen();
      LCD_displayString("B2 USED, B.E. !");
      /* Reset the MCU maybe it's stucked */
      IWDG_Init();
      while (1);
    }
  }
  else
  {
    /* There is something wrong with the bootloader as the used bank is not one of the banks it has */
    LCD_clearScreen();
    LCD_displayString("BL Fault Error!");
    LCD_displayStringRowColumn(1,0,"MCU Reset 5s");
    /* Reset the MCU maybe it's stucked */
    IWDG_Init();
    while (1);
  }
}
/*-----------------------------------------------------------------------------*/

void BL_fetchHostCommand(void)
{
  CheckBootloaderEN();
  
  /* If you returned back this means that you will start writing a new firmware */
  /* You must say that u started writing a new firmware */
  MyBank_Flash_Array[BL_APP_WRITE] = BL_APP_WRITE_TRUE;
  /* Document what you have erased in the flash memory */
  Perform_flash_erase(FLASH_READ_ADDRESS,0x01);
  BL_Write_Data(MyBank_Flash_Array);
  
  /* Init the Host buffer that we will received the required line in it */
  memset(Host_buffer,0,HOST_MAX_SIZE);
  uint8 i=0;
  
  while(1)
  { 
    /* Start the watchdog timer incase the fota master had a problem */ 
    IWDG_Init(); 
    /* To sync with master */
    CAN_Transmitted_Data.Data_To_Be_Sent = TARGET_READY;
    CAN_Transmitte( &CAN_Transmitted_Data );
    
    // send the first byte in the array as it contains the whole buffer length
    Host_buffer[0]= (uint8)CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number); 
    
    /* Send another ACK to start receiving the remained line */
    CAN_Transmitted_Data.Data_To_Be_Sent = TARGET_READY;
    CAN_Transmitte( &CAN_Transmitted_Data );
    
    /* Start receving the rest of the line */
    for( i=1;i<=Host_buffer[0];i++)
    { 
      Host_buffer[i]=(uint8)CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number);
    }
    /*  After receive anyline this means that the bootloader had received something so no need to use it anymore*/
    IWDG_Stop();
    
    /* Based on the CMD we received we need to do it USED: ERASE/WRITE/END */
    switch(Host_buffer[1])
    {
    case CBL_GET_VER_CMD :
      BL_Get_Version(Host_buffer);
      break;
    case CBL_GET_HELP_CMD:
      BL_Get_Help(Host_buffer);
      break;
    case CBL_GET_CID_CMD:
      BL_Get_Chip_Id_number(Host_buffer);
      break;
    case CBL_GO_TO_ADDR_CMD:
      BL_SendMessage("jump to the given address");
      break;
    case CBL_FLASH_ERASE_CMD:
      /* Check which bank should be deleted */
      if(MyBank_Flash_Array[BL_BANK_USED] ==BL_BANK1_USED){
        MyBank_Flash_Array[BL_APP2_ERASED] = BL_APP_ERASED_TRUE;
      }
      else {
        MyBank_Flash_Array[BL_APP1_ERASED] = BL_APP_ERASED_TRUE;
      }
      /* Erase the required location */
      BL_Flash_Erase(Host_buffer);
      /* Document what you have erased in the flash memory */
      Perform_flash_erase(FLASH_READ_ADDRESS,0x01);
      BL_Write_Data(MyBank_Flash_Array);
      break;
    case CBL_MEM_WRITE_CMD:
      /* Check if the received address is correct based on the Bank currently in-use */
      Received_Buffer_Address_Verify();
      /* Start writing on the received location */
      BL_Write_Data(Host_buffer);
      break;
    case CBL_END_ACTION_CMD:
      /* Send ack */
      while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
      BL_Send_ACK();
      /* Jump to the new location */
      if(MyBank_Flash_Array[BL_BANK_USED] == BL_BANK1_USED ){
        /* If bank 1 was the last thing used then the new firmware that we have just written, located at address of BANK2 */
        LCD_clearScreen();
        LCD_displayString("B2 Ready!");
        Delay_MS(250);
        JumpToMainHandler(BANK2_ADDRESS);
      }else if(MyBank_Flash_Array[BL_BANK_USED] == BL_BANK2_USED){
        /* If bank 2 was the last thing used then the new firmware that we have just written, located at address of BANK1 */
        LCD_clearScreen();
        LCD_displayString("B1 Ready!");
        Delay_MS(250);
        JumpToMainHandler(BANK1_ADDRESS);        
      }
      break;
    default:
      BL_fetchHostCommand(); //Fetch again
      break;
    }
    
  }
}

static void BL_Get_Help(uint8 *Host_buffer)
{
  uint8 BL_Supported_cmds[NUMBER_OF_SUPPORTED_CMDS]={CBL_GET_VER_CMD,CBL_GET_HELP_CMD,CBL_GET_CID_CMD,CBL_GO_TO_ADDR_CMD,CBL_FLASH_ERASE_CMD,CBL_MEM_WRITE_CMD,CBL_END_ACTION_CMD};
  uint16 Host_Packet_len=0;
  uint8 Host_check_sum_value=0;
  Host_Packet_len=Host_buffer[0]+1;
  Host_check_sum_value= *(uint8*)(Host_buffer+Host_Packet_len );
  if(CHECK_SUM_VERIFING_PASSED== BL_CHECK_SUM_verify(Host_buffer, Host_check_sum_value))
  {
    
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_ACK();
    for (uint8 i=0;i<NUMBER_OF_SUPPORTED_CMDS;i++)
    {
      CAN_Transmitted_Data.Data_To_Be_Sent = BL_Supported_cmds[i];
      CAN_Transmitte( &CAN_Transmitted_Data );
    }
    
    
  }
  else
  {
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_NACK();
  }
  
  
}

uint8  BL_CHECK_SUM_verify(uint8 *Host_buffer,uint8 Host_check_sum)
{
  
  uint8 check_sum_status=CHECK_SUM_VERIFING_FAILED;
  
  /* We need to add everything inside that array and then get the 2's comp of it */
  uint8 Buffer_Counter = 0;
  uint8 BL_Check_sum = 0;
  /* Make a loop to count till the Buffer Size  */
  for(Buffer_Counter=0;Buffer_Counter<(Host_buffer[0]);Buffer_Counter++)
  {
    BL_Check_sum = BL_Check_sum + Host_buffer[Buffer_Counter]; 
  }
  /* Get the 2's comp of it */
  BL_Check_sum = ~BL_Check_sum + 1;
  
  if(Host_check_sum==BL_Check_sum)
  {
    check_sum_status=CHECK_SUM_VERIFING_PASSED;
    
  }
  else
  {
    check_sum_status=CHECK_SUM_VERIFING_FAILED;
    
  }
  
  return check_sum_status;
  
}

/*
* Function to generate the checksum after checking it these function makes sure that that after adding the address and the vector table that everything is correct
*/
void BL_Buffer_CheckSum(uint8 *BL_BUFFER)
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
/*---------------------------------------------------------------------------------*/
static void BL_Send_ACK()
{
  CAN_Transmitted_Data.Data_To_Be_Sent = SEND_ACK;
  CAN_Transmitte( &CAN_Transmitted_Data );
  
}
static void BL_Send_NACK()
{
  CAN_Transmitted_Data.Data_To_Be_Sent = SEND_NACK;
  CAN_Transmitte( &CAN_Transmitted_Data );
  
}
static void BL_Get_Version(uint8 *Host_buffer)
{
  uint8 Version[4]={CBL_VENDOR_ID,CBL_SW_MAJOR_VERSION,CBL_SW_MINOR_VERSION,CBL_SW_PATCH_VERSION};
  uint16 Host_Packet_len=0;
  uint8 Host_check_sum_value=0;
  Host_Packet_len=Host_buffer[0]+1;
  Host_check_sum_value= *(uint8*)(Host_buffer+Host_Packet_len );
  if(CHECK_SUM_VERIFING_PASSED== BL_CHECK_SUM_verify(Host_buffer, Host_check_sum_value))
  {
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_ACK();
    for (uint8 i=0;i<4;i++)
    {
      CAN_Transmitted_Data.Data_To_Be_Sent = Version[i];
      CAN_Transmitte( &CAN_Transmitted_Data );
    }
    
    
  }
  else
  {
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_NACK();
  }
}
static void BL_Get_Chip_Id_number(uint8 *Host_buffer)
{
  uint16 Chip_Id = 0;
  uint16 Host_Packet_len=0;
  uint8 Host_check_sum_value=0;
  Host_Packet_len=Host_buffer[0]+1;
  Host_check_sum_value= *(uint8*)(Host_buffer+Host_Packet_len );
  if(CHECK_SUM_VERIFING_PASSED== BL_CHECK_SUM_verify(Host_buffer, Host_check_sum_value))
  {
    Chip_Id=(uint16)(DBGMCU->IDCODE & 0x00000FFF);
    
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_ACK();
    for (uint8 i=0;i<2;i++)
    {
      CAN_Transmitted_Data.Data_To_Be_Sent = Chip_Id;
      CAN_Transmitte( &CAN_Transmitted_Data );
      
    }
    
    
  }
  else
  {
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_NACK();
  }
  
  
}

static void BL_Flash_Erase(uint8 *Host_buffer)
{
  uint8 Erase_status=UNSUCCESSFUL_ERASE;
  uint32 Address_Host = 0;
  if(CHECK_SUM_VERIFING_PASSED== BL_CHECK_SUM_verify(Host_buffer, Host_buffer[Host_buffer[0]]))
  {
    
    Address_Host = (Host_buffer[2] << 24) |
      (Host_buffer[3] << 16) |
        (Host_buffer[4] << 8)  |
          (Host_buffer[5]);
    
    Erase_status =Perform_flash_erase(Address_Host,Host_buffer[6]);
    
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_ACK();
    
  }
  else
  {
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_NACK();
  }
  
  
  
}
static uint8 Perform_flash_erase(uint32 PageAddress,uint8 Page_Number)
{
  FLASH_EraseInitTypeDef pEraseInit;
  uint32 Page_error=0;
  HAL_StatusTypeDef Hal_status= HAL_ERROR;
  uint8 Page_Status=INVALID_PAGE_NUMBER;
  if(Page_Number>CBL_FLASH_MAX_PAGE_NUMBER)
  {
    Page_Status=INVALID_PAGE_NUMBER;
  }
  else
  {
    Page_Status=VALID_PAGE_NUMBER;
    if(Page_Number<=(CBL_FLASH_MAX_PAGE_NUMBER-1)||PageAddress==CBL_FLASH_MAX_ERASE)
    {
      if(PageAddress==CBL_FLASH_MAX_ERASE)
      {
        pEraseInit.TypeErase=FLASH_TYPEERASE_PAGES;
        pEraseInit.Banks=FLASH_BANK_1;
        pEraseInit.PageAddress=(MyBank_Flash_Array[BL_BANK_USED] == BL_BANK1_USED)?BANK2_ADDRESS:BANK1_ADDRESS; /* lw bank 1 used f kda hnktb f bank2 and vice versa*/
        pEraseInit.NbPages=APP_PAGE_SIZE;
      }
      else
      {
        pEraseInit.TypeErase=FLASH_TYPEERASE_PAGES;
        pEraseInit.Banks=FLASH_BANK_1;
        pEraseInit.PageAddress=PageAddress;
        pEraseInit.NbPages=Page_Number;
      }
      HAL_FLASH_Unlock();
      Hal_status =HAL_FLASHEx_Erase(&pEraseInit,&Page_error);
      HAL_FLASH_Lock();
      if(Page_error==HAL_SUCCESSFUL_ERASE)
      {
        Page_Status=SUCCESSFUL_ERASE;
      }
      else
      {
        Page_Status=UNSUCCESSFUL_ERASE;
      }
    }
    else
    {
      Page_Status=INVALID_PAGE_NUMBER;
    }
  }
  return Page_Status;
  
  
}
static void BL_Write_Data(uint8 *Host_buffer)
{
  uint8 Address_verify =ADDRESS_IS_VALID;
  uint32 Address_Host=0;
  uint8 Payload_status=FLASH_PAYLOAD_WRITE_FAILED;
  
  if(CHECK_SUM_VERIFING_PASSED== BL_CHECK_SUM_verify(Host_buffer, Host_buffer[Host_buffer[0]]))
  {
    
    // Extract the bytes and combine them into a 32-bit variable
    Address_Host = (Host_buffer[2] << 24) |
      (Host_buffer[3] << 16) |
        (Host_buffer[4] << 8)  |
          (Host_buffer[5]);
    Address_verify =BL_Address_verification(Address_Host);
    if(Address_verify == ADDRESS_IS_VALID)
    {
      Payload_status=FlashMemory_Payload_Write( (uint16*)&Host_buffer[7],Address_Host,Host_buffer[6]);
      if(Payload_status==FLASH_PAYLOAD_WRITE_PASSED)
      {
        
        while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
        BL_Send_ACK();
      }
      else 
      {
        while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
        BL_Send_NACK();
      }
    }
    else
    {
      while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
      BL_Send_NACK();  //send nack as the address is invalid
      //send that the address is invalid
    }
    
    
  }else if(Host_buffer[1] == FLASH_WRITE_BANK_CMD){
    // Extract the bytes and combine them into a 32-bit variable
    Address_Host = (Host_buffer[2] << 24) |
      (Host_buffer[3] << 16) |
        (Host_buffer[4] << 8)  |
          (Host_buffer[5]);
    Payload_status=FlashMemory_Payload_Write( (uint16*)&Host_buffer[7],Address_Host,Host_buffer[6]);
    return;
  }else
  {
    while(CAN_Receive_Message(FIRMWARE_Target_FILTER_Bank_Number) != MASTER_READY) { /*WASTE TIME TILL FOTA MASTER IS READY*/}
    BL_Send_NACK();
  }
}
static uint8 BL_Address_verification (uint32 Address)
{
  uint8 Address_verify =ADDRESS_IS_INVALID;
  if(Address>=FLASH_BASE && Address<=STM32F103_FLASH_END)
  {
    Address_verify =ADDRESS_IS_VALID;
  }
  else if (Address>=SRAM_BASE && Address<=STM32F103_SRAM_END)
  {
    Address_verify =ADDRESS_IS_VALID;
  }
  else
  {
    Address_verify =ADDRESS_IS_INVALID;
  }
  return Address_verify;
  
}
static uint8 FlashMemory_Payload_Write(uint16 * pdata,uint32 StartAddress,uint8 Payload_length)
{
  uint32 Address =0;//4BYTES
  uint8 Update_Address =0;//1 BYTE
  HAL_StatusTypeDef Hal_status= HAL_ERROR;
  uint8 Payload_status=FLASH_PAYLOAD_WRITE_FAILED;
  HAL_FLASH_Unlock();
  for(uint8 payload_count=0,Update_Address=0;payload_count<Payload_length/2;payload_count++,Update_Address+=2)
  {
    Address=StartAddress+ Update_Address;
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,Address,pdata[payload_count]); //writing in half word (2bytes) and increment the address by two in each half word write
    if(Hal_status != HAL_OK)
    {
      Payload_status=FLASH_PAYLOAD_WRITE_PASSED ; /* ############ Modified, swapped with other one */
    }
    else
    {
      Payload_status=FLASH_PAYLOAD_WRITE_FAILED;
    }
  }
  HAL_FLASH_Lock();
  return Payload_status;
}
