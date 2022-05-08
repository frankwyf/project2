#ifndef GameWindow_GUARD__H 
#define GameWindow_GUARD__H
#include <SDL2/SDL.h>
/*
  This head file is used to store the functions and variables 
  used in SDL windows and renders
*/
SDL_Renderer *renderer;
//the function to initialize a window for display
void InitWindow();
//the function to show next generation in SDL mode
void envolve(int **Game,SDL_Renderer *renderer);

#endif