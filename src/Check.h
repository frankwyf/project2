#ifndef Check_GUARD__H 
#define Check_GUARD__H
/*
  The following part is denfinitions of funtions checking the neighbours 
*/
int CheckUp(int **Game,int i,int j);
int CheckDown(int **Game,int i,int j);
int CheckLeft(int **Game,int i,int j);
int CheckRight(int **Game,int i,int j);
int CheckUpRight(int **Game,int i,int j);
int CheckUpLeft(int **Game,int i,int j);
int CheckDownLeft(int **Game,int i,int j);
int CheckDownRight(int **Game,int i,int j);

#endif