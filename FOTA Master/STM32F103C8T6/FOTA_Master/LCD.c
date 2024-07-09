/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: LCD.c
 *
 * Description: types for ARM
 *
 * Date Created: 12/8/2023
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

/**-------------------------INCLUDES Section------------------------**/
#include "LCD.h"
#include "Dio.h"

/**-------------------------Function Definition Section-------------**/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void)
{


	/* Configure the data port as output port */
#if(LCD_DATA_MODE == 8) /* Using 8 bit mode */
	{
	}
#elif(LCD_DATA_MODE == 4) /* Using 4 bit mode */
	{

		/* Send for 4 bit initialization of LCD  */
		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
		/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
	}

#endif

	LCD_sendCommand(DISPLAY_ON_CURSOR_OFF ); /* cursor off */
	LCD_sendCommand(LCD_CLR_DISPLAY); 		 /* clear LCD at the beginning */
}

/*----------------------------------------------------------------------------*/

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command)
{
	Dio_WriteChannel(DioConf_LCD_RS_CHANNEL_ID_INDEX,STD_LOW); /* Setting to Command Register selection */
	Delay_MS(1);
	Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX,STD_HIGH); /* Enable LCD */
	Delay_MS(1);

#if(LCD_DATA_MODE == 8)
	{
		//GPIO_writePort(LCD_OUTPUT_PORT, command); 			/* Sending the command through the 8 pins*/
/*              Dio_WriteChannel(DioConf_LCD_D0_CHANNEL_ID_INDEX, GET_BIT(data, 0));
		Dio_WriteChannel(DioConf_LCD_D1_CHANNEL_ID_INDEX, GET_BIT(data, 1));
		Dio_WriteChannel(DioConf_LCD_D2_CHANNEL_ID_INDEX, GET_BIT(data, 2));
		Dio_WriteChannel(DioConf_LCD_D3_CHANNEL_ID_INDEX, GET_BIT(data, 3));
		Dio_WriteChannel(DioConf_LCD_D4_CHANNEL_ID_INDEX, GET_BIT(data, 4));
		Dio_WriteChannel(DioConf_LCD_D5_CHANNEL_ID_INDEX, GET_BIT(data, 5));
		Dio_WriteChannel(DioConf_LCD_D6_CHANNEL_ID_INDEX, GET_BIT(data, 6));
		Dio_WriteChannel(DioConf_LCD_D7_CHANNEL_ID_INDEX, GET_BIT(data, 7));
*/
	}
#else
	{
		/* Sending the LAST four BITS */
		Dio_WriteChannel(DioConf_LCD_D4_CHANNEL_ID_INDEX, GET_BIT(command,4));
		Dio_WriteChannel(DioConf_LCD_D5_CHANNEL_ID_INDEX, GET_BIT(command,5));
		Dio_WriteChannel(DioConf_LCD_D6_CHANNEL_ID_INDEX, GET_BIT(command,6));
		Dio_WriteChannel(DioConf_LCD_D7_CHANNEL_ID_INDEX, GET_BIT(command,7));

		Delay_MS(1);
		Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW); /* De-activating the LCD */
		Delay_MS(1);
		Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH); /* Enable LCD */
		Delay_MS(1);

		/* Sending the FIRST four BITS */
		Dio_WriteChannel(DioConf_LCD_D4_CHANNEL_ID_INDEX, GET_BIT(command, 0));
		Dio_WriteChannel(DioConf_LCD_D5_CHANNEL_ID_INDEX, GET_BIT(command, 1));
		Dio_WriteChannel(DioConf_LCD_D6_CHANNEL_ID_INDEX, GET_BIT(command, 2));
		Dio_WriteChannel(DioConf_LCD_D7_CHANNEL_ID_INDEX, GET_BIT(command, 3));
	}
#endif

	/* Shared Part must be added at the END */
	Delay_MS(1);
	Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW); /* De-activating the LCD */
	Delay_MS(1);
}

/*----------------------------------------------------------------------------*/

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data)
{
	Dio_WriteChannel(DioConf_LCD_RS_CHANNEL_ID_INDEX, STD_HIGH); /* Activating the Data Register */
	Delay_MS(1);
	Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH); /* Activating the LCD */
	Delay_MS(1);


#if(LCD_DATA_MODE == 8)
	{
/*              Dio_WriteChannel(DioConf_LCD_D0_CHANNEL_ID_INDEX, GET_BIT(data, 0));
		Dio_WriteChannel(DioConf_LCD_D1_CHANNEL_ID_INDEX, GET_BIT(data, 1));
		Dio_WriteChannel(DioConf_LCD_D2_CHANNEL_ID_INDEX, GET_BIT(data, 2));
		Dio_WriteChannel(DioConf_LCD_D3_CHANNEL_ID_INDEX, GET_BIT(data, 3));
		Dio_WriteChannel(DioConf_LCD_D4_CHANNEL_ID_INDEX, GET_BIT(data, 4));
		Dio_WriteChannel(DioConf_LCD_D5_CHANNEL_ID_INDEX, GET_BIT(data, 5));
		Dio_WriteChannel(DioConf_LCD_D6_CHANNEL_ID_INDEX, GET_BIT(data, 6));
		Dio_WriteChannel(DioConf_LCD_D7_CHANNEL_ID_INDEX, GET_BIT(data, 7));
          
                Delay_MS(1);*/
	}
#else
	{
		/* Sending the LAST four BITS */
		Dio_WriteChannel(DioConf_LCD_D4_CHANNEL_ID_INDEX, GET_BIT(data, 4));
		Dio_WriteChannel(DioConf_LCD_D5_CHANNEL_ID_INDEX, GET_BIT(data, 5));
		Dio_WriteChannel(DioConf_LCD_D6_CHANNEL_ID_INDEX, GET_BIT(data, 6));
		Dio_WriteChannel(DioConf_LCD_D7_CHANNEL_ID_INDEX, GET_BIT(data, 7));

		Delay_MS(1);
		Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW); /* De-activating the LCD */
		Delay_MS(1);
		Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH); /* Enable LCD */
		Delay_MS(1);

		/* Sending the FIRST four BITS */
		Dio_WriteChannel(DioConf_LCD_D4_CHANNEL_ID_INDEX, GET_BIT(data, 0));
		Dio_WriteChannel(DioConf_LCD_D5_CHANNEL_ID_INDEX, GET_BIT(data, 1));
		Dio_WriteChannel(DioConf_LCD_D6_CHANNEL_ID_INDEX, GET_BIT(data, 2));
		Dio_WriteChannel(DioConf_LCD_D7_CHANNEL_ID_INDEX, GET_BIT(data, 3));
		Delay_MS(1);
	}
#endif

	Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW); /* De-activating the LCD */
	Delay_MS(1);
}

/*----------------------------------------------------------------------------*/

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str)
{
	uint8 a_stringCounter = 0; /* Counting the array of chars */

	while(Str[a_stringCounter] != '\0')
	{
		LCD_displayCharacter(Str[a_stringCounter]);
		a_stringCounter++;
	}
}

/*----------------------------------------------------------------------------*/

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 a_lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
	case 0:
          a_lcd_memory_address = col;
          break;
	case 1:
          a_lcd_memory_address = col + COL_1_BASE_ADDRESS;
          break;
        case 2:
          a_lcd_memory_address = col + COL_2_BASE_ADDRESS;
          break;
	case 3:
          a_lcd_memory_address = col + COL_3_BASE_ADDRESS;
          break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(a_lcd_memory_address | START_AT_FIRST_LINE);
}

/*----------------------------------------------------------------------------*/

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*----------------------------------------------------------------------------*/

/*
 * Description :
 * Display the required Char in a specified row and column index on the screen
 */
void LCD_displayCharRowColumn(uint8 row,uint8 col,uint8 data)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayCharacter(data); /* display the string */
}

/*----------------------------------------------------------------------------*/
/* Functions used for handling IntgerToString */
/*
 * Description :
 *  A static function used to reverse the passed string
 */
STATIC void reverse(char* str, int length)
{
	uint8 i, j;
	char temp;

	for (i = 0, j = length - 1; i < j; i++, j--) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}
/*
 * Description :
 *  A static function used to convert integer to strings
 */
STATIC char* itoa(int num, char* str, int base)
{
	uint8 i = 0;

	/* Handle 0 explicitly */
	if (num == 0)
	{
		str[i] = '0';
		str[i + 1] = '\0';
		return str;
	}

	/* Add the null terminator */
	str[i] = '\0';

	/* Convert the number to the corresponding base */
	while (num != 0)
	{
		i = i + 1;
		uint8 rem = num % base;
		str[i] = rem + '0';
		num = num / base;
	}

	// Reverse the string
	reverse(str, i + 1);

	return str;
}
/*----------------------------------------------------------------------------*/
/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
	char buff[16]; 			/* String to hold the ascii result */
        itoa(data,buff,10);  	/* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff); 	/* Display the string */
}

/*----------------------------------------------------------------------------*/

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLR_DISPLAY);
}

/**---------------------------------END-----------------------------**/


