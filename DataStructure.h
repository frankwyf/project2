#ifndef DataStructure_GUARD__H 
#define DataStructure_GUARD__H

/*
  The following part is denfinitions of variables
  the useage of each one is listed in the comments before
*/
//the variable to store the width of the game
int Row;
//the variable to store the lenght of the game
int Column;
//the initial game borad,updated every time after evolution
int **Game;
//the game borad after evolution 
int **NextGeneration;
//the steps of the game
int Step;
//the file pointer to read and write from the file
FILE *game;

/*
  The following part is denfinitions of funtions
  the useage of each one is listed in the comments before
*/
//read user input for size of the game
int map();
//the function to initialize the Game;
void initialGame();
//ask whether the user want to decide the steps or not
int steps();
//read in Game file
int Readfile(FILE *game);
//write the result back
int WriteResult(FILE *game);

#endif