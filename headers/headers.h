#ifndef HEADERS_H
#define HEADERS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
/*define a 2D map for walls, etc. */
#define MAP_WIDTH 40
#define MAP_HEIGHT 40
extern int map[MAP_HEIGHT][MAP_WIDTH];
/*Structure for the player */
typedef struct {
    /* Player's position*/
    float x, y;
    /* Player's direction*/
    float angle;
} Player;

/*Functions prototypes */
void initSDL(SDL_Window **window, SDL_Renderer **renderer);
void cleanupSDL(SDL_Window *window, SDL_Renderer *renderer);
void drawWalls(SDL_Renderer *renderer, Player player, int map[MAP_HEIGHT][MAP_WIDTH]);
void initSDL(SDL_Window **window, SDL_Renderer **renderer);
#endif /*HEADERS_H*/
