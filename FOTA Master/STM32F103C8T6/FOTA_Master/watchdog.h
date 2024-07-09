/******************************************************************************
 *
 * Module: watchdog
 *
 * File Name: watchdog.h
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - watchdog Driver.
 *
 * Author: Moustafa Ahmed
 ******************************************************************************/
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "Std_Types.h"
#include "Common_Macros.h"
#include "stm32f103c8t6_registers.h"

/*
 * Description :
 * Watchdog timer
 */
void startWatchdogTimer(void);
/*-------------------------------------------------------------------*/

#endif /* WATCHDOG_H */
