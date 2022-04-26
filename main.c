#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DataStructure.h"

int main(int argc, char **argv){
    printf("Wlecome to Conway's Game of Life!\n");
    //confogure the size of the game by user input
    if (argc<3){
        //read the initial file in
        if (Readfile()==0){
            //ask the user whether to change the size of the game or not
            printf("\nThe world is %i rows and %i columns\nDo you want to change (enter 'y' if you do)?\n",Row,Column);
            char Option=getchar(); 
            if (Option=='y'){
                //wait untile user input is valid
                while (map()==1){
                    map();
                }
                //create the initial map
                initialGame();
            }
            else{
                printf("\nGame continue with size %i x %i.\n",Row,Column);
                printf("\nStill want to change size? Restart the game.\n");
            }
        }
        //if file read in failed, start a new game
        else if (Readfile()==-1){
            initialGame();
        }
        //ask for steps
        steps();
    }
    //configure size of game by commnad line argument 
    else{
        //read in initial file
        Readfile();
        printf("Size of the game configured in commad line!\n");
        int j;
	    for (j=0;j<strlen(argv[1]);j++){
		    if (!isdigit(argv[1][j])){
			    printf("\nOnly numbers are allowed! Reconfigure and start again.\n");
			    exit(-1);
		    }
		    else{continue;}
	    }
        for (j=0;j<strlen(argv[2]);j++){
		    if (!isdigit(argv[2][j])){
			    printf("Only numbers are allowed! Reconfigure and start again.\n");
			    exit(-1);
		    }
		    else{continue;}
	    }
        //check whether the size is gthe same as defined in the file or not 
        if (Row==atoi(argv[1]) && Column==atoi(argv[2])){
            printf("Same size as last game!\n");
            //play the game

        }
        else{
            printf("Reopening a new game with given size...\n");
            Row=atoi(argv[1]);
            Column=atoi(argv[2]);
            initialGame();
        }
        //take the steps form the player
        while (steps()==-1){
            steps();
        }
    }    
    return 0;
}
