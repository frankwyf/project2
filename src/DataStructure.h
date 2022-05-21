#ifndef DataStructure_GUARD__H 
#define DataStructure_GUARD__H
#include <stdio.h>
/*
  The following part is denfinitions of variables
  the useage of each one is listed in the comments before
*/
/*the variable to store the width of the game*/
int Row;
/*the variable to store the lenght of the game*/
int Column;
/*the initial game borad,updated every time after evolution*/
int **Game;
/*the game borad after evolution */
int **NextGeneration;
/*the steps of the game*/
int Step;
/*the steps of the game*/
int Delay;
/*the file pointer to read and write from the file*/
FILE *game;
/*keep track of the step game is running*/
int move;
/*used in replay mode*/
int rRounds;

/*
  The following part is denfinitions of funtions
  the useage of each one is listed in the comments before
*/
/*read user input for size of the game*/
int map();
/*the function to initialize the Game*/
void initialGame();
/*ask whether the user want to decide the steps or not*/
int steps();
/*read in Game file*/
int Readfile(FILE *game);
/*write the result back*/
int WriteResult(FILE *game);
/*print stable game map*/
void PrintMap();
/*ask the player how fast it want the game to display*/
int delay();
/*the function to ask the user whether the game should be re-eastablished or not*/
void Ask();
/*the function to ask palyer whether to replay the game or not*/
void replay();

#endif