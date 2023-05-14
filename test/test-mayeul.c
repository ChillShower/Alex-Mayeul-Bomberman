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

    player_t player;
    playerInit(&player, &map, &screen);
    player_set_texture(&player,&window,"resources/animations/characters/bomberman/bas_1.png");

    while (1)
    {
        prepareScene(&window);
        doInput(&player);     
        
		if (playerPushUp(&player) && !(smthgIsUp(&player, &map, &screen)))
		{

            int x;
	        int y;

	        getPlayerGridCoordinates(&player, &screen, &map,&x, &y);
            printf("%d, %d \n", x, y);

            printf("%d, %d\n", player.x_coord, player.y_coord);
            printf("frame:%d\n", player.frame);
        
			playerGoUp(&player, &window);
		}

		if (playerPushDown(&player) && !(smthgIsDown(&player, &map, &screen)))
		{
            
			playerGoDown(&player, &window);
		}

		if (playerPushLeft(&player) && !(smthgIsLeft(&player, &map, &screen)))
		{
            
			playerGoLeft(&player, &window);
		}

		if (playerPushRight(&player) && !(smthgIsRight(&player, &map, &screen)))
		{
            
			playerGoRight(&player, &window);
		}

        if (playerPushBomb(&player))
        {
            playerPutBomb(&player, &map,&window);
        }

        player_rect_actualise(&player);
        gridActualisation(&player,&map);
        grid_renderer(rectArray, &map, &window);
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);
        draw_player(&player, &window);
        SDL_RenderPresent( window.cur_renderer);
        
        SDL_Delay(10);

    }
    
    mapDestruction(&map);

    return EXIT_SUCCESS;
}