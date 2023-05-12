#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "sprite.h"

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

    inputs_t* inputs;
    SDL_Texture* texture_player;
    SDL_Rect hitbox;
}player_t;

//init:
int playerInit(player_t* player);
int playerDestruction(player_t* player);

//coord:
int getCoordx(int* x_coord, player_t* player);
int getCoordy(int* y_coord, player_t* player);
int setCoordx(player_t* player,int x);
int setCoordy(player_t* player,int y);

//health:
int getHealth(player_t* player);
int setHealth(player_t* player, int new_health);
int healthSubstract(player_t* player, int substract);
int healthAdd(player_t* player, int add);

//case:
int getCasex(player_t* player);
int getCasey(player_t* player);
int player_rect_actualise(player_t* player);

//tests:
int playerPushUp(player_t* player);
int playerPushDown(player_t* player);
int playerPushLeft(player_t* player);
int playerPushRight(player_t* player);
int playerPushBomb(player_t* player);
#endif