 /******************************************************************************
 *
 * Module: DMA
 *
 * File Name: DMA.c
 *
 * Description: Source file for STM32F401RCT6 Microcontroller - DMA Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#include "DMA.h"
#include "stm32f103c8t6_registers.h"
#include "DMA_Registers.h"

/* Description: Used for initialization of DMA */
void DMA_Init( DMA_ConfigType DMA_Configuration )
{
   /* To Hold the ADDRESS of the registers of the passed channel */
   volatile uint32* DMA_Base_Address_Ptr = NULL_PTR; 
   volatile uint32* DMA_CCR_PTR    = NULL_PTR; 
   volatile uint32* DMA_CNDTR_PTR  = NULL_PTR; 
   volatile uint32* DMA_CPAR_PTR   = NULL_PTR; 
   volatile uint32* DMA_CMAR_PTR   = NULL_PTR; 
 
   switch(DMA_Configuration.Dma_Number)
   {
     case 0: 
             /* Storing the base address of DMA 1 */ 
             DMA_Base_Address_Ptr = &DMA_1_BASE_ADDRESS;  
             
             /* Enabling the clock of DMA 1 */
             SET_BIT( RCC_AHBENR, 0 );
             
             break;
     case 1: 
              /* Storing the base address of DMA 2 */
             DMA_Base_Address_Ptr = &DMA_2_BASE_ADDRESS; 
             
             /* Enabling the clock of DMA 2 */
             SET_BIT( RCC_AHBENR, 1 );
             
             break;
   }
   
   /* The casting ((volatile uint32 *) is essintial */
   DMA_CCR_PTR   = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x08 + 20 * ( DMA_Configuration.Channel_number - 1 )));
   DMA_CNDTR_PTR = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x0C + 20 * ( DMA_Configuration.Channel_number - 1 )));
   DMA_CPAR_PTR  = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x10 + 20 * ( DMA_Configuration.Channel_number - 1 )));
   DMA_CMAR_PTR  = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x14 + 20 * ( DMA_Configuration.Channel_number - 1 )));
     
   /* First mask all the registers that will be used */
   *DMA_CCR_PTR &= DMA_CCR_MASK;
   *DMA_CNDTR_PTR &= DMA_CNDTR_MASK;
   /* Set the initial value for CPAR and CMAR to zero */
   *DMA_CPAR_PTR = 0;
   *DMA_CMAR_PTR = 0;
   
   /* Set the peripheral register address in the DMA_CPARx register */
   *DMA_CPAR_PTR = DMA_Configuration.Peripheral_Address;  
    
   /*  Set the memory address in the DMA_CMARx register */
   *DMA_CMAR_PTR = DMA_Configuration.Buffer_Address;
   
   /* Configure the total number of data to be transferred in the DMA_CNDTRx register */ 
   *DMA_CNDTR_PTR = DMA_Configuration.Transfer_Number;
   
   /* Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register */
   *DMA_CCR_PTR |= ( DMA_Configuration.priority_level << PL); 
   
   /*  Configure data transfer direction, circular mode, peripheral & memory incremented mode, peripheral & memory data size, and interrupt 
       after half and/or full transfer in the DMA_CCRx register */
   *DMA_CCR_PTR |= ( DMA_Configuration.Circular_Mode << CIRC ) | ( DMA_Configuration.Memory_Size << MSIZE ) |\
                   ( DMA_Configuration.Peripheral_Size << PSIZE ) | ( DMA_Configuration.Memory_Increament << MINC ) |\
                   ( DMA_Configuration.Peripheral_Increament << PINC );
    
   /* If Memory to Memory mode is used then the source is CMAR and the distination is the address in the CPAR */
   if( DMA_Configuration.Direction == Memory_to_Memory )
   {
      SET_BIT( *DMA_CCR_PTR, DIR );
      SET_BIT( *DMA_CCR_PTR, MEM2MEM );
   }
   else if( DMA_Configuration.Direction == Read_From_Peripheral )
   {
      CLEAR_BIT( *DMA_CCR_PTR, DIR );       
   }
   else if( DMA_Configuration.Direction == Read_From_Memory )
   {
      SET_BIT( *DMA_CCR_PTR, DIR );
   }

   /* Activate the channel by setting the ENABLE bit in the DMA_CCRx register */
   SET_BIT( *DMA_CCR_PTR, EN );
}

void DMA_ReInit(DMA_ConfigType DMA_Configuration)
{
     volatile uint32* DMA_Base_Address_Ptr = NULL_PTR; 
     switch(DMA_Configuration.Dma_Number)
     {
       case 0: 
               /* Storing the base address of DMA 1 */ 
               DMA_Base_Address_Ptr = &DMA_1_BASE_ADDRESS;                                
               break;
       case 1: 
                /* Storing the base address of DMA 2 */
               DMA_Base_Address_Ptr = &DMA_2_BASE_ADDRESS;                
               break;
     }
    volatile uint32* DMA_CCR_PTR = (volatile uint32*)((volatile uint8*)DMA_Base_Address_Ptr + (0x08 + 20 * (DMA_Configuration.Channel_number - 1)));
    volatile uint32* DMA_CNDTR_PTR = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x0C + 20 * ( DMA_Configuration.Channel_number - 1 )));
    volatile uint32* DMA_CMAR_PTR  = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x14 + 20 * ( DMA_Configuration.Channel_number - 1 )));
    
    // Stop DMA transfer
    CLEAR_BIT(*DMA_CCR_PTR, EN);

    // Reset DMA transfer pointer
    *DMA_CMAR_PTR = DMA_Configuration.Buffer_Address;
    *DMA_CNDTR_PTR = DMA_Configuration.Transfer_Number;

    // Restart DMA transfer
    SET_BIT(*DMA_CCR_PTR, EN);
}