#ifndef GameWindow_GUARD__H 
#define GameWindow_GUARD__H
/*
  This head file is used to store the functions and variables 
  used in SDL windows and renders
*/

/*
  The follwing are SDL variables that are used
*/
//SDL render
SDL_Renderer* renderer = NULL;

/*
  The follwing are functions perform the task of SDL diplays
*/
//the function to initialize a window for display
void InitWindow();


#endif