//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL.h>
#include "renderer.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
//#include <assert.h>
//#include "map.h"

int main( int argc, char* args[])
{
    
    /*création et initialisation fenêtre*/
    //int size=20;
    //int sprite_size=40;
    screen_t screen;
    initScreen(&screen);
    window_t window;
    initWindow(&screen,&window);
    player_t player;
    
    SDL_Rect* rect_array = NULL;
    grid_init(&screen, &window, rect_array, 30, 5);
    grid_renderer_first(rect_array, &window, 30);
    

    free(rect_array);
    /*
    map_t map;
    mapInit(&map);
    generateMap(1/2 , &map);

    playerInit(&player);
    player_set_texture(&player,&window,"assets/player.png");
    
    SDL_Rect rect_grid[size*size];
    
    int grid[size*size];
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
        grid[i+j*size]=0;
        }
        }
    grid[0]=1;
    grid[size*size-1]=2;
    printf("%d",grid[0]);
    grid_init(&screen,&window,rect_grid,NULL,size,sprite_size);

    SDL_Texture* texture_block;
    texture_block=SDL_texture_init(NULL,&window,"assets/text1.png");
    SDL_SetRenderTarget(window.cur_renderer,texture_block);

    grid_renderer(rect_grid,&map,&window);
    SDL_Delay(4000);


    while(1==1){ 
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
            
        player_rect_actualise(&player);
            

        grid_renderer(rect_grid,&map,&window);
        draw_player(&player,&window);

		presentScene(&window);
        
    };
    */
    playerDestruction(&player);
    //mapDestruction(&map);
    destroyWindow(&window);
    return 0;

}