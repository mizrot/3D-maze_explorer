#include "../headers/headers.h"

/**
 * drawWalls - draw walls of the maze
 * @renderer: the renderer to draw the wall
 * @player: the player in the maze
 * @map: the map of the maze
 *
 */
static inline double clamp(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
void drawWalls(SDL_Renderer *renderer, Player player,
		int map[MAP_HEIGHT][MAP_WIDTH])
{
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);/*sky blue for ceiling */
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);/*Ground color */
	SDL_Rect groundRect = {
		0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2
	};
	SDL_RenderFillRect(renderer, &groundRect);
	/*TODO: Implement raycasting to draw walls based on player's position */
	int screenHeight = 480;
	int screenWidth = 640;
	double FOV = 60 * 3.14 / 180;/* 60 degree field of view*/
	double rayAngleStep = FOV / screenWidth;

	double prevDistance = -1.;
	int prevdrawStart = -1;
	int prevdrawEnd = -1;

	/* Loop through each vertical slice of the screen */
	for (int x = 0; x < screenWidth; x++)
	{
		bool endwall = false;
		double rayAngle = (player.angle - (FOV / 2)) + (x * rayAngleStep);

		/* Ray direction */
		double rayDirX = cos(rayAngle);
		double rayDirY = sin(rayAngle);

		/* Player's current position */
		double rayX = player.x;
		double rayY = player.y;

		/* Increment distance until we hit a wall*/
		double distanceToWall = 0;
		bool hit = false;

		while (!hit)
		{
			rayX += rayDirX * 0.01;
			rayY += rayDirY * 0.01;
			int mapX = (int)rayX;
			int mapY = (int)rayY;

			/*Check if the ray has hit a wall*/
			if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT)
			{
				if (map[mapY][mapX] == 1)
				{
					hit = true;
				}
				else if(map[mapY][mapX] == 2)
				{
					endwall = true;
					hit = true;
				}
			}
		}
		/* Calculate distance from the player to the wall*/
		distanceToWall = sqrt((rayX - player.x) * (rayX - player.x)
				+ (rayY - player.y) * (rayY - player.y));
		/* Calculate height of the wall based on distance */
		int lineHeight = (int)(screenHeight / distanceToWall);
		/*Calculate starting and ending positon of the wall slice*/
		int drawStart = -lineHeight / 2 + screenHeight / 2;

		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;

		if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
		
		if (prevDistance == -1.0 && prevdrawStart == -1 && prevdrawEnd == -1){
			prevDistance = distanceToWall;
			prevdrawStart = drawStart;
			prevdrawEnd = drawEnd;

		} 
		/* Set wall color*/
		if (endwall){
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		} else {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}  
		/* Draw the vertical slice (the wall) on the screen */
		SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
		if (fabs(prevDistance - distanceToWall) > 0.5){
			if (prevDistance - distanceToWall > 0.0){
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
			} else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawLine(renderer, x, prevdrawStart, x, prevdrawEnd);
		}
		}
		prevDistance = distanceToWall;
		prevdrawStart = drawStart;
		prevdrawEnd = drawEnd;
	}
	/* Render the frame (this part should already be in your loop)*/
	SDL_RenderPresent(renderer);
}
