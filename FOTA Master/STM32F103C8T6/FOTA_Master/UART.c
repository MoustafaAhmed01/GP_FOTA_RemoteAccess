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
#include "UART.h"
   
/* Disable interrupts (CPSID instruction) */   
void __disable_irq(void) 
{
    __asm("cpsid i"); 
}
/* Enable interrupts (CPSIE instruction) */
void __enable_irq(void) 
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
void UART_init( const UART_ConfigType * config )
{
    /* Set Pin 10 and Pin 9 in PortA as USART Receiver and USART Transmitter respectively  */
    Port_SetPinMode( PORTA_PIN_10 , PORT_PIN_FUNC_ALT_SERIAL_RX );
    Port_SetPinMode( PORTA_PIN_9  , PORT_PIN_FUNC_ALT_SERIAL_TX );
    
    /* Mask for Control Register 1 */
    USART_1_CR1_REG &= USART_1_CR1_MASK;
    
    /* Start setting the word length , parity mode and parity type according to the configuration */
    USART_1_CR1_REG |= ( config->Word_Length << M ) | ( config->Parity_Mode << PCE ) | (config->Parity_Type << PS) ;
      
    if( config->Event_Type == INTERRUPT )
    {
      /* Activate the Interrupts according to the required configuration */
      USART_1_CR1_REG |= ( config->PE_Interrupt << PEIE ) | ( config->TXE_INTERRUPT << TXEIE ) | ( config->TC_INTERRUPT << TCIE ) | ( config->RXNE_INTERRUPT << RXNEIE ) | ( config->IDLE_INTERRUPT << IDLEIE );     
      
      /* Set Global interrupt for the Cortex M */
      __enable_irq();
      
      /* Enable interrupt for UART 1 */ 
      NVIC_ISER1_REG |= ( 1 << (37-32) );
    
      /* Set the priority for the UART 1 */
      NVIC_PRI9_REG |= ( ( config->Priority_Level << 4 ) << 8 );
    }
    
    /* DMA Setup */
    if( config->DMA_CONTROL == DMA_TX_Enable )
    {
      CLEAR_BIT( USART_1_CR3_REG, DMAR );
      SET_BIT( USART_1_CR3_REG, DMAT );
    }
    else if( config->DMA_CONTROL == DMA_RX_Enable )
    {
      CLEAR_BIT( USART_1_CR3_REG, DMAT );
      SET_BIT( USART_1_CR3_REG, DMAR );
    }
    else
    {
      CLEAR_BIT( USART_1_CR3_REG, DMAR );
      CLEAR_BIT( USART_1_CR3_REG, DMAT );      
    }
    
    /* Activate the Transmitter enable and Receiver enable in USART_CR1 Register*/
    USART_1_CR1_REG |= ( 1 << TE ) | ( 1 << UE ) | ( 1 << RE );
    
    /* Set the Required BAUD RATE in USART_BRR  Mantisa Register */;
    USART_1_BRR_REG = (uint32)( (float32)((float32)(F_CPU / 16) / (config->Baud_Rate))+1 ) << DIV_MANTISSA ;
    
    /* Set the number of stop bits in USART_CR2 Register */
    USART_1_CR2_REG = USART_1_CR2_REG & ~( 0x00000003 << 12 ) | ( config->Stop_Bit << 12 );
    
 
          
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
    /* Wait until the transmission data register is empty */
    //while( ! BIT_IS_CLEAR( USART_1_SR_REG , TXE ) );
    
    /* Put the data that is meant to be send in the data register */
    USART_1_DR_REG = (uint8)data;
    
    /* Wait untill the transmission is completed */
    while( BIT_IS_CLEAR( USART_1_SR_REG , TC ) );
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
    /* Wait until there is a data to be read in the read data register */
    while( BIT_IS_CLEAR( USART_1_SR_REG , RXNE ) ); 
    
    CLEAR_BIT(USART_1_SR_REG , RXNE);
    
    /* Return the received data in the data register */
    return USART_1_DR_REG;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i=0;
	while(Str[i]!='\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}







