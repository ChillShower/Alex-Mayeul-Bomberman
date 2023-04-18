#include "../include/renderer.h"
#include "../include/player.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int main()
{   
    int size=20;
    int sprite_size=40;
    screen_t screen;
    initScreen(&screen);
    window_t window;
    initWindow(&screen,&window);
    SDL_Rect rect_grid[size*size];
    SDL_Event e; bool quit = false; 
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
    grid_renderer_first(rect_grid,&window,NULL,size,sprite_size);
    while( quit == false ){ 
        
        while( SDL_PollEvent( &e ) ){ 
            if( e.type == SDL_QUIT ) quit = true; 

            grid_renderer(rect_grid,&window,grid,size,sprite_size);

        } 
    }
    destroyWindow(&window);

}