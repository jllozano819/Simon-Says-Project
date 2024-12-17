/*
 * @file main.c
 *
 * @brief Main source code for the Simon Says program.
 *
 * This file contains the main entry point and function definitions for the Simon Says program.
 * It interfaces with the following:
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board Push Buttons (SW2 - SW5)
 *	- EduBase Board Seven-Segment Display
 *	- DMT-1206 Magnetic Buzzer
 *
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Wyatt Lopez Coggins, Jose Lozano
 */
 
#include "TM4C123GH6PM.h"

#include "GPIO.h"
#include "SysTick_Delay.h"
#include "Seven_Segment_Display.h"
#include "Buzzer.h"
#include "stdlib.h"



static uint8_t level = 0;
static uint8_t lv1array[] = {0, 0};
static uint8_t lv2array[] = {0, 0, 0};
static uint8_t lv3array[] = {0, 0, 0, 0};
const uint8_t lowlimit = 1;
const uint8_t uplimit = 4;
static uint8_t lv1playerarr[] = {0, 0};
static uint8_t lv2playerarr[] = {0, 0, 0};
static uint8_t lv3playerarr[] = {0, 0, 0, 0};
static int index1 = 0;
static int index2 = 0;
static int index3 = 0;
void Generate_Sequence(void);
void LED_Sound_Link(uint8_t link);
void Level_Config(void);
void Player_Sequence(void);
uint8_t Player_SeqConv(uint8_t conv);
void Sequence_Check(int seqlength);
void LEVEL_FAIL(void);
void LEVEL_PASS(void);
void BEAT_GAME(void);
void RESET_GAME(void);

int main(void)
{
	// Initialize the LEDs on the EduBase board (Port B)
	EduBase_LEDs_Init();
	
	//// Initialize the buttons (SW2 - SW5) on the EduBase board (Port D)
	EduBase_Button_Init();
		
	// Initialize the SysTick timer used to provide blocking delay functions
	SysTick_Delay_Init();
	
	// Initialize the Seven-Segment Display on the EduBase board
	Seven_Segment_Display_Init();
	
	// Initialize the Initialize the DMT-1206 Magnetic Buzzer (Port C)
	Buzzer_Init();
	
	// Initialize the LaunchPad RGB LED (Port F)
	RGB_LED_Init();
	
	while(1)
	{
		Generate_Sequence();
		
		Level_Config();
	}
}

/**
 * @brief The Generate_Sequence function creates the random sequence for the game.
 *
 * This function creates a random sequence for the level 1, 2, and 3 arrays. It 
 * uses a for loop to fill the array with a random sequence. The rand function is
 * used to create the random sequence in the array. The random elements in the array 
 * are limited to a minimum and maximum value of 1 and 4 respectively. 
 *
 * @param None
 *
 * @return None
 */
void Generate_Sequence(void)
{
	for (int i = 0; i < 2; i++)
	{
		lv1array[i] = rand() % (uplimit - lowlimit + 1) + lowlimit;
	}
	
	for (int i = 0; i < 3; i++)
	{
		lv2array[i] = rand() % (uplimit - lowlimit + 1) + lowlimit;
	}
	
	for (int i = 0; i < 4; i++)
	{
		lv3array[i] = rand() % (uplimit - lowlimit + 1) + lowlimit;
	}
}

/**
 * @brief The LED_Sound_Link function turns on the appropriate LED and
 * plays the assigned note when a button is pressed.
 *
 * This function creates the sound profile for each button and also 
 * turns on the appropriate LED when a button is pressed. 
 * It does this by using a switch case to determine which case 
 * or button has been pressed and will activate the LED and sound.
 *
 * @param link An unsigned 8 bit integer representing index of the level and player arrays.
 *						 Used to determine which LED and Sound should be played.
 *
 * @return None
 */
void LED_Sound_Link(uint8_t link)
{
	switch(link)
	{
		case 1:
		{
			EduBase_LEDs_Output(0x01);
			Play_Note(G4_NOTE, 50);
		}
		break;
		
		case 2:
		{
			EduBase_LEDs_Output(0x02);
			Play_Note(A4_NOTE, 50);
		}
		break;
		
		case 3:
		{
			EduBase_LEDs_Output(0x04);
			Play_Note(B4_NOTE, 50);
		}
		break;
		
		case 4:
		{
			EduBase_LEDs_Output(0x08);
			Play_Note(C5_NOTE, 50);
		}
		break;
		
		default:
		{
			EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
		}
		break;
	}
}

/**
 * @brief The Level_Config function is in charge of playing each level.
 *
 * This function uses a switch case to play each level of Simon Says. It will display the level 
 * on the Seven Segment display by using the level variable. The level variable is used for the
 * switch case to determine which level it is on. Then it will display the level's array and
 * will use the Player_Sequence and Sequence_Check functions to read and check the players input.
 *
 * @param None
 *
 * @return None
 */
void Level_Config(void)
{
	Seven_Segment_Display(level+1);
	RGB_LED_Output(RGB_LED_BLUE);
	switch(level)
	{
		case 0:
		{
			for (int i = 0; i < 2; i++)
			{
				LED_Sound_Link(lv1array[i]);
				SysTick_Delay1ms(500);
				EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
				SysTick_Delay1ms(500);
			}
			Player_Sequence();
			Sequence_Check(2);
			break;
		}
		case 1:
		{
			for (int i = 0; i < 3; i++)
			{
				LED_Sound_Link(lv2array[i]);
				SysTick_Delay1ms(500);
				EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
				SysTick_Delay1ms(500);
			}
			Player_Sequence();
			Sequence_Check(3);
			break;
		}
		case 2:
		{
			for (int i = 0; i < 4; i++)
			{
				LED_Sound_Link(lv3array[i]);
				SysTick_Delay1ms(500);
				EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
				SysTick_Delay1ms(500);
			}
			Player_Sequence();
			Sequence_Check(4);
			break;
		}
	}
}

/**
 * @brief The Player_Sequence function records the players sequence.
 *
 * This function will use a switch case and the level variable to determine which
 * level the player is on. Each case will then use a while loop to make sure that  
 * the right amount of elements have been taken from the player's input. It will
 * use the variables index1, index2, and index3 to assure that the proper amount of
 * elements are being recorded. The elements will be recorded in the level player arrays
 * with the Player_SeqConv function determining the value of the elements that 
 * come from the button status. When it completes the last level the index variables will reset.
 *
 * @param None
 *
 * @return None
 */
void Player_Sequence(void)
{
	switch(level)
	{
		case 0:
		{
			while (index1 == 0 || index1 == 1)
			{
				uint8_t button_status = Get_EduBase_Button_Status();
				if (button_status != 0)
				{
					lv1playerarr[index1] = Player_SeqConv(button_status);
					LED_Sound_Link(lv1playerarr[index1]);
					index1 = index1 + 1;
				}
			}
		}
		break;
		case 1:
		{
			while (index2 == 0 || index2 == 1 || index2 == 2)
			{
				uint8_t button_status = Get_EduBase_Button_Status();
				if (button_status != 0)
				{
					lv2playerarr[index2] = Player_SeqConv(button_status);
					LED_Sound_Link(lv2playerarr[index2]);
					index2 = index2 + 1;
				}
			}
		}
		break;
		case 2:
		{
			while (index3 == 0 || index3 == 1 || index3 == 2 || index3 == 3)
			{
				uint8_t button_status = Get_EduBase_Button_Status();
				if (button_status != 0)
				{
					lv3playerarr[index3] = Player_SeqConv(button_status);
					LED_Sound_Link(lv3playerarr[index3]);
					index3 = index3 + 1;
				}
				if (index3 == 4)
				{
					index1 = 0;
					index2 = 0;
					index3 = 0;
					break;
				}
			}
		}
		break;
	}
}

/**
 * @brief The Player_SeqConv function returns a desired converted value for the player array.
 *
 * This function uses a switch case where each case is determined by the button status 
 * of the EduBase board. Each case will make the variable val a specified value. 
 * This value is then returned to be used in the Player_Sequence function.
 *
 * @param conv An 8-bit unsigned integer representing the status of the EduBase Board buttons
 *						 that was passed to the function. Used to determine which value should be placed 
 *						 in the player arrays.
 *
 * @return val An 8-bit unsigned integer representing the desired value to be placed in the
 *						 players arrays.
 */
uint8_t Player_SeqConv(uint8_t conv)
{
	uint8_t val = 0;
	switch(conv)
	{
		case 0x01:
		{
			val = 1;
			break;
		}
		case 0x02:
		{
			val = 2;
			break;
		}
		case 0x04:
		{
			val = 3;
			break;
		}
		case 0x08:
		{
			val = 4;
			break;
		}
	}
	return val;
}

/**
 * @brief The Sequence_Check function will check the player's input.
 *
 * This function uses a switch case to compare the player's array with the randomly
 * generated array. The for loop is used to check the elements in each array. 
 * If the arrays are not the same then the LEVEL_FAIL function will be executed. If they
 * are the same the LEVEL_PASS function will be executed. When the last level is passed the 
 * BEAT_GAME function will be called.
 *
 * @param seqlength An integer representing the length of a sequence. Used to ensure the 
 *									correct number of array indexes are checked.
 *
 * @return None
 */
void Sequence_Check(int seqlength)
{
	switch(level)
	{
		case 0:
		{
			for(int i = 0; i < seqlength; i++)
			{
				if (lv1array[i] != lv1playerarr[i])
				{
					LEVEL_FAIL();
					break;
				}
				else
				{
					if (i == seqlength - 1)
					{
						LEVEL_PASS();
					}
				}
			}
		}
		break;
		case 1:
		{
			for(int i = 0; i < seqlength; i++)
			{
				if (lv2array[i] != lv2playerarr[i])
				{
					LEVEL_FAIL();
					break;
				}
				else
				{
					if (i == seqlength - 1)
					{
						LEVEL_PASS();
					}
				}
			}
		}
		break;
		case 2:
		{
			for(int i = 0; i < seqlength; i++)
			{
				if (lv3array[i] != lv3playerarr[i])
				{
					LEVEL_FAIL();
					break;
				}
				else
				{
					if (i == seqlength - 1)
					{
						BEAT_GAME();
					}
				}
			}
		}
		break;
	}
}

/**
 * @brief The LEVEL_FAIL function is used to reset the game if a level is failed.
 *
 * This function will be called when the player array and the randomly generated
 * array are not the same. This means that the player failed the level. All the LEDs will
 * flash to signify the level is failed and it will restart the game.
 *
 * @param None
 *
 * @return None
 */
void LEVEL_FAIL(void)
{
	for(int i = 0; i < 4; i++)
	{
		RGB_LED_Output(RGB_LED_RED);
		EduBase_LEDs_Output(EDUBASE_LED_ALL_ON);
		SysTick_Delay1ms(500);
		RGB_LED_Output(RGB_LED_OFF);
		EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
		SysTick_Delay1ms(500);
	}
	
	RESET_GAME();
}

/**
 * @brief The LEVEL_PASS function is used to advance levels in the game.
 *
 * This function will flash the LEDs in a specific pattern (0x09) when a level is passed
 * and will increase the level variable by 1 to signify that it is going to the next level.
 *
 * @param None
 *
 * @return None
 */
void LEVEL_PASS(void)
{
	for(int i = 0; i < 4; i++)
	{
		RGB_LED_Output(RGB_LED_GREEN);
		EduBase_LEDs_Output(0x09);
		SysTick_Delay1ms(500);
		RGB_LED_Output(RGB_LED_OFF);
		EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
		SysTick_Delay1ms(500);
	}
	level = level + 1;
}

/**
 * @brief The BEAT_GAME function is used when all levels have been passed.
 *
 * This function will flash the LEDs in a specific pattern (0x06) signifying that the player
 * has beat the game and will then call the RESET_GAME function.
 *
 * @param None
 *
 * @return None
 */
void BEAT_GAME(void)
{
	Seven_Segment_Display(0);
	RGB_LED_Output(RGB_LED_GREEN);
	EduBase_LEDs_Output(0x06);
	SysTick_Delay1ms(3000);
	RESET_GAME();
}

/**
 * @brief The RESET_GAME function will reset the game when it is beaten or failed.
 *
 * This function will clear all arrays and variables to restart the game from
 * the beginning. 
 *
 * @param None
 *
 * @return None
 */
void RESET_GAME(void)
{
	for(int i = 0; i < 2; i++)
	{
		lv1array[i] = 0;
		lv1playerarr[i] = 0;
	}
	
	for(int i = 0; i < 3; i++)
	{
		lv2array[i] = 0;
		lv2playerarr[i] = 0;
	}
	for(int i = 0; i < 4; i++)
	{
		lv3array[i] = 0;
		lv3playerarr[i] = 0;
	}
	index1 =0;
	index2 = 0;
	index3 = 0;
	level = 0;
}