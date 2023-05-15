#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "map.h"


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
int initWindow(screen_t* screen, window_t* window);
int destroyWindow(window_t* window);

int screenGetWidth(int* width, screen_t* screen);   
int screenGetHeight(int* height, screen_t* screen);
int screenSetWidth(int width, screen_t* screen);
int screenSetHeight(int height, screen_t* screen);

//initialisation rendu:
int initSDL_Rect(SDL_Rect * pos, int x, int y, unsigned int w, unsigned int h);
SDL_Texture* SDL_texture_init(SDL_Texture* texture, window_t* window, char* filename);
int grid_init(screen_t* ecran,SDL_Rect* rect_array,int width, int height, int size_rect);

// rendu:
int grid_renderer_first(SDL_Rect* array_rect,window_t* window, int grid_width, int grid_height);
int grid_renderer(SDL_Rect* array_rect, map_t* map, window_t* window, SDL_Texture** texturesList);
SDL_Texture* loadTexture(SDL_Texture * texture,char *filename, window_t* window);
int draw_on_rectangle(SDL_Texture * texture,SDL_Rect rectangle,window_t* window);
SDL_Texture* SDL_texture_init(SDL_Texture* texture, window_t* window, char* filename);
int player_set_texture(player_t* player,SDL_Texture* texture);
int draw_player(player_t* player, window_t* window);

int getPlayerGridCoordinates(player_t* player, screen_t* screen, map_t* map, int* x, int* y);
int IsPlayerInMap(player_t* player, screen_t* screen, map_t* map);
int test_rectangle(window_t* window);
#endif