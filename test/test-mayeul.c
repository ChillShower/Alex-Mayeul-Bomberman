#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "instance.h"

int main( int argc, char* args[])
{
    screen_t screen;
    initScreen(&screen);

    window_t window;
    initWindow(&screen, &window);

    SDL_Rect rectArray[DEFAULT_MAP_WIDTH*DEFAULT_MAP_HEIGHT];
    grid_init(&screen, rectArray, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, DEFAULT_SIZE_OF_CELL);

    map_t map;
    mapInit(&map);
    generateMap(0.85, &map);

    SDL_Texture* texturesList[30];
    texturesListInit(texturesList, &window);

    player_t player;
    playerInit(&player, &map, &screen);
    player_set_texture(&player,texturesList[0]);
    grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);

    while (!(caseOfGameOver(&player)))
    {
        prepareScene(&window);
        if(!(playerIsDead(&player)))
        {
            doInput(&player); 
        }
            
		if (playerPushUp(&player) && !(smthgIsUp(&player, &map, &screen)))
		{
			playerGoUp(&player, &window, texturesList);
		}

		if (playerPushDown(&player) && !(smthgIsDown(&player, &map, &screen)))
		{
            
			playerGoDown(&player, &window, texturesList);
		}

		if (playerPushLeft(&player) && !(smthgIsLeft(&player, &map, &screen)))
		{
            
			playerGoLeft(&player, &window, texturesList);
		}

		if (playerPushRight(&player) && !(smthgIsRight(&player, &map, &screen)))
		{
            
			playerGoRight(&player, &window, texturesList);
		}

        if (playerPushBomb(&player))
        {
            playerPutBomb(&player, &map,&window);
        }
        gridActualisation(&player,&map,&screen,&window, texturesList);

        grid_renderer(rectArray, &map, &window, texturesList);
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);

        draw_player(&player, &window);

        SDL_RenderPresent( window.cur_renderer);
        SDL_Delay(10);
        

    }

    SDL_RenderCopy(window.cur_renderer, texturesList[26], NULL,NULL);
    SDL_RenderPresent( window.cur_renderer);
	SDL_Delay(5000);
    mapDestruction(&map);

    return EXIT_SUCCESS;
}