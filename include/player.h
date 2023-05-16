#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include"param.h"
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
    int x_grid;
    int y_grid;
    int speed;
    int health;
    int death; // frame de mort
    int immuned; //frame de clignotement : prend la valeur par défaut, se décremmente, lorsque la valeur atteint 0, le joueur n'est plus immunisé
    int x_strength;
    int y_strength;
    inputs_t* inputs;
    SDL_Texture* texture_player;
    int frame; // frame de déplacement
    SDL_Rect hitbox;
}player_t;

//init:
int playerDestruction(player_t* player);

//coord
int getCoordx(int* x_coord, player_t* player);

int getCoordy(int* y_coord, player_t* player);

int getGridy(int* y_grid, player_t* player);

int getGridx(int* x_grid, player_t* player);

int setCoordx(player_t* player,int x);

int setCoordy(player_t* player,int y);

int setGridx(player_t* player);

int setGridy(player_t* player);
//health
int getHealth(player_t* player);

int setHealth(player_t* player, int new_health);

int healthSubstract(player_t* player, int substract);

int healthAdd(player_t* player, int add);
int setPlayerX_strength(int x, player_t* player);
int setPlayerY_strength(int y, player_t* player);
int getPlayerX_strength(int* x, player_t* player);
int getPlayerY_strength(int* x, player_t* player);
int player_rect_actualise(player_t* player);

// Actions:

int playerPushUp(player_t* player);
int playerPushDown(player_t* player);
int playerPushLeft(player_t* player);
int playerPushRight(player_t* player);
int playerPushBomb(player_t* player);
int playerResetInputs(player_t* player);

int playerIsDead(player_t* player);
#endif