
#include "potentiometer.h"
uint16 potentiometer_write(uint8 ADC_num , uint8 ADC_channel_id)
{
  uint16 adc_Result;
  adc_Result=ADC_readChannel(ADC_channel_id,ADC_num);
  uint16 tuner_value;
  tuner_value=(uint16)(((uint32)adc_Result*MAX_TUNE)/(ADC_MAXIMUM_THRESHOLD));
 // tuner_value=(uint16)(((uint32)adc_Result*MAX_TUNE*ADC_REF_VOLT)/(ADC_MAXIMUM_THRESHOLD*MOTOR_MAX_VOLT));
  
  return tuner_value;
 // return adc_Result;
}
