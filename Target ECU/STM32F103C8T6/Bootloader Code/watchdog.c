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
   
void IWDG_Init(void) {
    // Enable write access to IWDG_PR and IWDG_RLR registers
    IWDG->KR = 0x5555;

    // Set the prescaler to divide the LSI clock by 64
    IWDG->PR = IWDG_PR_PR_2;

    /* Reload the value with 5 seconds = 5*625 where 625 came from 40KHz for lSI Bus divided by the prescaler value 64 */
    IWDG->RLR = 3125;

    // Reload the IWDG counter
    IWDG->KR = 0xAAAA;

    // Start the IWDG
    IWDG->KR = 0xCCCC;
}

// Function to stop the Independent Watchdog (IWDG)
void IWDG_Stop(void) {
    // Reset the IWDG counter
    IWDG->KR = 0xAAAA;

    // Disable the write access to IWDG_PR and IWDG_RLR registers
    IWDG->KR = 0x0000;
}

/* END */





