#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "DataStructure.h"
#include "NextGenre.h"


int main(int argc, char **argv){
    time_t t;
    struct tm * lt;
    time (&t);//get Unix time
    lt = localtime (&t);//turn into time struct
    printf("%d/%d/%d %d:%d:%d\nWelcome to Conway's Game of Life!\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    //confogure the size of the game by user input
    if (argc<3){
        //read the initial file in
        if (Readfile(game)==0){
            //ask the user whether to change the size of the game or not
            printf("\nLast game is %i rows and %i columns\nDo you want to change (enter 'y' if you do)?",Row,Column);
            char Option=getchar();
            //eat the \n at the end of the input
            getchar(); 
            if (Option=='y'){
                //wait untile user input is valid
                while (map()==1){
                    map();
                }
                //create the initial map
                printf("Initialzing new game with size: %i X %i...\nStep 0:\n",Row,Column);
                initialGame();
            }
            else{
                printf("\nGame continue with size %i X %i.\nStep 0:\n",Row,Column);
                //print the initial game
                int i,j;
                for (i=0;i<Row;i++){
                    for (j=0;j<Column;j++){
                        printf("%d,",Game[i][j]);
                    }
                    printf("\n");
                }
                printf("Still want to change size? Restart the game.\n\n");
            }
        }
        //if file read in failed, start a new game
        else if (Readfile(game)==-1){
            initialGame();
        }
        //ask for steps
        printf("Last game stopped at step %i.\n",Step);
        while (steps()==-1){
            steps();
        }
        //play the game
        if (Step!=0){
            int move;
            for (move=0;move<Step;move++){
                printf("Step: %d\n",move+1);
                NextGen(NextGeneration);
                printf("\n");
            }
        }
        else{
            printf("Infinite steps! Termiante the game when you want.\n");
            int life=1;
            while (1){
                printf("Step: %d\n",life);
                NextGen(NextGeneration);
                life++;
                printf("\n");
            }
        }
        //write the result 
        if (WriteResult(game)==-1){
           printf("Exit without saving at: %d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
        }
        else{
            printf("Game saved at: %d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
        }  
    }
    //configure size of game by commnad line argument 
    else{
        //read in initial file
        Readfile(game);
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
        //play the game
        if (Step!=0){
            int move;
            for (move=0;move<Step;move++){
                printf("Step: %d\n",move+1);
                NextGen(NextGeneration);
                printf("\n");
            }
        }
        else{
            printf("Infinite steps! Termiante the game when you want.\n");
            int life=1;
            while (1){
                printf("Step: %d\n",life);
                NextGen(NextGeneration);
                life++;
                printf("\n");
            }
        } 
        //write the result 
        if (WriteResult(game)==-1){
           printf("Exit without saving at:%d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
        }
        else{
            printf("Game saved at:%d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
        }
    }   
    return 0;
}
