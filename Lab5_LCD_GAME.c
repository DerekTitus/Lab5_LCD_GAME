/*
 * Lab5_LCD_GAME.c
 *
 *  Created on: Nov 3, 2013
 *      Author: C15Colin.Busho
 */

#include <msp430.h>
#include "Lab5_LCD_GAME.h"
#include "LCD/Lab4_LCD.h"
#include "buttons/button.h"
#include "random/rand.h"

unsigned char initPlayer()
{
        return 0x80;
}

void printPlayer(unsigned char player)
{
        writeCommandByte(player);
        writeDataByte('*');
}

void clearPlayer(unsigned char player)
{
        writeCommandByte(player);
        writeDataByte(' ');
}

unsigned char movePlayer(unsigned char player, unsigned char direction)
{
        switch (direction) {
                //
                // update player position based on direction of movement
                //
        			case RIGHT:
        				clearPlayer(player);
						player += 1;
						if (player == 0x88)
						{
							player = 0x87;
						}
						printPlayer(player);
						waitForP1ButtonRelease(BIT1);
						break;
                    case LEFT:
                    	clearPlayer(player);
						player -= 1;
						if (player == 0x7F)
						{
							player = 0x80;
						}
						if (player == 0xBF)
						{
							player = 0xC0;
						}
						printPlayer(player);
						waitForP1ButtonRelease(BIT2);
                        break;
                    case UP:
                    	clearPlayer(player);
						if (player >= 0xC0)
						{
							player -= 0x40;
						}
						printPlayer(player);
						waitForP1ButtonRelease(BIT3);
                        break;
                    case DOWN:
                    	clearPlayer(player);
                    	if (player <= 0x87)
						{
							player += 0x40;
						}
						printPlayer(player);
						waitForP1ButtonRelease(BIT4);
                    	break;

        }

        return player;
}

char didPlayerWin(unsigned char player, char isGameOver, char myString1[], char myString2[])
{
	if (player == 0xc7)
	{
		isGameOver = 0;
		LCDclear();
		writeString(myString1, 8);
		cursorToLineTwo();
		writeString(myString2, 8);
		__delay_cycles(1000000);
	}
	else{ isGameOver = 1;}
	return isGameOver;
}

char isMineLegal(char proposedMine, char placedMine)
{
	return ((proposedMine == (placedMine + 0x3F)) || (proposedMine == (placedMine + 0x40)) ||
			(proposedMine == (placedMine + 0x41)) || (proposedMine == (placedMine - 0x3F)) ||
			(proposedMine == (placedMine - 0x40)) || (proposedMine == (placedMine - 0x41)) ||
			(proposedMine == placedMine));
}

char generateMines(char mineCheck, char myString1[], char myString2[])
{
	char random = 0x81;
	LCDclear();
	writeString(myString1, 8);
	cursorToLineTwo();
	writeString(myString2, 8);
	do
	{
		random += 1;
		if (random == 0x88)
		{
			random = 0xC0;
		}
		if (random == 0xC7)
		{
			random = 0x81;
		}

		while (isMineLegal(random, mineCheck))
		{
			random += 1;
			if (random == 0x88)
			{
				random = 0xC0;
			}
			if (random == 0xC7)
			{
				random = 0x81;
			}
		}

	} while (!isP1ButtonPressed(BIT1));

	waitForP1ButtonRelease(BIT1);
	return random;

}

void printMines(char mine1, char mine2){
	writeCommandByte(mine1);
	writeDataByte('X');
	writeCommandByte(mine2);
	writeDataByte('X');
}
