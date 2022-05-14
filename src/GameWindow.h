#ifndef GameWindow_GUARD__H 
#define GameWindow_GUARD__H
#include <SDL2/SDL.h>
/*
  This head file is used to store the functions and variables 
  used in SDL windows and renders
*/
//SDL window pointer
SDL_Window *window;
//SDL surface pointer
SDL_Surface *surface;
//SDL event
SDL_Event e;
//SDL render
SDL_Renderer *render;
//the number of cells that are alive
int alive;

//the function to initialize a window for display
int InitWindow();
//the function to show next generation in SDL mode
void show(int **Game);
//the function to intialize a window for click
void click();
//the function to display message on the window
void title(int round);
#endif