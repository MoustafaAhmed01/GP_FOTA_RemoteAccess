#include "DMA.h"
#include "UART_Regs.h"
uint8 Data_Array[500]={0};
//uint8 LPWAN_Data[100]={0};
const DMA_ConfigType  DMA_Configurations = {DMA_1,DMA_CHANNEL_5,Very_High,Bits_8,Bits_8,D_Enable,D_Disable,D_Enable,Read_From_Peripheral,500,(uint32)(Data_Array),(uint32)&USART_1_DR_REG};
//const DMA_ConfigType  DMA_7_Configurations= {DMA_1,DMA_CHANNEL_7,Very_High,Bits_8,Bits_8,D_Enable,D_Disable,D_Enable,Read_From_Peripheral,500,(uint32)(LPWAN_Data),(uint32)&USART_2_DR_REG};