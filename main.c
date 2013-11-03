#include <msp430.h>
#include <Lab5_LCD_GAME.h>
#include "buttons/button.h"
#include "LCD/Lab4_LCD.h"

/*
 * main.c
 */

char flag = 0;
char isGameOver = 1;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    init_timer();
    init_buttons();
    __enable_interrupt();

    while(1)
    {
         	unsigned char player = initPlayer();

           	while (isGameOver)
           	{

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
