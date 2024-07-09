/*file name: bootloader.h
 * author : seif ayman
 * date ; 29/2/2024
 */


#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_


/* Includes ------------------------------------------------------------------*/
#include "CAN.h"
#include "LCD.h"
#include <string.h>
#include "watchdog.h"
#include <stdarg.h>
#include <stdio.h>
#include "stm32f103c8t6_registers.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_flash.h"
#include "stm32f1xx_hal_flash_ex.h"

#define CBL_GET_VER_CMD     0x10
#define CBL_GET_HELP_CMD    0x11
#define CBL_GET_CID_CMD     0x12
#define CBL_GO_TO_ADDR_CMD  0x14
#define CBL_FLASH_ERASE_CMD 0x15
#define CBL_MEM_WRITE_CMD   0x16
#define CBL_END_ACTION_CMD  0x36
#define NUMBER_OF_SUPPORTED_CMDS 7

#define FLASH_WRITE_BANK_CMD 0x37

#define CHECK_SUM_VERIFING_FAILED 0X00
#define CHECK_SUM_VERIFING_PASSED 0X01

#define SEND_NACK           0xAB
#define SEND_ACK            0xCD
#define HOST_MAX_SIZE       200


#define CBL_VENDOR_ID       100
#define CBL_SW_MAJOR_VERSION 1
#define CBL_SW_MINOR_VERSION 1
#define CBL_SW_PATCH_VERSION 0

#define CBL_FLASH_MAX_PAGE_NUMBER 64
#define CBL_FLASH_MAX_ERASE 0x000000FF

#define INVALID_PAGE_NUMBER 0x00
#define VALID_PAGE_NUMBER   0x01
#define UNSUCCESSFUL_ERASE  0x02
#define SUCCESSFUL_ERASE    0x03

#define HAL_SUCCESSFUL_ERASE 0xFFFFFFFU

#define ADDRESS_IS_INVALID   0x00
#define ADDRESS_IS_VALID     0x01

#define STM32F103_SRAM_SIZE  (20*1024)
#define STM32F103_FLASH_SIZE  (64*1024)
#define STM32F103_SRAM_END    (SRAM_BASE + STM32F103_SRAM_SIZE )
#define STM32F103_FLASH_END    (FLASH_BASE + STM32F103_FLASH_SIZE )

#define FLASH_PAYLOAD_WRITE_FAILED 0x00
#define FLASH_PAYLOAD_WRITE_PASSED 0x01

#define TARGET_READY 0x17
#define MASTER_READY 0x18
#define HOST_BUFFER_END 0X00

#define START_BOOTLOADER        'S'
#define BOOTLOADER_FLAG 0x424C  // 'BL' in ASCII
#define Application_inValid_FLAG 0x5649  // 'IV' in ASCII invalid which means that there is no application found (cleared)

#define BANK1_ADDRESS 0x08003000
#define BANK2_ADDRESS 0x08009400
#define BANK1_ADDRESS_HIGH 0x30
#define BANK2_ADDRESS_HIGH 0x94
#define APP_PAGE_SIZE 24
#define BL_PAGE_SIZE  9
#define FLASH_SAVED_VALUES_PAGES 0x01

#define Startup_Code            0x27
#define FLASH_READ_ADDRESS      0x0800FFF0
#define BL_BANK_USED            7
#define BL_STATE                8
#define BL_APP1_ERASED          9
#define BL_APP2_ERASED          10
#define BL_APP_WRITE            11
#define BL_APP_WRITE_TRUE       1
#define BL_APP_WRITE_FALSE      2
#define BL_BANK1_USED           1
#define BL_BANK2_USED           2
#define BL_STATE_TRUE           1
#define BL_STATE_FALSE          2
#define BL_APP_ERASED_TRUE      1
#define BL_APP_ERASED_FALSE     2
typedef enum{
	BL_NACK=0,
	BL_ACK
}BL_status;

void BL_fetchHostCommand(void);
void BL_SendMessage(const uint8 *format);
/*
* Function to generate the checksum after checking it these function makes sure that that after adding the address and the vector table that everything is correct
*/
void Received_Buffer_Address_Verify();
static void JumpToMainHandler(uint32 Address);
static void CheckBootloaderEN(void);
static void BL_Send_ACK();
static void BL_Send_NACK();
static void BL_Get_Help(uint8 *Host_buffer);
static void BL_Get_Chip_Id_number(uint8 *Host_buffer);
#endif /*INC_BOOTLOADER_H_ */
