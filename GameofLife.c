#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "DataStructure.h"

//ask whether the user want to decide the steps or not
int steps(){
    printf("Do you want to decide how many steps the game displays?\nEnter a number (up to 10 digits) if you want: ");
    char *step=(char *)malloc(sizeof(int)*10 + sizeof(char));
    fgets(step,42,stdin);
    step[strlen(step)-1]='\0';
    int i;
    for (i=0;i<strlen(step);i++){
		if (!isdigit(step[i])){
			printf("\nEvolution will continue!\nTerminate the Game when you want.\n\n");
            Step=0;
			return Step;
		}
		else{continue;}
	}
    Step=atoi(step);
    //check the number is valid or not 
    if (Step<0){
        printf("\nInvalid Step number!\n\n");
		return -1;
    }
    else{
        printf("The Game of Life will evolute for %i generations.\n",Step);
        return Step;
    }
}

//read user input for size of the game
int map(){
    steps();
    //two char pointers to store user input and check whether they are vaild or not
    char *row=(char *)malloc(sizeof(int)*10 + sizeof(char));
    char *column=(char *)malloc(sizeof(int)*10+sizeof(char));
    //get user input and check if it is valid or not
    printf("Enter Rows of the Game (up to 10 digits):");
    fgets(row,42,stdin);
    row[strlen(row)-1]='\0';//get rid of the '\n' at the last of the input
	int j;
	for (j=0;j<strlen(row);j++){
		if (!isdigit(row[j])){
			printf("\nOnly numbers are allowed!\n\n");
			return 1;
		}
		else{continue;}
	}
    Row=atoi(row);
    //check the number is valid or not 
    if (Row<1){
        printf("\nInvalid Row number!\n\n");
		return 1;
    }
    printf("Enter columns of the Game (up to 10 digits):");
    fgets(column,42,stdin);
    column[strlen(column)-1]='\0';//get rid of the '\n' at the last of the input
	for (j=0;j<strlen(row);j++){
		if (!isdigit(column[j])){
			printf("\nOnly numbers are allowed!\n");
			return 1;
		}
		else{continue;}
	}
    Column=atoi(column);
    //check the number is valid or not 
    if (Column<1){
        printf("\nInvalid Row number!\n\n");
		return 1;
    }
    //free the pointers
    free(row);
    free(column);
    return 0;
}

//read in Game file
int Readfile(FILE *game){
    game=fopen("Game.txt","r");
    if (game!=NULL){
        printf("\nReading in game file...\n\n");
        //read the file in by line
        char temp[1024];
        char *read=fgets(temp,sizeof(temp),game);
        if (read==NULL){
            printf("\nEmpty game file found. Please configure the game by hand.\n");
            return -1;
        }
        temp[strlen(temp)-1]='\0';
        int count=0;
        int len, index;
        while (read!=NULL){
            char *data=strtok(temp,",");
            while (data!=NULL){
                switch (count){
                //read in rows
                    case 0:
                        len=strlen(data);
	                        for (index=0;index<len;index++){
		                        if (!isdigit(data[index])){
			                        printf("\nBroken game file found. Please configure the game by hand.\n");
		                            return -1;
	                            }
		                        else{continue;}
	                        }
				        Row=atoi(data);
                        break;
                    //read in columns
                    case 1:
                        len=strlen(data);
	                        for (index=0;index<len;index++){
		                        if (!isdigit(data[index])){
			                        printf("\nBroken game file found. Please configure the game by hand.\n");
		                            return -1;
	                            }
		                        else{continue;}
	                        }
				        Column=atoi(data);
                        break;
                    //read in the step of the game
                    case 2:
                        len=strlen(data);
	                        for (index=0;index<len;index++){
		                        if (!isdigit(data[index])){
			                        printf("\nBroken game file found. Please configure the game by hand.\n");
		                            return -1;
	                            }
		                        else{continue;}
	                        }
				        Step=atoi(data);
                }
                count+=1;
                data=strtok(NULL,",");
            }
            //read in the next line
            memset(temp, '\0', 1024);
            read = fgets(temp,sizeof(temp),game);
            temp[strlen(temp)-1]='\0';
        }    
    }
    else{
        //creat a file named "Game.txt"
        game=fopen("Game.txt","wb");
        printf("\n Game file lost!\n Creating a new one...\nManually configuration reqiured.\n\n");
        return -1;
    }
} 

//Create the initial game
void initialGame(){
    int i,j;
    //create a two dimensional array to be used as the Game borad
    Game=(int **)malloc(sizeof(int)*Row);
    for (i=0;i<Row;i++){
        Game[i]=(int *)malloc(sizeof(int)*Column);
        for (j=0;j<Column;j++){
            //initail state of the game,random 0s and 1 s
            Game[i][j]=rand()%2;
            printf("%d,",Game[i][j]);
        }
    printf("\n");
    }
}