#include <stdio.h>
#include <stdlib.h>
#include "DataStructure.h"

//Create the initial game
void initialGame(){
    int i,j;
    //create a two dimensional array to be used as the Game borad
    Game=(int **)malloc(sizeof(int)*Row);
    for (i=0;i<Row;i++){
        Game[i]=(int *)malloc(sizeof(int)*Cloumn);
        for (j=0;j<Cloumn;j++){
            //initail state of the game
            Game[i][j]=1;
            printf("%d,",Game[i][j]);
        }
    printf("\n");
    }
}