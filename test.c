#include "map.h"
#include "renderer.h"
#include "event.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main()
{
    int size=20;
    int sprite_size=40;

    screen_t screen;
    initScreen(&screen);
    window_t window;
    initWindow(&screen,&window);

    map_t map;
    mapInit(&map);
    generateMap(1/2, &map);

    SDL_Rect rect_grid[size*size];
    grid_init(&screen,&window,rect_grid,NULL,size,sprite_size);

    presentScene(&window);
    SDL_Delay(3000);
    
    mapDestruction(&map);
    return 0;
}