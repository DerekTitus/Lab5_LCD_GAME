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
	P1IE |= BIT1|BIT2|BIT3|BIT4;                 // enable the interrupts
	P1IES |= BIT1|BIT2|BIT3|BIT4;                   // configure interrupt to sense falling edges
}

char flag = 0;
char isGameOver = 1;
char myString1[] = "YOU     ";
char myString2[] = "WIN!      ";
char myString3[] = "YOU     ";
char myString4[] = "LOSE!     ";

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

			char startover = 1;
			LCDclear();
    		unsigned char player = initPlayer();
         	char direction = 0;
         	printPlayer(player);

           	while (isGameOver)
           	{
           		if(isP1ButtonPressed(BIT1))
           		{
           			direction = RIGHT;
           			player = movePlayer(player, direction);
           			TAR = 0;
           			flag = 0;
           		}

           		if(isP1ButtonPressed(BIT2))
           		{
           			direction = LEFT;
           			player = movePlayer(player, direction);
           			TAR = 0;
					flag = 0;
           		}

           		if(isP1ButtonPressed(BIT3))
           		{
           			direction = UP;
           			player = movePlayer(player, direction);
           			TAR = 0;
					flag = 0;
           		}

           		if(isP1ButtonPressed(BIT4))
           		{
           			direction = DOWN;
           			player = movePlayer(player, direction);
           			TAR = 0;
					flag = 0;
          		}

           		isGameOver = didPlayerWin(player, isGameOver, myString1, myString2);

           	}

           	while(startover)
           	{
           		flag = 0;

           		if(isP1ButtonPressed(BIT1))
				{
           			startover = 0;
           			waitForP1ButtonRelease(BIT1);
				}

           		if(isP1ButtonPressed(BIT2))
				{
					startover = 0;
					waitForP1ButtonRelease(BIT2);
				}

           		if(isP1ButtonPressed(BIT3))
				{
					startover = 0;
					waitForP1ButtonRelease(BIT3);
				}

           		if(isP1ButtonPressed(BIT4))
				{
					startover = 0;
					waitForP1ButtonRelease(BIT4);
				}

           	}
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
    	isGameOver = 0;
		LCDclear();
		writeString(myString3, 8);
		cursorToLineTwo();
		writeString(myString4, 8);
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void)
{
    if (P1IFG & BIT1)
    {
        P1IFG &= ~BIT1;                            // clear flag
        while (1) {}                            // toggle LED 2
    }

    if (P1IFG & BIT2)
    {
        P1IFG &= ~BIT2;                         // clear flag
        P1OUT ^= BIT0;                            // toggle LED 1
    }

    if (P1IFG & BIT3)
    {
        P1IFG &= ~BIT3;                         // clear P1.3 interrupt flag
        P1OUT ^= BIT0|BIT6;                     // toggle both LEDs
    }
}


