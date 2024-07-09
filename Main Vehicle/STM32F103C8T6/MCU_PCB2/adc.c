 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the STm32f103c8 blue pill ADC driver
 *
 * Author: Shady Alaa Eldeen Mohammed
 *
 *******************************************************************************/
#include "adc.h"
#include "ADC_REG.h"
#include "stm32f103c8t6_registers.h"
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void delay_ms(uint32 ms)
{
  for (uint32 i=0;i<ms*500;i++)
  {
    asm("NOP");
  }
}
void ADC_init(ADC_Config* Config_ptr)
{
  
	/*Clock Enable by register RCC_apb2enr*/
  if(Config_ptr->ADC_num == ADC1)
  {
        SET_BIT(RCC_APB2ENR,ADC1EN_BIT);  /*Setting ADC1EN Bit*/
         
  }
  if((Config_ptr->ADC_num )== ADC2)
  {
        SET_BIT(RCC_APB2ENR,ADC2EN_BIT);  /*Setting ADC2EN Bit*/
  }
  

  
 SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,ADON_BIT);  /*Wake up ADC from power saving mode*/
 delay_ms(20);
 /**---------------------------EXTERNAL Trigger selection +ALIGN Type+ Sampling rate selection--------------------**/  
  if((Config_ptr->external_trig_mode == SW_START) && (Config_ptr->external_trig == ENABLE))
  { 
    SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,20); /*Enable selection bits below*/
    SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,17);
    SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,18);  
    SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,19);  
  }
  if(Config_ptr->allign_mode == LEFT)
   {
   SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,ALIGN_BIT); /*Setting ALIGN Bit*/ 
   }
   else if(Config_ptr->allign_mode == RIGHT)
   {
   CLEAR_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,ALIGN_BIT); /*Clearing ALIGN Bit*/
   }
  
  if(Config_ptr->channel_index >=10)
  {
    ADCx[Config_ptr->ADC_num]->ADC_SMPR1_REGISTER |=((Config_ptr->sample_select)<<((Config_ptr->channel_index*3)-30));
  }
  else
  {
    ADCx[Config_ptr->ADC_num]->ADC_SMPR2_REGISTER |=((Config_ptr->sample_select)<<(Config_ptr->channel_index*3));
  }
/**********************************************************************************************************/  
 CLEAR_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,CONT_BIT); /*Making it single conversion*/
 SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,CAL_BIT); /*Setting CAL Bit*/   /*enable Calibration to maximize accuracy*/
 while(GET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,CAL_BIT) !=0);
  if( Config_ptr->disc_mode == DISABLE)/*DiscMode*/
   {
     CLEAR_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER,DISCEN_BIT);  /*Clearing DISCEN Bit*/ 
   }
  else
  {
         SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER,DISCEN_BIT);  /*Setting DISCEN Bit*/ 
  }
   
  if(Config_ptr->scan_mode == ENABLE)
  {
    SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER,SCAN_BIT); /*Setting SCAN Bit*/ 
  }
 
    else if (Config_ptr->scan_mode == DISABLE)
  {
    CLEAR_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER,SCAN_BIT);
  }
 
  if(Config_ptr->ADC_num == ADC1 &&(Config_ptr->dual_mode !=Independent_Mode))/*DUAL mode*/
    {
      (ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER)=((ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER)&(0xFFF0FFFF))|(Config_ptr->dual_mode<<16);
    }

  

/**------------------------------Watchdog section---------------------------------------------------**/  
  if(Config_ptr->wd_en == ENABLE)
  {
    SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER,AWDEN_BIT); /*Setting AWDEN Bit*/ 
  }
  else
  {
    CLEAR_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER,AWDEN_BIT);
  }
  
  /*ADC Prescaling by setting ADCPRE bits with the prescaler value in RCC_CFG register*/
  //  RCC_CFGR=(0xFFFF3FFF &(RCC_CFGR))|((Config_ptr->ADC_prescaler)<<15);
    ADCx[Config_ptr->ADC_num]->ADC_HTR_REGISTER=ADC_MAXIMUM_THRESHOLD;
    ADCx[Config_ptr->ADC_num]->ADC_LTR_REGISTER=ADC_MINIMUM_THRESHOLD;   
  if(Config_ptr->wd_single == SINGLE)
   {
   SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR1_REGISTER,AWDSGL_BIT);  /*Setting AWDSGL Bit*/ 
   }
/*******************************************************************************************************/
  
/**------------------------------DMA section---------------------------------------------------**/  
  
  if((Config_ptr->DMA_req == ENABLE) &&((Config_ptr->ADC_num==ADC1 )))
   {
   SET_BIT(ADCx[Config_ptr->ADC_num]->ADC_CR2_REGISTER,DMA_BIT); /*Setting DMA Bit*/
   }
/*******************************************************************************************************/  


              
}

uint16 ADC_readChannel(uint8 channel_num,eADC_Num_t ADC_num)
{    
       
        ADCx[ADC_num]->ADC_SQR3_REGISTER &=0XFFFFFFE0; /* Clear channel */
	ADCx[ADC_num]->ADC_SQR3_REGISTER |= channel_num;
          SET_BIT(ADCx[ADC_num]->ADC_CR2_REGISTER,ADON_BIT);
           delay_ms(20);/*wait for tSTAB*/
         SET_BIT(ADCx[ADC_num]->ADC_CR2_REGISTER,ADON_BIT);
          delay_ms(50);
	/* Start conversion of regular channels */
	SET_BIT(ADCx[ADC_num]->ADC_CR2_REGISTER,SWSTART_BIT);   /*Setting SWSTART Bit*/
	/* Wait till end of operation flag is set */
	while (BIT_IS_CLEAR(ADCx[ADC_num]->ADC_SR_REGISTER,EOC_BIT)); /*CHECKING ON EOC BIT*/ 
     //   LCD_moveCursor(0,12);
     //   LCD_displayString("Ana 3det el EOC");
	uint16 a_result =(uint16) (ADCx[ADC_num]->ADC_DR_REGISTER);
	CLEAR_BIT(ADCx[ADC_num]->ADC_SR_REGISTER,EOC_BIT);
	return a_result;
}
