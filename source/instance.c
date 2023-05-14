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

int playerInit(player_t* player, map_t* map, screen_t* screen){

    int screen_width;
    screenGetWidth(&screen_width, screen);

    int screen_height;
    screenGetHeight(&screen_height, screen);

    int map_width;
    mapGetWidth(&map_width,map);

    int map_height;
    mapGetHeight(&map_height, map);

    int sizeOfCell;
    mapGetSizeOfCell(&sizeOfCell, map);

    int x_fake_origin= screen_width/2-sizeOfCell*map_width/2;
    int y_fake_origin= screen_height/2-sizeOfCell*map_height/2;

    setCoordx(player,x_fake_origin);
    setCoordy(player,y_fake_origin);
    setHealth(player,3);
    player->speed=4;

    inputs_t* inputs = malloc(sizeof(inputs_t));
    player->x_strength = 1;
    player->y_strength = 1;
    player->frame = FRAME_RATE;
    player->inputs = inputs;
    player->inputs->up=0;
    player->inputs->down=0;
    player->inputs->left=0;
    player->inputs->right=0;
    player->hitbox.h=60;
    player->hitbox.w=60;
    player->hitbox.x=(player->x_coord - player->hitbox.w/2);
    player->hitbox.y=(player->y_coord - player->hitbox.h/2);
    player ->texture_player=NULL;
    return 0;
};