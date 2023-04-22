#include "../include/renderer.h"
#include "../include/player.h"
#include "../include/event.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> 
#include <assert.h>

int main()
{   
    /*création et initialisation fenêtre*/
    int size=20;
    int sprite_size=40;
    screen_t screen;
    initScreen(&screen);
    window_t window;
    initWindow(&screen,&window);
    player_t player;
    
    playerinit(&player);
    player_set_texture(&player,&window,"assets/player.png");
    /*création temporaire de l'arène */
    SDL_Rect rect_grid[size*size];
    //SDL_Event e; bool quit = false; 
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
    //SDL_Texture *texture = SDL_CreateTexture(window.cur_renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,40,40);
    
    /*initialisation texture*/
    SDL_Texture* texture_block;
    texture_block=SDL_texture_init(NULL,&window,"assets/text1.png");
    SDL_SetRenderTarget(window.cur_renderer,texture_block);
    grid_renderer_first(rect_grid,&window,NULL,size);
    //atexit(cleanup);
    while(1==1){ 
        prepareScene(&window);
        
        doInput(&player);     
           
		if (player.up)
		{
			player.y_coord-= 4;
		}

		if (player.down)
		{
			player.y_coord += 4;
		}

		if (player.left)
		{
			player.x_coord -= 4;
		}

		if (player.right)
		{
			player.x_coord += 4;
		}
            
        player_rect_actualise(&player);
            

        grid_renderer(rect_grid,texture_block,&window,grid,size);
        draw_player(&player,&window);

		presentScene(&window);
        
    };
    destroyWindow(&window);
    return 0;

}