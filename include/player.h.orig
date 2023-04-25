#ifndef PLAYER_H
#define PLAYER_H
<<<<<<< HEAD
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
=======
>>>>>>> 481d0bccaa26d81fece76e98b307ac010e068ed4

#include <string.h>
#include "sprite.h"

typedef struct player{
    int x_coord;
    int y_coord;
    int health;
<<<<<<< HEAD
    int up;
    int down;
    int left;
    int right;
    SDL_Texture* texture_player;
    SDL_Rect hitbox;
=======
    char* name;
    sprite_t sprite;
>>>>>>> 481d0bccaa26d81fece76e98b307ac010e068ed4
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

int  healthSubstract(player_t* player, int substract);

int healthAdd(player_t* player, int add);

//case
int getCasex(player_t* player);

int getCasey(player_t* player);
int playerinit(player_t* player);
int player_rect_actualise(player_t* player);

<<<<<<< HEAD
=======

>>>>>>> 481d0bccaa26d81fece76e98b307ac010e068ed4
#endif