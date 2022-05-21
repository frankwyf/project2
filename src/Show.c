#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GameWindow.h"
#include "DataStructure.h"

//structures to get time and display in SDL window
time_t t;
struct tm * lt;

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
	move=1;
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
	title(move);
	SDL_Delay(Delay);
	TTF_Quit();
	SDL_DestroyWindow(text); 
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(introText);
	SDL_FreeSurface(intro);
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
				            printf("\n**********************\n    Setting over!\n**********************\n\n");
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
int title(int round){
	//open fount library
	if (TTF_Init()==-1){
		printf("Unable to open font library!%s\n",TTF_GetError());
		return -1;
	}
	//set font and size
	TTF_Font *font=TTF_OpenFont("arial.ttf",16);
	if (!font){
		printf("TTF_OpenFont: Open simsun.ttf %s\n", TTF_GetError());
		return -1; 
	}
	//deal with every step
	if (round>-1){
		if (SDL_Init(SDL_INIT_EVERYTHING)<0){
    	    printf("Unable to initialise SDL: %s\n", SDL_GetError());
		    SDL_Quit();
	        return -1;
	    }
	    text=SDL_CreateWindow(
	        "Result of game",
		    1000,
		    0,
		    200,
		    200,
		    SDL_WINDOW_SHOWN
	    );
		time (&t);//get Unix time
        lt=localtime (&t);//turn into time struct
		int deaded=Row*Column-alive;
	    char message[100]=" ";
	    snprintf(message,sizeof(message),"Alive: %d.  Dead: %d. Step: %d. %d/%d/%d %d:%d:%d",alive,deaded,round-1,lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
		SDL_Rect livecells={
		    .x=50,
		    .y=50,
		    .w=100,
		    .h=100,
	    };
		render=SDL_CreateRenderer(text,-1,0);
        //rendering the message
		SDL_Color livemessage={173,255,47,0};
		intro=TTF_RenderText_Solid_Wrapped(font,message,livemessage,100);
		introText=SDL_CreateTextureFromSurface(render, intro);
		//clean the render and copy the txture to surface
	    SDL_RenderClear(render);
	    SDL_RenderCopy(render,introText,NULL,&livecells);
	    SDL_RenderPresent(render);
		SDL_Delay(100);
		return 0;
	}
	//initila a new window to show tips
	if (SDL_Init(SDL_INIT_EVERYTHING)<0){
    	printf("Unable to initialise SDL: %s\n", SDL_GetError());
		SDL_Quit();
	    return -1;
	}
	text=SDL_CreateWindow(
	    "Tips for the game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		300,
		300,
		SDL_WINDOW_SHOWN
	);
	if (text == NULL) {
	 	printf("Unable to create window: %s\n", SDL_GetError());
	 	SDL_Quit();
	    return -1;
	}
	//create the render
	render=SDL_CreateRenderer(text,-1,0);
	//show tips when playing the game
	if (round==-1){
		SDL_Rect tips={
		    .x=30,
		    .y=100,
		    .w=250,
		    .h=85,
	    };   
	    //set color and create surface
	    SDL_Color color={255,255,0,0};
	    intro = TTF_RenderUTF8_Blended_Wrapped(font,"Press 'Backspace' to re-intialize. Press 'Enter' to reset the game.    Press 'Esc' to quit.                         Any key to continue...",color,250);
	    introText= SDL_CreateTextureFromSurface(render, intro);
	    //clean the render and copy the txture to surface
	    SDL_RenderClear(render);
	    SDL_RenderCopy(render,introText,NULL,&tips);
	    SDL_RenderPresent(render);
		bool Quit=false;
		while (!Quit){
			while (SDL_PollEvent(&event) != 0) {
		        switch (event.type) {
					case SDL_KEYDOWN:
					Quit=true;
					break;
				}
			}
		}
	}
	//display welcome message
	if (round==-2){
	    //the area to show the message
	    SDL_Rect welcome={
		    .x=25,
		    .y=100,
		    .w=250,
		    .h=50,
	    };   
	    //set color and create surface
	    SDL_Color color={0,255,0,0};
	    intro = TTF_RenderUTF8_Blended_Wrapped(font,"Welcome to conway's game of life!         Game will start soon ...",color,250);
	    introText= SDL_CreateTextureFromSurface(render, intro);
	    //clean the render and copy the txture to surface
	    SDL_RenderClear(render);
	    SDL_RenderCopy(render,introText,NULL,&welcome);
	    SDL_RenderPresent(render);
	    bool Quit=false;
		while (!Quit){
			while (SDL_PollEvent(&event) != 0) {
				SDL_Delay(200);
				Quit=true;
			}
		}
	}
	//dsiplay goodbye message
	if (round==-3){
		char message[200]=" ";
	    snprintf(message,sizeof(message),"End of Game! Good Bye.    %d/%d/%d %d:%d:%d",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
	    //the area to show the message
	    SDL_Rect goodbye={
		    .x=50,
		    .y=100,
		    .w=250,
		    .h=50,
	    };   
	    //set color and create surface
	    SDL_Color color={230,230,250,0};
	    intro = TTF_RenderUTF8_Solid_Wrapped(font,message,color,250);
	    introText= SDL_CreateTextureFromSurface(render, intro);
	    //clean the render and copy the txture to surface
	    SDL_RenderClear(render);
	    SDL_RenderCopy(render,introText,NULL,&goodbye);
	    SDL_RenderPresent(render);
	    bool Quit=false;
		while (!Quit){
			while (SDL_PollEvent(&event) != 0) {
				SDL_Delay(200);
				Quit=true;
			}
		}
	}
	//display tips for players when stopped during the game for replay
	if (round==-4){
		char message[200]=" ";
	    snprintf(message,sizeof(message),"Replay will start soon...    %d/%d/%d %d:%d:%d",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
	    //the area to show the message
	    SDL_Rect replaying={
		    .x=50,
		    .y=100,
		    .w=250,
		    .h=50,
	    };   
	    //set color and create surface
	    SDL_Color color={0,255,255,0};
	    intro = TTF_RenderUTF8_Solid_Wrapped(font,message,color,250);
	    introText= SDL_CreateTextureFromSurface(render, intro);
	    //clean the render and copy the txture to surface
	    SDL_RenderClear(render);
	    SDL_RenderCopy(render,introText,NULL,&replaying);
	    SDL_RenderPresent(render);
		SDL_Delay(1000);
	    SDL_DestroyWindow(text); 
    	SDL_DestroyRenderer(render);
	    SDL_DestroyTexture(introText);
	    SDL_FreeSurface(intro);
		return 0;
	}
	//display tips for players when stopped during the game for re-initialize
	if (round==-5){
		char message[200]=" ";
	    snprintf(message,sizeof(message),"Re-establish the game by click on the boxes. Press enter when finised.            %d/%d/%d %d:%d:%d",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
	    //the area to show the message
	    SDL_Rect reesatblish={
		    .x=30,
		    .y=100,
		    .w=250,
		    .h=80,
	    };   
	    //set color and create surface
	    SDL_Color color={0,255,255,0};
	    intro = TTF_RenderUTF8_Solid_Wrapped(font,message,color,250);
	    introText= SDL_CreateTextureFromSurface(render, intro);
	    //clean the render and copy the txture to surface
	    SDL_RenderClear(render);
	    SDL_RenderCopy(render,introText,NULL,&reesatblish);
	    SDL_RenderPresent(render);
	    SDL_Delay(2000);
	    SDL_DestroyWindow(text); 
    	SDL_DestroyRenderer(render);
	    SDL_DestroyTexture(introText);
	    SDL_FreeSurface(intro);
		return 0;
	}
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(text); 
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(introText);
	SDL_FreeSurface(intro);
	SDL_Quit();  
	return 0;
}


