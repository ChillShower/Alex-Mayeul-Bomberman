#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include "sprite.h"
#include "map.h"

typedef struct inputs{
    int up;
    int down;
    int left;
    int right;
    int space;
} inputs_t;

typedef struct player{
    int x_coord;
    int y_coord;
    int speed;
    int health;
/*
    int up;
    int down;
    int left;
    int right;
*/
    inputs_t* inputs;
    SDL_Texture* texture_player;
    SDL_Rect hitbox;
}player_t;

//init
int playerInit(player_t* player);

//coord
int getCoordx(player_t* player);
int getCoordy(player_t* player);
int setCoordx(player_t* player,int x);
int setCoordy(player_t* player,int y);

//health
int getHealth(player_t* player);
int setHealth(player_t* player, int new_health);
int healthSubstract(player_t* player, int substract);
int healthAdd(player_t* player, int add);

//case
int getCasex(player_t* player);
int getCasey(player_t* player);
int playerinit(player_t* player);
int player_rect_actualise(player_t* player);

// Actions:

int playerGoRight(player_t* player);
int playerGoLeft(player_t* player);
int playerGoUp(player_t* player);
int playerGoDown(player_t* player);
int playerPutBomb(player_t* player, map_t* map);

#endif