 /******************************************************************************
 *
 * Module: Delay
 *
 * File Name: Delay.c
 *
 * Date Created: 12/27/2023
 *
 * Description: Source file for STM32F401RCT6 Microcontroller - Delay Driver.
 *
 * Author: Moustafa Ahmed
 ******************************************************************************/

/**-------------------------INCLUDES Section------------------------**/
#include "Delay.h"

/**-------------------------Definitions & Config Section------------**/


/**-------------------------Function Definition---------------------**/
void Delay_MS(uint32 milliseconds) 
{
    // Calculate the number of cycles required for the delay
    uint32 cycles = (60 * milliseconds * 1000) / 6; // 6 cycles per loop iteration

    // Use a simple loop for the delay
    for (uint32 i = 0; i < cycles; ++i) {
        __asm("NOP"); // No operation (one cycle)
    }
}

/**-------------------------END------------------------------------**/










