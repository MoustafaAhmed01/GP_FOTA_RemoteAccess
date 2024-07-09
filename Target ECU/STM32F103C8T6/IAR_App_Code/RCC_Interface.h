/**********************************************************
* Author : Ehab Mohamed 
* Version: V1.0
* Date: 8 Nov 2021
***********************************************************/
#ifndef RCC_INTERFACE_H
    #define RCC_INTERFACE_H

	#include "RCC_Config.h"
#include "Platform_Types.h"

	#if(SYS_CLK == HSI)
        #define FCK 8000000
    #elif(SYS_CLK == HSE)
        #define FCK 16000000
    #else
        #define FCK (180000000U)

		#if(APB2_PRESCALE_DIV == 2 )
			#define APB2_CLK (FCK / 2)
		#endif

		#if(APB1_PRESCALE_DIV == 2 )
			#define APB1_CLK (FCK / 4)
		#endif

    #endif

    enum Bus
    {
        AHB1, AHB2, AHB3, APB1, APB2
    };

    enum AHB1_PerID
    {
        GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, RCC_DMA1 = 21, RCC_DMA2
    };

    enum AHB2_PerID
    {
        DCMI
    };


    enum APB1_PerID
    {
        RCC_TIM2, RCC_TIM3, RCC_TIM4, RCC_TIM5, RCC_TIM6, RCC_TIM7, RCC_TIM12, RCC_TIM13,
        RCC_TIM14, WWDG = 11, SPI2 = 14, SPI3, RCC_USART2 = 17,
        RCC_USART3, USART4, USART5, I2C1, I2C2, I2C3
    };

    enum APB2_PerID
    {
        TIM1, TIM8, RCC_USART1 = 4, USART6
    };

    /* Public Functions Prototypes */
    void RCC_InitSystemClock();
    void RCC_EnableClock(uint8, uint8);
    void RCC_DisableClock(uint8, uint8);


#endif
