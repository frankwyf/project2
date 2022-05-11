#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
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
    int x,y;
    for (y = 0; y < Row; y++) {
		for (x = 0; x < Column; x++ ) {
            //get the state of life for next stage
			int state = Game[y][x];
            //decide to fill a black or green block
			int rgb = (state>0) ? 0xff : 0x00;
            //fill the window with filled rectangles
			SDL_Rect square = {
				.x = x * (600/Column)+0.1,
				.y = y * (600/Row)+0.1,
				.w = 600/Column-0.1,
				.h = 600/Row-0.1,
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

