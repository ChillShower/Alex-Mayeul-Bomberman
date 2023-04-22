#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

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
int initSDL_Rect(SDL_Rect * pos, int x, int y, unsigned int w, unsigned int h);
int grid_init(screen_t* ecran,window_t* window,SDL_Rect* rect_array, int* grille, int width,int size_rect);
int grid_renderer_first(SDL_Rect* array_rect,window_t* window, int* grille, int width,int size_rect);
int grid_renderer(SDL_Rect* array_rect,window_t* window, int* grille, int width,int size_rect);

#endif