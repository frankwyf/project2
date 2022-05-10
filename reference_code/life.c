/*
 * Conway's Game of Life
 *
 * Press any key to re-initialise :)
 * Click the window to exit.
 *
 * gcc -std=c99 -lsdl2 -Wall -Werror -Wpedantic -Wno-unused-function -o life life.c
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

//width and height
#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 240

//game map
bool canvas[SCREEN_HEIGHT][SCREEN_WIDTH];

// These are the possible initialisation functions for the canvas
static void init_random(void);
static void init_glider_gun(void);

// Set this to one of the functions above
#define INIT_FUNC init_glider_gun

static bool next_state(int x, int y)
{
	int on = 0;

	// Vertical neighbors
	if (y > 0 && canvas[y - 1][x])
		on += 1;
	if ((y < SCREEN_HEIGHT - 1) && canvas[y + 1][x])
		on += 1;

	// Horizontal neighbors
	if (x > 0 && canvas[y][x - 1])
		on += 1;
	if ((x < SCREEN_WIDTH - 1) && canvas[y][x + 1])
		on += 1;

	// Diagonally adjacent neighbors
	if (x > 0 && y > 0 && canvas[y - 1][x - 1])
		on += 1;
	if ((x < SCREEN_WIDTH - 1) && (y < SCREEN_HEIGHT - 1) && canvas[y + 1][x + 1])
		on += 1;
	if (x > 0 && (y < SCREEN_HEIGHT - 1) && canvas[y + 1][x - 1])
		on += 1;
	if ((x < SCREEN_WIDTH - 1) && y > 0 && canvas[y - 1][x + 1])
		on += 1;

	// Conway's Game of Life rules
	if (canvas[y][x]) {
		if (on == 1)
			return false;
		else if (on == 4)
			return false;
		else if (on == 2 || on == 3)
			return true;
	}
	else {
		if (on == 3)
			return true;
	}

	return false;
}

//初始状态
static void init_random(void)
{
	// Randomise the starting state, so the rules actually do something...
	for (size_t x = 0; x < SCREEN_WIDTH; x += 1) {
		for (size_t y = 0; y < SCREEN_HEIGHT; y += 1) {
			canvas[y][x] = rand() % 2 == 0 ? true : false;
		}
	}
}

static void init_glider_gun(void)
{
	// Gosper Glider Gun
	//living cells
	canvas[5][1] = true;
	canvas[5][2] = true;
	canvas[6][1] = true;
	canvas[6][2] = true;
	canvas[5][11] = true;
	canvas[6][11] = true;
	canvas[7][11] = true;
	canvas[4][12] = true;
	canvas[3][13] = true;
	canvas[3][14] = true;
	canvas[8][12] = true;
	canvas[9][13] = true;
	canvas[9][14] = true;
	canvas[6][15] = true;
	canvas[4][16] = true;
	canvas[5][17] = true;
	canvas[6][17] = true;
	canvas[7][17] = true;
	canvas[6][18] = true;
	canvas[8][16] = true;
	canvas[3][21] = true;
	canvas[4][21] = true;
	canvas[5][21] = true;
	canvas[3][22] = true;
	canvas[4][22] = true;
	canvas[5][22] = true;
	canvas[2][23] = true;
	canvas[6][23] = true;
	canvas[1][25] = true;
	canvas[2][25] = true;
	canvas[6][25] = true;
	canvas[7][25] = true;
	canvas[3][35] = true;
	canvas[4][35] = true;
	canvas[3][36] = true;
	canvas[4][36] = true;
}
#undef main
int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialise SDL: %s\n", SDL_GetError());
		goto cleanup_error;
	}

	SDL_Window *window = SDL_CreateWindow(
		"Game of Life",
		100,
		100,
		SCREEN_WIDTH * 2,
		SCREEN_HEIGHT * 2,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		printf("Unable to create window: %s\n", SDL_GetError());
		goto cleanup_error;
	}

	SDL_Surface *surface = SDL_GetWindowSurface(window);

	SDL_Event e;
	bool quit = false;
	bool next_canvas[SCREEN_HEIGHT][SCREEN_WIDTH];

    //intial game
	INIT_FUNC();

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_KEYDOWN:
				memset(canvas, 0, sizeof(canvas));
				INIT_FUNC();
				break;

			case SDL_QUIT:
			case SDL_MOUSEBUTTONDOWN:
				quit = true;
				break;
			}
		}

		memset(next_canvas, 0, sizeof(next_canvas));

		for (int y = 0; y < SCREEN_HEIGHT; y += 1) {
			for (int x = 0; x < SCREEN_WIDTH; x += 1) {
				bool onoff = next_state(x, y);//get the state of life for next stage
				int rgb = onoff ? 0x00 : 0xff;
				next_canvas[y][x] = onoff;

				SDL_Rect square = {
					.x = x * 2,
					.y = y * 2,
					.w = 2,
					.h = 2,
				};

				SDL_FillRect(
					surface,
					&square,
					SDL_MapRGB(surface->format, rgb, rgb, rgb)
				);
			}
		}
        //cover the map   
		memcpy(&canvas, &next_canvas, sizeof(canvas));

		SDL_UpdateWindowSurface(window);
		SDL_Delay(100);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

cleanup_error:
	SDL_Quit();
	return 1;
}

    