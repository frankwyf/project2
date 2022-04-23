#include <stdio.h>
#include <stdlib.h>
#include "DataStructure.h"

int main(int argc, char **argv){
    //confogure the size of the game by user input
    if (argc<3){
        printf("Wlecome to Conway's Game of Life!\n");
        printf("Enter Rows of the Game:");
        scanf("%d",&Row);
        printf("Enter columns of the Game:");
        scanf("%d",&Cloumn);
        initialGame();
    }
    //configure size of game by commnad line argument 
    else{
        Row=atoi(argv[1]);
        Cloumn=atoi(argv[2]);
        initialGame();
    }    
    return 0;
}
