#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DataStructure.h"

int main(int argc, char **argv){
    printf("Wlecome to Conway's Game of Life!\n");
    Readfile();
    //confogure the size of the game by user input
    if (argc<3){
        steps();
        //wait untile user input is valid
        while (map()==1){
            map();
        }
        //create the initial map
        initialGame();
    }
    //configure size of game by commnad line argument 
    else{
        while (steps()==-1){
            steps();
        }
        printf("Size of the game configured in commad line!\n");
        int j;
	    for (j=0;j<strlen(argv[1]);j++){
		    if (!isdigit(argv[1][j])){
			    printf("\nOnly numbers are allowed! Reconfigure and start again.\n");
			    exit(-1);
		    }
		    else{continue;}
	    }
        Row=atoi(argv[1]);
        for (j=0;j<strlen(argv[2]);j++){
		    if (!isdigit(argv[2][j])){
			    printf("Only numbers are allowed! Reconfigure and start again.\n");
			    exit(-1);
		    }
		    else{continue;}
	    }
        Column=atoi(argv[2]);
        initialGame();
    }    
    return 0;
}
