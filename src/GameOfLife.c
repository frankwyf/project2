#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>
#include "DataStructure.h"
#include "Check.h"
#include "NextGenre.h"
#include "GameWindow.h"

//ask whether the user want to decide the steps or not
int steps(){
    printf("Enter a number if you want to decide how many steps the game display (0 for infinite): ");
    char *step=(char *)malloc(sizeof(int) + sizeof(char));
    fgets(step,5,stdin);
    step[strlen(step)-1]='\0';
    int i;
    for (i=0;i<strlen(step);i++){
		if (!isdigit(step[i])){
			printf("\nInvalid Input! try again.\n");
			return -1;
		}
		else{continue;}
	}
    Step=atoi(step);
    //check the number is valid or not 
    if (Step<0){
        printf("\nInvalid Step number!\n");
		return -1;
    }
    if (Step==0){
        printf("The game will go infinite.\n");
        return Step;
    }
    else{
        printf("The Game of Life will evolute for %i generations.\n",Step);
        free(step);
        return Step;
    }
}

//read user input for size of the game
int map(){
    //two char pointers to store user input and check whether they are vaild or not
    char *row=(char *)malloc(sizeof(int) + sizeof(char));
    char *column=(char *)malloc(sizeof(int) + sizeof(char));
    //get user input and check if it is valid or not
    printf("Enter Rows of the Game (up to 1024):");
    fgets(row,5,stdin);
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
    if (Row>1024){
        printf("Over 1024 rows! Screen can't hold that much!\n");
        return 1;
    }
    //check the number is valid or not 
    if (Row<2){
        printf("\nInvalid Row number!\n");
		return 1;
    }
    printf("Enter columns of the Game (up to 1024):");
    fgets(column,42,stdin);
    column[strlen(column)-1]='\0';//get rid of the '\n' at the last of the input
	for (j=0;j<strlen(column);j++){
		if (!isdigit(column[j])){
			printf("\nOnly numbers are allowed!\n");
			return 1;
		}
		else{continue;}
	}
    Column=atoi(column);
    if (Column>1024){
        printf("Over 1024 columns! Screen can't hold that much!\n");
        return 1;
    }
    //check the number is valid or not 
    if (Column<2){
        printf("\nInvalid Row number!\n");
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
        printf("Reading in game file...\n");
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
        while (read!=NULL && temp[0]!='\0'){
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
            free(data);
        }
        int i,j;
        Game=(int **)malloc(sizeof(*Game)*Row);
        for (i=0;i<Row;i++){
            //read in the next line
            memset(temp, '\0', 1024);
            read = fgets(temp,sizeof(temp),game);
            temp[strlen(temp)-1]='\0';
            char *cell=strtok(temp,",");
            Game[i]=(int *)malloc(sizeof(**Game)*Column);
            //read in the data by row
            for (j=0;j<Column;j++){
                for (index=0;index<strlen(cell);index++){
                    if (!isdigit(cell[index])){
                        printf("\nInvalid cell found. Please configure the game by hand.\n");
		                return -1;
                    }
                }
                if (atoi(cell)!=1 && atoi(cell)!=0){
                    printf("\nInvalid cell found. Please configure the game by hand.\n");
		            return -1;
                }
                else{
                    Game[i][j]=atoi(cell);
                    cell=strtok(NULL,",");
                }
            }
            free(cell);
        }
        fclose(game);
        return 0;
    }
    else{
        //creat a file named "Game.txt"
        game=fopen("Game.txt","wb");
        printf("\nGame file lost!\nCreating a new one...\nManually configuration reqiured.\n\n");
        fclose(game);
        return -1;
    }
} 

//Create the initial game
void initialGame(){
    int i,j;
    //create a two dimensional array to be used as the Game borad
    Game=(int **)malloc(sizeof(*Game)*Row);
    for (i=0;i<Row;i++){
        Game[i]=(int *)malloc(sizeof(**Game)*Column);
        for (j=0;j<Column;j++){
            //initail state of the game with random 0s and 1 s
            Game[i][j]=rand()%2;
            printf("%d ",Game[i][j]);
        }
    printf("\n");
    }
}
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

//Generate the new generation
int Evolution(int **Game, int i, int j){
    int Neighbours = CheckUp(Game,i,j) + CheckDown(Game,i,j) 
                    + CheckLeft(Game,i,j) + CheckRight(Game,i,j)
                    + CheckUpRight(Game,i,j) + CheckUpLeft(Game,i,j)
                    + CheckDownLeft(Game,i,j) + CheckDownRight(Game,i,j);
    if (Game[i][j]==0){
        if (Neighbours==3){
            return 1;
        }
        else{
            return 0;
        }
    }
    if (Neighbours==2 || Neighbours==3){
        return 1;
    }
    else{
        return 0;
    }
}

//going through the whole map
void NextGen(int **map){
    int x,y;
    map=(int **)malloc(sizeof(*Game)*Row);
    for (x=0;x<Row;x++){
        map[x]=(int *)malloc(sizeof(**Game)*Column);
        for (y=0;y<Column;y++){
            //put the new generation into the map
            map[x][y]=Evolution(Game,x,y);
            printf("%d ",map[x][y]);
        }
        printf("\n");
    }
    //put the cells of the next generation back to Game to keep the game going 
    for (x=0;x<Row;x++){
        for (y=0;y<Column;y++){
            Game[x][y]=map[x][y];
        }
    }
    //make the evolution 2000 milliseconds pertime (windows:Sleep, linux:sleep)
    Sleep(1000);
}

//the function to print every step of the game
void ShowGen(){
    //play the game
    if (Step!=0){
        int move;
        for (move=0;move<Step;move++){
            printf("Step: %d\n",move+1);
            NextGen(NextGeneration);
            printf("\n-----------------------------\n\n");
            show(Game);
        }
    }
    else{
        printf("Infinite steps! Termiante the game when you want.\n");
        int life=1;
        bool quit = false;
        while (!quit) {
	        while (SDL_PollEvent(&e) != 0) {
                printf("Step: %d\n",life);
                NextGen(NextGeneration);
                life++;
                printf("\n-----------------------------\n\n");
                show(Game);
		        switch (e.type) {
                    //press any key to terminate the programme
		            case SDL_KEYDOWN:
			            quit = true;
			            break;
                    //use mouse to press exit button
		            case SDL_QUIT:
		            case SDL_MOUSEBUTTONDOWN:
			            quit = true;
			            break;
		        }
	        }
        }
    } 
}

void PrintMap(){
    //print the initial game
    int i,j;
    for (i=0;i<Row;i++){
        for (j=0;j<Column;j++){
            printf("%d ",Game[i][j]);
        }
        printf("\n");
    }
}

//write the result back
int WriteResult(FILE *game){
    game=fopen("Game.txt","w");
    //if the file is missing, crete a new one
    if (game==NULL){
        game=fopen("Game.txt","wb");
    }
    //write in the result
    fprintf(game,"%i,%i,%i\n\n",Row,Column,Step);
    int i,j;
    for (i=0;i<Row;i++){
        for (j=0;j<Column;j++){
            if (j!=Column-1){
                fprintf(game,"%i,",Game[i][j]);
            }
            else{
                fprintf(game,"%i\n",Game[i][j]);
            }
        }
    }
    fclose(game);
    if (ferror(game)){
        printf("Faild to stroe last game!\nData lost.\n");
        return -1;
    }
    else{
        printf("Data saved successfully! \nGood Bye!\n");
        return 0;
    }
}