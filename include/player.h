#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct player{
    int x_coord;
    int y_coord;
    int health;
    int up;
    int down;
    int left;
    int right;
    SDL_Texture* texture_player;
    SDL_Rect hitbox;
}player_t;

//init

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

#endif