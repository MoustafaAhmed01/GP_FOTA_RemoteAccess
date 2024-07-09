 /******************************************************************************
 *
 * Module: CAN
 *
 * File Name: CAN_PBCFG.c
 *
 * Description: Post Build Configuration Source file for STM32F103C8T6 Microcontroller - CAN Driver
 *
 * Author: Shady Alaa
 ******************************************************************************/

#include "CAN.h"
/*
  Initializing CAN
  *
  * MAilboxes_Priority : By ID just like FIFO
  * Received_FIFO_Lock_Mode : NO
  * Auto_Retransmission : Yes
  * Automatic_wakeup_mode : Yes
  * Automatic_Bus_Off_Management : Yes
  * Debug freeze Mode : Enable (freezed)
  * Time_Mode : Disable
  * Silent_Mode : Disable
  * LoopBack_Mode : Disable
  * BaudRate_BTR_Value : 0x001e0001 (1Mbps)
  * Interrupte: Enable    
  *
*/
const CAN_ConfigType CAN_Configurations={ Priority_BY_ORDER, Not_LOCKED, Enable_Retransmission, AUTO_Wakeup, AUTO_Bus_Off_Left, Debug_freeze_ENABLE, DISABLE, DISABLE, DISABLE, 1, 0x001c0011, DISABLE };
const Filter_ConfigType Filter_Configurations={ 
                                                FILTER_Bank_0,  MASK_MODE, FIFO_0, SINGLE_32_BIT, FILTER_0_ID,  0xFFE00007, Dara_Frame, Standard,
                                                FILTER_Bank_1,  MASK_MODE, FIFO_0, SINGLE_32_BIT, FILTER_1_ID,  0xFFE00007, Dara_Frame, Standard,
                                                FILTER_Bank_2,  LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_2_ID,  0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_3,  LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_3_ID,  0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_4,  LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_4_ID,  0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_5,  LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_5_ID,  0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_6,  LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_6_ID,  0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_7,  LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_7_ID,  0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_8,  LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_8_ID,  0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_9,  LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_9_ID,  0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_10, LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_10_ID, 0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_11, LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_11_ID, 0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_12, LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_12_ID, 0XFFFF, Dara_Frame, Standard,
                                                FILTER_Bank_13, LIST_ID_MODE, FIFO_0, SINGLE_32_BIT, FILTER_13_ID, 0XFFFF, Dara_Frame, Standard,
                                               };
                                                
                                                
                                                
                                                