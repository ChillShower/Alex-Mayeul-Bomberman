#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "renderer.h"
#include "event.h"

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

    player_t player;
    playerInit(&player);
    player_set_texture(&player,&window,"assets/player.png");

    while (1)
    {
        prepareScene(&window);
        
        doInput(&player);     
        
		if (playerPushUp(&player))
		{
			playerGoUp(&player);
		}

		if (playerPushDown(&player))
		{
			playerGoDown(&player);
		}

		if (playerPushLeft(&player))
		{
			playerGoLeft(&player);
		}

		if (playerPushRight(&player))
		{
			playerGoRight(&player);
		}

        if (playerPushBomb(&player))
        {
            playerPutBomb(&player, &map);
        }

        player_rect_actualise(&player);

        grid_renderer(rectArray, &map, &window);
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);
        draw_player(&player, &window);
        SDL_RenderPresent( window.cur_renderer);
        
        SDL_Delay(10);

    }
    
    mapDestruction(&map);

    return EXIT_SUCCESS;
}