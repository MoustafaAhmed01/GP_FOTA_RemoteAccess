/**********************************************************
* Author : Ehab Mohamed 
* Version: V1.0
* Date: 8 Nov 2021
***********************************************************/
#ifndef RCC_PRIVATE_H
    #define RCC_PRIVATE_H

	#define RCC_CR (*((volatile uint32*)0x40023800))
	#define RCC_PLLCFGR (*((volatile uint32*)0x40023804))
	#define RCC_CFGR (*((volatile uint32*)0x40023808))

    #define RCC_AHB1ENR (*((volatile uint32*)0x40023830))
    #define RCC_AHB2ENR (*((volatile uint32*)0x40023834))
    #define RCC_AHB3ENR (*((volatile uint32*)0x40023838))
    #define RCC_APB1ENR (*((volatile uint32*)0x40023840))
    #define RCC_APB2ENR (*((volatile uint32*)0x40023844))




#endif


