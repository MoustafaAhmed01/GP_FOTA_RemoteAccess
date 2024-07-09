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
void DMA_Init( const DMA_ConfigType *DMA_Configuration )
{
   /* To Hold the ADDRESS of the registers of the passed channel */
   volatile uint32* DMA_Base_Address_Ptr = NULL_PTR; 
   volatile uint32* DMA_CCR_PTR          = NULL_PTR; 
   volatile uint32* DMA_CNDTR_PTR        = NULL_PTR; 
   volatile uint32* DMA_CPAR_PTR         = NULL_PTR; 
   volatile uint32* DMA_CMAR_PTR         = NULL_PTR; 
 
   switch(DMA_Configuration->Dma_Number)
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
   
   /* The casting ((volatile uint32 *) is essintial to make  */
   DMA_CCR_PTR   = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x08 + 20 * ( DMA_Configuration->Channel_number - 1 )));
   DMA_CNDTR_PTR = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x0C + 20 * ( DMA_Configuration->Channel_number - 1 )));
   DMA_CPAR_PTR  = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x10 + 20 * ( DMA_Configuration->Channel_number - 1 )));
   DMA_CMAR_PTR  = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x14 + 20 * ( DMA_Configuration->Channel_number - 1 )));
     
   *DMA_CCR_PTR &= DMA_CCR_MASK;
   *DMA_CCR_PTR |= ( DMA_Configuration->priority_level << PL) | ( DMA_Configuration->Circular_Mode << CIRC )    |\
                   ( DMA_Configuration->Memory_Size << MSIZE ) |( DMA_Configuration->Peripheral_Size << PSIZE ) |\
                   ( DMA_Configuration->Memory_Increament << MINC ) | ( DMA_Configuration->Peripheral_Increament << PINC );
    
   /* If Memory to Memory mode is used then the source is CMAR and the destination is the address in the CPAR */
   if( DMA_Configuration->Direction == Memory_to_Memory )
   {
      SET_BIT( *DMA_CCR_PTR, DIR );
      SET_BIT( *DMA_CCR_PTR, MEM2MEM );
   }
   else if( DMA_Configuration->Direction == Read_From_Peripheral )
   {
      CLEAR_BIT( *DMA_CCR_PTR, DIR );       
   }
   else if( DMA_Configuration->Direction == Read_From_Memory )
   {
      SET_BIT( *DMA_CCR_PTR, DIR );
   }
     
   *DMA_CNDTR_PTR = DMA_Configuration->Transfer_Number;
   *DMA_CMAR_PTR = DMA_Configuration->Buffer_Address;
   *DMA_CPAR_PTR = DMA_Configuration->Peripheral_Address;  
  
   SET_BIT( *DMA_CCR_PTR, EN );
}
void DMA_Enable( const DMA_ConfigType *DMA_Configuration)
{
   /* To Hold the ADDRESS of the registers of the passed channel */
   volatile uint32* DMA_Base_Address_Ptr = NULL_PTR; 
   volatile uint32* DMA_CCR_PTR          = NULL_PTR; 
  switch(DMA_Configuration->Dma_Number)
   {
     case 0: 
             /* Storing the base address of DMA 1 */ 
             DMA_Base_Address_Ptr = &DMA_1_BASE_ADDRESS;  
             
             /* Enabling the clock of DMA 1 */
        //     SET_BIT( RCC_AHBENR, 0 );
             
             break;
     case 1: 
              /* Storing the base address of DMA 2 */
             DMA_Base_Address_Ptr = &DMA_2_BASE_ADDRESS; 
             
             /* Enabling the clock of DMA 2 */
        //     SET_BIT( RCC_AHBENR, 1 );
             
             break;
   }
  
   DMA_CCR_PTR   = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x08 + 20 * ( DMA_Configuration->Channel_number - 1 )));
  
   SET_BIT( *DMA_CCR_PTR, EN );
}
void DMA_Disable(const DMA_ConfigType *DMA_Configuration)
{ /* To Hold the ADDRESS of the registers of the passed channel */
   volatile uint32* DMA_Base_Address_Ptr = NULL_PTR; 
   volatile uint32* DMA_CCR_PTR          = NULL_PTR; 
  switch(DMA_Configuration->Dma_Number)
   {
     case 0: 
             /* Storing the base address of DMA 1 */ 
             DMA_Base_Address_Ptr = &DMA_1_BASE_ADDRESS;  
             
             /* Enabling the clock of DMA 1 */
       //      SET_BIT( RCC_AHBENR, 0 );
             
             break;
     case 1: 
              /* Storing the base address of DMA 2 */
             DMA_Base_Address_Ptr = &DMA_2_BASE_ADDRESS; 
             
             /* Enabling the clock of DMA 2 */
    //         SET_BIT( RCC_AHBENR, 1 );
             
             break;
   }
 
   DMA_CCR_PTR   = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x08 + 20 * ( DMA_Configuration->Channel_number - 1 )));
   CLEAR_BIT( *DMA_CCR_PTR, EN );
}
void DMA_resetBuffer(uint8 *Memory_start)
{
  for(uint8 i=0;Memory_start[i]!='\0';i++)
  {
    Memory_start[i]='\0';
    
  }
  
}
void DMA_resetCNDTR(const DMA_ConfigType *DMA_Configuration)
{
     /* To Hold the ADDRESS of the registers of the passed channel */
   volatile uint32* DMA_Base_Address_Ptr = NULL_PTR; 
   volatile uint32* DMA_CNDTR_PTR        = NULL_PTR; 
   volatile uint32* DMA_CPAR_PTR         = NULL_PTR; 
   volatile uint32* DMA_CMAR_PTR         = NULL_PTR; 
 
   switch(DMA_Configuration->Dma_Number)
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
   
   /* The casting ((volatile uint32 *) is essential to make  */

   DMA_CNDTR_PTR = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x0C + 20 * ( DMA_Configuration->Channel_number - 1 )));
   DMA_CPAR_PTR  = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x10 + 20 * ( DMA_Configuration->Channel_number - 1 )));
   DMA_CMAR_PTR  = (volatile uint32 *)((volatile uint8 *)DMA_Base_Address_Ptr +( 0x14 + 20 * ( DMA_Configuration->Channel_number - 1 )));
   *DMA_CNDTR_PTR = DMA_Configuration->Transfer_Number;
   *DMA_CMAR_PTR = DMA_Configuration->Buffer_Address;
   *DMA_CPAR_PTR = DMA_Configuration->Peripheral_Address;  
  
  
  
  
  
}