#include "instance.h"

int mapInstanciation(map_t* map, int width, int height, screen_t* screen)
{
    map->width = width;
    map->height = height;

    int screenWidth;
    screenGetWidth(&screenWidth, screen);

    map->sizeOfCell = (int) screenWidth / width;

    return 0;
}