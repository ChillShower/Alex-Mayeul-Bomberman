#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "player.h"
#include <map.h>


typedef struct screen{
    int width; 
    int height;
} screen_t;

typedef struct window{
    SDL_Window* cur_window; 
    SDL_Renderer* cur_renderer;
    SDL_Surface* screenSurface;
}window_t;

//rendu d'un tableau en grille
int initScreen(screen_t* screen);
int initWindow(screen_t* ecran, window_t* window);
int destroyWindow(window_t* window);

int screenGetWidth(int* width, screen_t* screen);
int screenGetHeight(int* height, screen_t* screen);
int screenSetWidth(int width, screen_t* screen);
int screenSetHeight(int height, screen_t* screen);

int initSDL_Rect(SDL_Rect * pos, int x, int y, unsigned int w, unsigned int h);
SDL_Texture* SDL_texture_init(SDL_Texture* texture, window_t* window, char* filename);
int grid_init(screen_t* ecran,window_t* window,SDL_Rect* rect_array, int* grille, int width,int size_rect);

int grid_renderer_first(SDL_Rect* array_rect,window_t* window, int* grille, int width);
int grid_renderer(SDL_Rect* array_rect,map_t* map, window_t* window, int* grid, int grid_width);
SDL_Texture* loadTexture(SDL_Texture * texture,char *filename, window_t* window);
int draw_on_rectangle(SDL_Texture * texture,SDL_Rect rectangle,window_t* window);

int player_set_texture(player_t* player,window_t* window,char* filename);
int draw_player(player_t* player, window_t* window);

#endif