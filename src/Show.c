#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "GameWindow.h"
#include "DataStructure.h"

void InitWindow(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Init Failed\n");
        exit(EXIT_FAILURE);
    }
    SDL_Window *win = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("Window creation Failed\n");
        exit(EXIT_FAILURE);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Renderer creation Failed\n");
        exit(EXIT_FAILURE);
    }
}
void envolve(int **Game,SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int i,j;
    for (i=0;i<Row;i++){
        for (j=0;j<Column;j++){
            if (Game[i][j]==1){
                SDL_Rect point = {i, j, 1, 1};
                SDL_RenderFillRect(renderer, &point);
            }
            else{continue;}
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}