#include <stdio.h>
#include "Check.h"
#include "DataStructure.h"

/*
  The follwing part will be 8 functions that check the 8 nighbours of a target cell
  Neighbours outside the boundary are assumed dead
*/
int CheckUp(int **Game,int i,int j){
    if (i==0){
        return 0;
    }
    else{
        return Game[i-1][j];
    }
}
int CheckDown(int **Game,int i,int j){
    if (i==Row-1){
        return 0;
    }
    else{
        return Game[i+1][j];
    }
}
int CheckLeft(int **Game,int i,int j){
    if (j==0){
        return 0;
    }
    else{
        return Game[i][j-1];
    }
}
int CheckRight(int **Game,int i,int j){
    if (j==Column-1){
        return 0;
    }
    else{
        return Game[i][j+1];
    }
}
int CheckUpRight(int **Game,int i,int j){
    if (i==0){
        return 0;
    }   
    if (j==Column-1){
        return 0;
    }
    else{
        return Game[i-1][j+1];
    } 
}
int CheckUpLeft(int **Game,int i,int j){
    if (i==0){
        return 0;
    }
    if (j==0){
        return 0;
    }
    else{
        return Game[i-1][j-1];
    }
}
int CheckDownLeft(int **Game,int i,int j){
    if (i==Row-1){
        return 0;
    }
    if (j==0){
        return 0;
    }
    else{
        return Game[i+1][j-1];
    }
}
int CheckDownRight(int **Game,int i,int j){
    if (i==Row-1){
        return 0;
    }
    if (j==Column-1){
        return 0;
    }
    else{
        return Game[i+1][j+1];
    }
}