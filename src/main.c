#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "DataStructure.h"
#include "NextGenre.h"
#include "GameWindow.h"

//undefine the key word "main" in SDL macro definition
#undef main

int main(int argc, char **argv){
    title(-2);
    time_t t;
    struct tm * lt;
    time (&t);//get Unix time
    lt = localtime (&t);//turn into time struct
    printf("\n%d/%d/%d %d:%d:%d   Welcome to Conway's Game of Life!\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    //configure the size of the game by user input
    if (argc<3){
        //read the initial file in
        if (Readfile(game)==-1){
            //if file read in failed, start a new game
            int size=map();
            while (size==1){
                size=map();
            }
            printf("Initialzing new game with size: %i X %i...\n",Row,Column);
            initialGame();
            int late=delay();
            while (late==-1){
                late=delay();
            }
        }
        else{
            printf("\n----------------------------------------------------------\n\n");
            Ask();
            printf("Last game stopped at step %i.\n",Step);
        }
    }
    //configure size of game by command line arguments 
    else{
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
        if (Readfile(game)==-1){
            //if file read in failed, start a new game
            Row=atoi(argv[1]);
            Column=atoi(argv[2]);
            printf("Initial file lost...\nNew game with size: %i X %i...\n",Row,Column);
            initialGame();
        }
        else{
            if (Row==atoi(argv[1]) && Column==atoi(argv[2])){
                printf("Same size as last game!\n");
            }
            else{
                Row=atoi(argv[1]);
                Column=atoi(argv[2]);
                printf("Reopening a new game with given size %i X %i...\n",Row,Column);
                initialGame();
            }
        }
        //ask player for delay and steps
        int late=delay();
        while (late==-1){
            late=delay();
        }
    }
    int round=steps();
    while (round==-1){
        round=steps();
    }
    printf("Step 0:\n");
    PrintMap();
    //give tips
    title(-1);
    //init SDL window
    InitWindow();
    //show first stage
    show(Game);
    //show every genertaion of the game
    ShowGen();
    //destory windows
    SDL_DestroyWindow(text);
    SDL_DestroyWindow(window);
	SDL_Quit();
    //offer replay mode for finite steps
    replay();
    title(-3);
    //write the result 
    if (WriteResult(game)==-1){
        time (&t);//get Unix time
        lt = localtime (&t);//turn into time struct
        printf("Exit without saving at: %d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    }
    else{
        time (&t);//get Unix time
        lt = localtime (&t);//turn into time struct
        printf("Game saved at: %d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    } 
    return 0;
}