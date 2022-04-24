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
//the game borad
int **Game;
//the steps of the game
int Step;


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



#endif