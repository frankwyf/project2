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
	//draw lines between rectangles
    render=SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render,255,0,0,255);
    int i;
    for (i=0;i<600;i+=600/Row){
        //draw horizontal line first, the vertical lines
        SDL_RenderDrawLine(render,0,i,0,i);
        SDL_RenderDrawLine(render,i,0,i,0);
    }
    SDL_RenderPresent(render);
	SDL_ShowWindow(window);
    return 0;
}

void show(int **Game){
    int x,y;
    for (y = 0; y < Row; y++) {
		for (x = 0; x < Column; x++ ) {
            //get the state of life for next stage
			int state = Game[y][x];
            //decide to fill a black or white block
			int rgb = (state>0) ? 0x00 : 0xff;
            //fill the window with filled rectangles
			SDL_Rect square = {
				.x = x * (600/Column),
				.y = y * (600/Row),
				.w = 600/Column,
				.h = 600/Row,
			};
            //fill the window with filled blocks
			SDL_FillRect(
				surface,
				&square,
				SDL_MapRGB(surface->format, rgb, rgb, rgb)
			);
		}
	}
	SDL_UpdateWindowSurface(window);
    SDL_Delay(300);
}

