#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GameWindow.h"
#include "DataStructure.h"


//function to create the window
int InitWindow(){
    //initial SDL libraries 
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Unable to initialise SDL: %s\n", SDL_GetError());
		SDL_Quit();
	    return -1;
	}
    //create the SDL window
	window = SDL_CreateWindow(
		"Conway's Game of Life",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,  //position of the window
		600, //width of the window
		600,  //height of the window
		SDL_WINDOW_SHOWN //widow is visible
	);
    //check the window is created or not
    if (window == NULL) {
		printf("Unable to create window: %s\n", SDL_GetError());
		SDL_Quit();
	    return -1;
	}
    //bind the surface and window together
    surface = SDL_GetWindowSurface(window);
	//set the background for the window
	SDL_Rect background = {
		.x=0,
		.y=0,
		.w=600,
		.h=600,
	};
	SDL_FillRect(
		surface,
		&background,
		SDL_MapRGB(surface->format, 123, 123, 122)
	);
	SDL_UpdateWindowSurface(window);
    return 0;
}

void show(int **Game){
	//initialize number of living cells every time function is called
	alive=0;
    int x,y;
    for (y = 0; y < Row; y++) {
		for (x = 0; x < Column; x++ ) {
			//count how many alive cells are there
			alive=alive+Game[y][x];
            //get the state of life for next stage
			int state = Game[y][x];
            //decide to fill a black or green block
			int rgb = (state>0) ? 0xff : 0x00;
            //fill the window with filled rectangles
			SDL_Rect square = {
				.x = x * (600/Column)+0.01,
				.y = y * (600/Row)+0.01,
				.w = (600/Column)-0.01,
				.h = (600/Row)-0.01,
			};
            //fill the window with filled blocks
			SDL_FillRect(
				surface,
				&square,
				SDL_MapRGB(surface->format, 0, rgb, 0)
			);
		}
	}
	SDL_UpdateWindowSurface(window);
    SDL_Delay(Delay);
}

//the function to intialize a window for click
void click(){
	printf("Click to change the sate of the cells!\nPress enter when finished, Esc to exit the game.\n");
	InitWindow();
	show(Game);
	int i,j,x,y;
	//set for click events
	bool setting = true;
	while (setting){
		while (SDL_PollEvent(&e) != 0){
			switch (e.type) {
				case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x,&y);
				   for (i=0;i<Row;i++){
					   for (j=0;j<Column;j++){
						   if (j*(600/Column-0.1)<x && x<(j+1)*(600/Column-0.1) && i*(600/Row-0.1)<y && y<(i+1)*(600/Row-0.1)){
							   Game[i][j] = (Game[i][j]>0) ? 0:1 ;
							   show(Game);
							   //break the outter for loop
							   i=Row;
							   break;
						    }
							else{continue;}
					   }
				    }
				break;
				case SDL_KEYDOWN:
				    switch(e.key.keysym.sym){
						case SDLK_RETURN:
				            printf("Setting over!\n");
					        setting=false;
					        SDL_DestroyWindow(window);
	                        SDL_Quit();
					    break;
						case SDLK_ESCAPE:
						    printf("-------------------\nTerminated at initial state.\nSaving is ignored.\n");
				            setting=false;
							exit(1);
				            break;
					}
				break;	    
			}
		}
	}
	WriteResult(game);
}

//the function to display message on the window
void title(int round){
	char num[100]=" ";
	int dead=Row*Column-alive;
}