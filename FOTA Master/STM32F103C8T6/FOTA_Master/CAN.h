/*************************************************************************************************
 *
 * Module: Controller Area Network
 *
 * File Name: CAN.h
 *
 * Description: Header for STM32F103C8T6 Microcontroller - CAN Driver.
 *
 * Author: Shady Alaa
 ***************************************************************************************************/
#ifndef CAN_HEADER_FILE
#define CAN_HEADER_FILE

#include "CAN_Regs.h"
#include "Common_Macros.h"
#include "stm32f103c8t6_registers.h"
#include "Std_Types.h"
/*****************************Filter numbers definition**********************************************/
#define  FILTER_Bank_0               0
#define  FILTER_Bank_1               1
#define  FILTER_Bank_2               2
#define  FILTER_Bank_3               3
#define  FILTER_Bank_4               4
#define  FILTER_Bank_5               5
#define  FILTER_Bank_6               6
#define  FILTER_Bank_7               7
#define  FILTER_Bank_8               8
#define  FILTER_Bank_9               9
#define  FILTER_Bank_10              10
#define  FILTER_Bank_11              11
#define  FILTER_Bank_12              12
#define  FILTER_Bank_13              13

#define  Configured_FILTERS_NUMBER              2
#define  FILTERS_NUMBER                         14

/*****************************ID list specific for each filter******************************************/
#define  FILTER_0_ID           (uint16)(0x0000)
#define  FILTER_1_ID           (uint16)(0x0002)
#define  FILTER_2_ID           (uint16)(0x0003)
#define  FILTER_3_ID           (uint16)(0x0004)
#define  FILTER_4_ID           (uint16)(0x0005)
#define  FILTER_5_ID           (uint16)(0x0006)
#define  FILTER_6_ID           (uint16)(0x0007)
#define  FILTER_7_ID           (uint16)(0x0008)
#define  FILTER_8_ID           (uint16)(0x0009)
#define  FILTER_9_ID           (uint16)(0x000A)
#define  FILTER_10_ID          (uint16)(0x000B)
#define  FILTER_11_ID          (uint16)(0x000C)
#define  FILTER_12_ID          (uint16)(0x000D)
#define  FILTER_13_ID          (uint16)(0x000E)

/* This should be the value of the bank number that sould be checked in the handler or the CAN receive message function */
#define FIRMWARE_Target_FILTER_Bank_Number         0x0
#define FIRMWARE_Master_FILTER_Bank_Number         0x1

/* Those should be STID that will be sent with the message frame */
#define FIRMWARE_Target_FILTER_ID                  0x0
#define FIRMWARE_Master_FILTER_ID                  0x2

/*********************************************************************************
*                   CAN general Configurations Enumerations
**********************************************************************************/
/*
  Description:
    Priority_BY_ID (0):  Priority driven by the identifier of the message.
    Priority_BY_ORDER (1): Priority driven by the request order (FIFOs)  
 */
typedef enum{
  Priority_BY_ID, Priority_BY_ORDER
}t_MAilboxes_Priority;

/*
  Description:
    Not_LOCKED (0): Once a receive FIFO is full the next incoming message will overwrite the previous one.
    LOCKED (1): Once a receive FIFO is full the next incoming message will be discarded.  
 */
typedef enum{
Not_LOCKED, LOCKED
}t_Received_FIFO_Lock_Mode;

/*
  Description:
    Enable_Retransmission (0): The CAN hardware will automatically retransmit the message untill successfuly transmission.
    DISABLE_Retransmission (1): A message will be transmitted only once, independently of the transmission result. 
 */
typedef enum{
  Enable_Retransmission, DISABLE_Retransmission
}t_Auto_Retransmission;

/*
  Description:
    MANUAL_Wakeup (0):  The Sleep mode is left on software request.
    AUTO_Wakeup (1):  The Sleep mode is left automatically by hardware on CAN message detection. (Recommended)
 */
typedef enum{
  MANUAL_Wakeup, AUTO_Wakeup
}t_Automatic_wakeup_mode;

/*
  Description:
    when the node counters many errors it automatically enters a bus off state,
    so it can't either transmitte or receive any messages so to return back on the bus we must select either:
      1-MANUAL_Bus_Off_Left (0): The Bus-Off state is left on software request.
      2-AUTO_Bus_Off_Left(1) : The Bus-Off state is left automatically by hardware. (Recommended)
 */
typedef enum{
  MANUAL_Bus_Off_Left, AUTO_Bus_Off_Left
}t_Automatic_Bus_Off_Management;

/*
  Description:
    Debug_freeze_DISABLE (0): The CAN controller continues to operate normally even when the microcontroller is halted.
    Debug_freeze_ENABLE (1): The CAN controller's transmission and reception activities are paused 
                              when the microcontroller is halted during debugging.
  */
typedef enum{
  Debug_freeze_DISABLE, Debug_freeze_ENABLE
}t_Debug_freeze_Mode;

/*
  Description:
    Can be used for any mode to weather enable or disable it.
 */
typedef enum{
  DISABLE,ENABLE
}t_Mode;

/*********************************************************************************
*                       CAN general Interrupts Enumerations
**********************************************************************************/
/*
  Description:
    Enum to hold if: SLAK Interrupt is activated or not 
*/
typedef enum {
    SLAKI_DISABLE,
    SLAKI_ENABLE
} t_Sleep_Ack_Interrupt;

/*
  Description:
    Enum to hold if: WKUI Interrupt is activated or not 
*/
typedef enum {
    WKUIE_DISABLE,
    WKUIE_ENABLE
} t_Wakeup_Interrupt;

/*
  Description:
    Enum to hold if: Error Interrupt is activated or not 
*/
typedef enum {
    ERRIE_DISABLE,
    ERRIE_ENABLE
} t_Error_Interrupt;

/*
  Description:
    Enum to hold if: Last Error Code Interrupt is activated or not 
*/
typedef enum {
    LECIE_DISABLE,
    LECIE_ENABLE
} t_Last_Error_Code_Interrupt;

/*
  Description:
    Enum to hold if: Bus-Off Interrupt is activated or not 
*/
typedef enum {
    BOFIE_DISABLE,
    BOFIE_ENABLE
} t_Bus_Off_Interrupt;

/*
  Description:
    Enum to hold if: Error Passive Interrupt is activated or not 
*/
typedef enum {
    EPVIE_DISABLE,
    EPVIE_ENABLE
} t_Error_Passive_Interrupt;

/*
  Description:
    Enum to hold if: Error Warning Interrupt is activated or not 
*/
typedef enum {
    EWGIE_DISABLE,
    EWGIE_ENABLE
} t_Error_Warning_Interrupt;

/*
  Description:
    Enum to hold if: FIFO Overrun Interrupt (FIFO1) is activated or not 
*/
typedef enum {
    FOVIE1_DISABLE,
    FOVIE1_ENABLE
} t_FIFO_Overrun_Interrupt1;

/*
  Description:
    Enum to hold if: FIFO Full Interrupt (FIFO1) is activated or not 
*/
typedef enum {
    FFIE1_DISABLE,
    FFIE1_ENABLE
} t_FIFO_Full_Interrupt1;

/*
  Description:
    Enum to hold if: FIFO Message Pending Interrupt (FIFO1) is activated or not 
*/
typedef enum {
    FMPIE1_DISABLE,
    FMPIE1_ENABLE
} t_FIFO_Message_Pending_Interrupt1;

/*
  Description:
    Enum to hold if: FIFO Overrun Interrupt (FIFO0) is activated or not 
*/
typedef enum {
    FOVIE0_DISABLE,
    FOVIE0_ENABLE
} t_FIFO_Overrun_Interrupt0;

/*
  Description:
    Enum to hold if: FIFO Full Interrupt (FIFO0) is activated or not 
*/
typedef enum {
    FFIE0_DISABLE,
    FFIE0_ENABLE
} t_FIFO_Full_Interrupt0;

/*
  Description:
    Enum to hold if: FIFO Message Pending Interrupt (FIFO0) is activated or not 
*/
typedef enum {
    FMPIE0_DISABLE,
    FMPIE0_ENABLE
} t_FIFO_Message_Pending_Interrupt0;

/*
  Description:
    Enum to hold if: Transmit Mailbox Empty Interrupt is activated or not 
*/
typedef enum {
    TMEIE_DISABLE,
    TMEIE_ENABLE
} t_Transmit_Mailbox_Empty_Interrupt;

/*
  =============== The whole Interrupts that bxCAN provides ===============

  t_Sleep_Ack_Interrupt Sleep_Ack_Interrupt;
  t_Wakeup_Interrupt    Wakeup_Interrupt; 
  t_Error_Interrupt     Error_Interrupt;
  t_Last_Error_Code_Interrupt Last_Error_Code_Interrupt;
  t_Bus_Off_Interrupt         Bus_Off_Interrupt;

  t_Error_Passive_Interrupt   Error_Passive_Interrupt;
  t_Error_Warning_Interrupt   Error_Warning_Interrupt;

  t_FIFO_Overrun_Interrupt1   FIFO_Overrun_Interrupt1;
  t_FIFO_Full_Interrupt1      FIFO_Full_Interrupt1;
  t_FIFO_Message_Pending_Interrupt1   FIFO_Message_Pending_Interrupt1;

  t_FIFO_Overrun_Interrupt0   FIFO_Overrun_Interrupt0;
  t_FIFO_Full_Interrupt0      FIFO_Full_Interrupt0;
  t_FIFO_Message_Pending_Interrupt0   FIFO_Message_Pending_Interrupt0;

  t_Transmit_Mailbox_Empty_Interrupt  Transmit_Mailbox_Empty_Interrupt;

  =========================================================================
 */

/*
  Description: Structure to configure bxCAN: 
*/
typedef struct{
  t_MAilboxes_Priority MAilboxes_Priority;                  
  t_Received_FIFO_Lock_Mode Received_FIFO_Lock_Mode;
  t_Auto_Retransmission Auto_Retransmission;
  t_Automatic_wakeup_mode Automatic_wakeup_mode;
  t_Automatic_Bus_Off_Management  Automatic_Bus_Off_Management;
  t_Debug_freeze_Mode Debug_freeze_Mode; 
  t_Mode Time_Mode;

  t_Mode Silent_Mode;
  t_Mode LoopBack_Mode;
  
  uint8 Priority_Level;
  uint32 BaudRate_BTR_Value;
  
  t_Mode Rx_Interrupt;
}CAN_ConfigType;

/**********************************************************************************
*                           CAN Transmission Enumerations
***********************************************************************************/
/*
  Description:
    Enum to hold if the transmitted Frame is Data or Remote frame 
*/
typedef enum{
  Dara_Frame, Remote_Frame
}t_RTR;

/*
  Description:
    Enum to hold if the identifier is standard or extended
*/
typedef enum{
  Standard, Extended
}t_Identifier_Extention_Type;

/*
  Description: 
    Enum to represent DLC (Data Lenght Code) sizes from one byte to eight bytes 
*/
typedef enum {
    ONE_BYTE = 1, TWO_BYTE, THREE_BYTE, FOUR_BYTE, FIVE_BYTE, SIX_BYTE, SEVEN_BYTE, EIGHT_BYTE
} t_DLC_Size;

typedef enum
{
  MailBox_0, MailBox_1, MailBox_2
} t_MailBox_Number;
/*
  Description: Structure to configure bxCAN transmitted frame 
*/
typedef struct{
  t_MailBox_Number MailBox_Number;                         /* MailBox_0 or MailBox_1 or MailBox_2 */
  t_DLC_Size DLC_Size;                                     /* ONE_BYTE, TWO_BYTE, THREE_BYTE, FOUR_BYTE, FIVE_BYTE, SIX_BYTE, SEVEN_BYTE, EIGHT_BYTE */                
  t_Identifier_Extention_Type Identifier_Extention_Type;   /* Standard or Extended */
  uint16 Identifier;                                       /* Set the topic of the transmitted message */
  t_RTR xRTR;                                              /* Data Frame or Remote Frame */
  uint32 Data_To_Be_Sent;                               
}CAN_Frame_Ptr;

/*********************************************************************************
*                      Filter Configuration Enumerations
**********************************************************************************/
typedef enum{
  MASK_MODE,LIST_ID_MODE
}t_filter_Mode;

typedef enum{
  DUAL_16_BIT,SINGLE_32_BIT
}t_filter_Scale;

typedef enum{
  FIFO_0,FIFO_1
}t_filter_FIFO;

typedef struct{
  uint8 filter_number;
  t_filter_Mode Mode;
  t_filter_FIFO Assigned_FIFO;
  t_filter_Scale Scale;
  uint16 ID;
  uint32 Masked_bits;
  
  t_RTR xRTR;
  t_Identifier_Extention_Type Identifier_Extention_Type;

}Filter_Configuration;

typedef struct{
  
  Filter_Configuration Filter[FILTERS_NUMBER];

}Filter_ConfigType;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*
  Description:
    This function is used initiallize the CAN peripheral
 */
void CAN_Init(const CAN_ConfigType* Config_Ptr);

/*
  Description:
    This function is used to receive data from the FIFO according to specific filter
*/
uint32 CAN_Receive_Message(uint8 Required_Filter_ID);

/*
  Description:
    This function is used to perform a software master reset of the bxCAN controller.
 */
void Reset_bxCAN(void);

/*
  Description:
    This function is intended to transmit a CAN frame using one of the mailboxes of the CAN controller. 
*/
void CAN_Transmitte(const CAN_Frame_Ptr* CAN_Frame); 

/* 
  Description:
    This function is used to configuer the whole 14 filters presented in bxCAN1
 */
void Filters_Init( const Filter_ConfigType* Config_Ptr );

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

extern const Filter_ConfigType Filter_Configurations;
extern const CAN_ConfigType  CAN_Configurations;

#endif /* CAN_HEADER_FILE */