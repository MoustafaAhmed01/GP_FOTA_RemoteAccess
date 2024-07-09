 /******************************************************************************
 *
 * Module: PLL
 *
 * File Name: PLL.c
 *
 * Date Created: 12/27/2023
 *
 * Description: Source file for STM32F401RCT6 Microcontroller - Pll Driver.
 *
 * Author: Moustafa Ahmed
 ******************************************************************************/


/**-------------------------INCLUDES Section------------------------**/
#include "stm32f103c8t6_registers.h"
#include "PLL.h"

/**-------------------------Definitions & Config Section------------**/


/**-------------------------Function Definition---------------------**/

void SystemClockInit(void)
{
    /* Enable HSE */
    RCC_CR |= RCC_CR_HSEON;
    while (!(RCC_CR & RCC_CR_HSERDY));

    /* Enable Prefetch Buffer and set Flash Latency */
    FLASH_ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;

    /* Configure PLL */
    RCC_CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLXTPRE_HSE_DIV1;

    /* Enable PLL */
    RCC_CR |= RCC_CR_PLLON;
    while (!(RCC_CR & RCC_CR_PLLRDY));

    /* Select PLL as system clock */
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC_CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
}

/**-------------------------END------------------------------------**/

