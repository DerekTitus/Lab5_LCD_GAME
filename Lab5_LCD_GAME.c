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
	}
	return isGameOver;
}
