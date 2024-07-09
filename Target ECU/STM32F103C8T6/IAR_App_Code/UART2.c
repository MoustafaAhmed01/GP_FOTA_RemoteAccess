/******************************************************************************
 *
 * Module: USART
 *
 * File Name: UART.c
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - UART Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/
#include "UART2.h"
   
/* Disable interrupts (CPSID instruction) */   
void __disable_irq_2(void) 
{
    __asm("cpsid i"); 
}
/* Enable interrupts (CPSIE instruction) */
void __enable_irq_2(void) 
{
    __asm("cpsie i"); 
}   
   
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */   
void UART2_init( const UART2_ConfigType * config )
{
    /* Set Pin 2 and Pin 3 in PortA as USART2 Receiver and USART2 Transmitter respectively  */
    Port_SetPinMode( PORTA_PIN_2  , PORT_PIN_FUNC_ALT_SERIAL_TX );
    Port_SetPinMode( PORTA_PIN_3  , PORT_PIN_FUNC_ALT_SERIAL_RX );
    
    /* Mask for Control Register 1 */
    USART_2_CR1_REG &= USART_2_CR1_MASK;
    
    /* Start setting the word length , parity mode and parity type according to the configuration */
    USART_2_CR1_REG |= ( config->Word_Length << M ) | ( config->Parity_Mode << PCE ) | (config->Parity_Type << PS) ;
      
    if( config->Event_Type == INTERRUPT_2 )
    {
      /* Activate the Interrupts according to the required configuration */
      USART_2_CR1_REG |= ( config->PE_Interrupt << PEIE ) | ( config->TXE_INTERRUPT << TXEIE ) | ( config->TC_INTERRUPT << TCIE ) | ( config->RXNE_INTERRUPT << RXNEIE ) | ( config->IDLE_INTERRUPT << IDLEIE );     
      
      /* Set Global interrupt for the Cortex M */
      __enable_irq_2();
      
      /* Enable interrupt for UART2 */ 
      NVIC_ISER1_REG |= ( 1 << (38-32) );  // Assuming UART2 interrupt is at index 28
      
      /* Set the priority for the UART2 interrupt */
      NVIC_PRI9_REG |= (  config->Priority_Level << 20 );  // Assuming UART2 priority register is PRI7
    }
    
    /* DMA Setup */
     /* DMA Setup */
    if( config->DMA_CONTROL == DMA_TX_Enable_2 )
    {
      CLEAR_BIT( USART_2_CR3_REG, DMAR );
      SET_BIT( USART_2_CR3_REG, DMAT );
    }
    else if( config->DMA_CONTROL == DMA_RX_Enable_2 )
    {
      CLEAR_BIT( USART_2_CR3_REG, DMAT );
      SET_BIT( USART_2_CR3_REG, DMAR );
    }
    else
    {
      CLEAR_BIT( USART_2_CR3_REG, DMAR );
      CLEAR_BIT( USART_2_CR3_REG, DMAT );      
    }
    
    /* Activate the Transmitter enable and Receiver enable in USART_CR1 Register*/
    USART_2_CR1_REG |= ( 1 << TE ) | ( 1 << UE ) | ( 1 << RE );
    
    /* Set the Required BAUD RATE in USART_BRR  Mantisa Register */;
    USART_2_BRR_REG = (uint32)( (float32)((float32)(F_CPU / 16) / (config->Baud_Rate))+1 ) << DIV_MANTISSA ;
    
    /* Set the number of stop bits in USART_CR2 Register */
    USART_2_CR2_REG = USART_2_CR2_REG & ~( 0x00000003 << 12 ) | ( config->Stop_Bit << 12 );
    
 
          
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART2_sendByte(const uint8 data)
{
    /* Wait until the transmission data register is empty */
    //while( ! BIT_IS_CLEAR( USART_2_SR_REG , TXE ) );
    
    /* Put the data that is meant to be send in the data register */
    USART_2_DR_REG = (uint8)data;
    
    /* Wait untill the transmission is completed */
    while( BIT_IS_CLEAR( USART_2_SR_REG , TC ) );
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART2_recieveByte(void)
{
    /* Wait until there is a data to be read in the read data register */
    while( BIT_IS_CLEAR( USART_2_SR_REG , RXNE ) ); 
    
    CLEAR_BIT(USART_2_SR_REG , RXNE);
    
    /* Return the received data in the data register */
    return USART_2_DR_REG;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART2_sendString(const uint8 *Str)
{
	uint8 i=0;
	while(Str[i]!='\0')
	{
		UART2_sendByte(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART2_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART2_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART2_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}







