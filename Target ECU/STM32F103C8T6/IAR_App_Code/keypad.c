/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: keypad.c
 *
 * Description: types for AVR
 *
 * Date Created: 15/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

/**-------------------------INCLUDES Section------------------------**/
#include "Dio.h"
#include "keypad.h"

/**-------------------------Extern Section--------------------------**/

/**-------------------------Static Section--------------------------**/

/**-------------------------Constants Section-----------------------**/

/**-------------------------Struct Section--------------------------**/

/**-------------------------Struct Members Section------------------**/

/**-------------------------Global Variables Section----------------**/

/* Private functions prototypes: */

#if(KEYPAD_NUM_COLS == 3)
static uint8 Keypad_4x3_adjustSwitchNumber(uint8);
#elif(KEYPAD_NUM_COLS == 4)
static uint8 Keypad_4x4_adjustSwitchNumber(uint8);
#endif
/**-------------------------Config Section--------------------------**/
/* Description: Called by the KEYPAD_Init function (only) used to fill the KEYPAD configurations structure */
static void KEYPAD_configurations(void)
{
  Dio_WriteChannel(DioConf_KEYPAD_R1_CHANNEL_ID_INDEX ,STD_LOW);
  Dio_WriteChannel(DioConf_KEYPAD_R2_CHANNEL_ID_INDEX ,STD_LOW);
  Dio_WriteChannel(DioConf_KEYPAD_R3_CHANNEL_ID_INDEX ,STD_LOW);
  Dio_WriteChannel(DioConf_KEYPAD_R4_CHANNEL_ID_INDEX ,STD_LOW);
}
/**-------------------------Function Definition Section-------------**/

/* Public functions definitions: */
uint8 Keypad_getPressedKey()
{
  /**-----------------------Local Variables----------------------**/
  uint8 row,col;

   /* Initializing KEYPAD Col's port directions */
   KEYPAD_configurations();
   
  /**-----------------------Main Section-------------------------**/

	while(1)
	{
		for(row = 0; row < KEYPAD_NUM_ROWS; row++ )
		{
                  /* Select one row to be high at a time */
                  Dio_WriteChannel(DioConf_KEYPAD_R1_CHANNEL_ID_INDEX + row,STD_HIGH);

                  /* Check for COLs that will read 1 */
                  for(col = 0; col < KEYPAD_NUM_COLS; col++)
                  {
                    if(Dio_ReadChannel(DioConf_KEYPAD_C1_CHANNEL_ID_INDEX + col))
                    {
#if(KEYPAD_NUM_COLS == 3)
					return Keypad_4x3_adjustSwitchNumber((row*KEYPAD_NUM_COLS)+col+1);
#elif(KEYPAD_NUM_COLS == 4)
					return Keypad_4x4_adjustSwitchNumber((row*KEYPAD_NUM_COLS)+col+1);
#endif
                    }   /* End if */
                    
                  }   /* End for(row=0;row<NUM_ROW; row++)*/
			/*--------------------------------------------------------*/
                        
                        /* Turn back the selected row to STD_LOW */
                        Dio_WriteChannel(DioConf_KEYPAD_R1_CHANNEL_ID_INDEX + row,   STD_LOW);       
			/*--------------------------------------------------------*/
                }   /* End for(col=0;col<NUM_COL;col++) */
                
        }   /* End while() */
        
}   /* End Keypad_getPressedKey() function */


/* Private functions definitions: */

#if(KEYPAD_NUM_COLS == 3)
/*
 * A function to make the keypad fit it's 4x3
 * design in proteus
 */
static uint8 Keypad_4x3_adjustSwitchNumber(uint8 buttonNumber)
{

	switch(buttonNumber)
	{
	case 10:
		return'*';
		break;
	case 11:
		return 0;
		break;
	case 12:
		return'#';
		break;
	default:
		return buttonNumber;
	}   /*End switch */

}   /* End Keypad_4x3_adjustSwitchNumber() function */
#elif(KEYPAD_NUM_COLS == 4)
/*
 * A function to make the keypad fit it's 4x4
 * design in proteus
 */
static uint8 Keypad_4x4_adjustSwitchNumber(uint8 buttonNumber)
{

	switch(buttonNumber)
	{
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return 'A';
		break;
	case 5:
		return '4';
		break;
	case 6:
		return '5';
		break;
	case 7:
		return '6';
		break;
	case 8:
		return'B';
		break;
	case 9:
		return '7';
		break;
	case 10:
		return '8';
		break;
	case 11:
		return '9';
		break;
	case 12:
		return'C';
		break;
	case 13:
		return'*';
		break;
	case 14:
		return '0';
		break;
	case 15:
		return'#';
		break;
	case 16:
		return'D';
		break;
	}   /* End switch */

        
}   /* End Keypad_4x4_adjustSwitchNumber() function */

/**---------------------------------END-----------------------------**/

#endif

