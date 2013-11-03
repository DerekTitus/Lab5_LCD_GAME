#include <msp430.h>
#include <Lab5_LCD_GAME.h>
#include "buttons/button.h"
#include "LCD/Lab4_LCD.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    unsigned char player = initPlayer();

            init_timer();
            init_buttons();
            __enable_interrupt();

            while(1)
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
                     *
                     * print game over or you won, depending on game result
                     *
                     * wait for button press to begin new game (you can poll here)
                     * wait for release before starting again
                     */
            }
	
	return 0;
}

//
// YOUR TIMER A ISR GOES HERE
//

void init_timer()
{
        // do timer initialization work
}

void init_buttons()
{
        // do button initialization work
}
