#include <msp430.h>
#include "Lab5_LCD_GAME.h"
#include "buttons/button.h"
#include "LCD/Lab4_LCD.h"

/*
 * main.c
 */

void init_timer()
{
    // do timer initialization work
	TACTL &= ~(MC1|MC0);        // stop timer

	TACTL |= TACLR;             // clear TAR

	TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?

	TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?

	TACTL &= ~TAIFG;            // clear interrupt flag

	TACTL |= MC1;               // set count mode to continuous

	TACTL |= TAIE;              // enable interrupt

	__enable_interrupt();       // enable maskable interrupts

}

void init_buttons()
{
    // do button initialization work
	configureP1PinAsButton(BIT1|BIT2|BIT3|BIT4);
}

char flag = 0;
char isGameOver = 1;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    init_timer();
    init_buttons();
    __enable_interrupt();
    initSPI();
    LCDinit();

    while(1)
    {
			flag = 0;
			isGameOver = 1;
    		char myString1[] = "YOU     ";
    	    char myString2[] = "WIN!      ";
    		unsigned char player = initPlayer();
         	char direction = 0;
         	printPlayer(player);

           	while (isGameOver)
           	{
           		if(isP1ButtonPressed(BIT1))
           		{
           			direction = RIGHT;
           			player = movePlayer(player, direction);
           		}

           		if(isP1ButtonPressed(BIT2))
           		{
           			direction = LEFT;
           			player = movePlayer(player, direction);
           		}

           		if(isP1ButtonPressed(BIT3))
           		{
           			direction = UP;
           			player = movePlayer(player, direction);
           		}

           		if(isP1ButtonPressed(BIT4))
           		{
           			direction = DOWN;
           			player = movePlayer(player, direction);
          		}

           		isGameOver = didPlayerWin(player, isGameOver, myString1, myString2);
            		/*
                     * while (game is on)
                     * {
                     *                 check if button is pushed (you don't want to block here, so don't poll!)
                     *                 if button is pushed:
                     *                         clear current player marker
                     *                         update player position based on direction
                     *                         print new player
                     *                         clear two second timer
                     *                         wait for button release (you can poll here)
                     * }

                     */
           	}
while(1){}
            	/*
            	                     * print game over or you won, depending on game result
            	                     *
            	                     * wait for button press to begin new game (you can poll here)
            	                     * wait for release before starting again
            	                     */
    }
	
	return 0;
}

// Flag for continuous counting is TAIFG
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
    TACTL &= ~TAIFG;            // clear interrupt flag
    flag += 1;
    if(flag == 4)
    {

    }
}


