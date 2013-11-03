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
						printPlayer(player);
						waitForP1ButtonRelease(BIT1);
						break;
                    case LEFT:
                    	clearPlayer(player);
						player -= 1;
						printPlayer(player);
						waitForP1ButtonRelease(BIT2);
                        break;
                    case UP:
                    	clearPlayer(player);
						player -= 0x40;
						printPlayer(player);
						waitForP1ButtonRelease(BIT3);
                        break;
                    case DOWN:
                    	clearPlayer(player);
						player += 0x40;
						printPlayer(player);
						waitForP1ButtonRelease(BIT4);
                    	break;

        }

        return player;
}

char didPlayerWin(unsigned char player)
{
        return player == 0xC7;
}
