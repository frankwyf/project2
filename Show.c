#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "GameWindow.h"

void InitWindow(){
    SDL_Window *window = NULL;
    //check the window can be initialized or not 
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }
    //clean up when exit
    atexit(SDL_Quit);
    //crete the window and set attributes like title,colour and characters
    SDL_CreateWindowAndRenderer(1000,600,0,&window,&renderer);
    SDL_SetWindowTitle(window, "Conway's Game of Life");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
}