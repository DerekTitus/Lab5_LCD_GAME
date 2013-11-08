Lab5_LCD_GAME
=============

This provides the code to play a game on the geek box LCD screen to move across the screen from the top left to the bottom right.

NOTES
=====

This code relies on the button library and LCD libraries.

Functions
=========

unsigned char initPlayer()
  Initializes player to starting position on board.
  0x80 is the upper left of the LCD
  
void printPlayer(unsigned char player)
  Prints player at the passed in position
  
void clearPlayer(unsigned char player)
  Clears old player
  
unsigned char movePlayer(unsigned char player, unsigned char direction)
  Given a player's current position and a direction, returns an updated player position
  
char didPlayerWin(unsigned char player, char isGameOver, char myString1[], char myString2[])
  Checks if player won
  If they won, prints winning strings
  Returns whether or not the game is over
  
char generateMines(char mineCheck, char myString1[], char myString2[])
  Prints two strings (player instructions)
  Checks to see if new mine can be placed against mineCheck
  Returns mine
  
char isMineLegal(char proposedMine, char placedMine)
  returns logic to test mine placement
  
void printMines(char mine1, char mine2)
  prints mines to LCD
