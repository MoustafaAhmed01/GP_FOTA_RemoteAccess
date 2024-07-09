/******************************************************************************
 *
 * Module: WATCHDOG
 *
 * File Name: watchdog.c
 *
 * Description: source file for STM32F103C8T6 Microcontroller - watchdog Driver.
 *
 * Author: Moustafa Ahmed
 ******************************************************************************/
#include "watchdog.h"
   
void startWatchdogTimer(void) {
    // Enable Watchdog peripheral clock
    RCC_APB1ENR |= (1 << 11);  // Bit 11 is the WWDG clock enable bit

    // Set prescaler to 8 (72 MHz / 8 = 9 MHz)
    WWDG_CFR = (0x7F << 0) | (1 << 7) | (1 << 9);  // Window value = 0x7F, Prescaler = 8, Watchdog enabled

    // Enable Watchdog
    WWDG_CR |= (1 << 7);  // Start the watchdog timer

    // Loop until the watchdog reset occurs (you may add additional logic here if needed)
    while (!(WWDG_SR & (1 << 0)));  // Wait until the watchdog flag is set, indicating a reset
}

/* END */





