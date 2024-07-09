#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_
#include "adc.h"
#define MAX_TUNE 330
#define OUTPUT_MAX_VOLT  5


uint16 potentiometer_write(uint8 ADCx,uint8 ADC_channel_id);

#endif