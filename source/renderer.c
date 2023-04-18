#include "../include/renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

int initScreen(screen_t* screen){
    screen->width=1920;
    screen->height=1080;
    return 0;

}

int initWindow(screen_t* screen,window_t* window){
    window->cur_window=NULL;
    window->screenSurface=NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    else
    {
        window->cur_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen->width, screen->height, SDL_WINDOW_FULLSCREEN_DESKTOP );
        if( window->cur_window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }

    };
    window->cur_renderer=SDL_CreateRenderer(window->cur_window,-1,SDL_RENDERER_ACCELERATED);
        if( window->cur_renderer == NULL )
        {
            printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }
    return 0;
};

int destroyWindow(window_t* window){
    
    //Destroy window
    SDL_DestroyWindow( window->cur_window );
    SDL_DestroyRenderer(window ->cur_renderer);
    //Quit SDL subsystems
    SDL_Quit();
    return 0;
};

int initSDL_Rect(SDL_Rect * pos, int x, int y, unsigned int w, unsigned int h){
	if(pos == NULL) return 1;
	pos->x = x;      //abscisse
	pos->y = y;     //ordonnées
	pos->w = w;    //longueur
	pos->h = h;   //largeur
    return 0;
};


int grid_init(screen_t* screen,window_t* window,SDL_Rect* rect_array, int* grille, int grid_width,int size_rect){
    int x_fake_origin=screen->width/2-size_rect*grid_width/2;
    int y_fake_origin=screen->height/2-size_rect*grid_width/2;
    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_width;j++){
            initSDL_Rect(&rect_array[i+j*grid_width],x_fake_origin+i*size_rect,y_fake_origin+j*size_rect ,size_rect,size_rect);   
        };
    };
    return 0;

}

int grid_renderer_first(SDL_Rect* array_rect, window_t* window, int* grid, int grid_width,int size_rect){
    SDL_SetRenderDrawColor(window->cur_renderer,255,255,255,255);
    SDL_RenderDrawRects(window->cur_renderer,array_rect,grid_width*grid_width);
    SDL_RenderPresent( window->cur_renderer);
    return 0;
};
int grid_renderer(SDL_Rect* array_rect, window_t* window, int* grid, int grid_width,int size_rect){
    SDL_Surface* tmp= SDL_LoadBMP("../assets/text_road.bmp");
    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_width;j++){
        if (grid[i+j*grid_width]==0){
            
            SDL_SetRenderDrawColor(window->cur_renderer,255,255,255,255);
        };
        if (grid[i+j*grid_width]==1){
            SDL_SetRenderDrawColor(window->cur_renderer,0,0,255,255);
        };
        if (grid[i+j*grid_width]==2){
            SDL_SetRenderDrawColor(window->cur_renderer,255,0,0,255);
        };
            SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
        };
    };
    SDL_FreeSurface(tmp);
    SDL_RenderPresent( window->cur_renderer);
    
    return 0;
};