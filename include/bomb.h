#ifndef BOMB_H
#define BOMB_H

#include "param.h"
#include "player.h"

#define BOMB_DURATION  5
#define BOMB_FRAME (FRAME_RATE*BOMB_DURATION)

#include <sprite.h>

typedef struct bomb{
    int frame; // quand frame arrive à 0 -> explosion
    int x_strength;
    int y_strength;

} bomb_t;

int bombInit(bomb_t** bomb, player_t* player);
int isExploded(bomb_t* bomb);
int bombActualise(bomb_t* bomb);
int bombDestruction(bomb_t** bomb);
int setBombX_strength(int x, bomb_t* bomb);
int setBombY_strength(int y, bomb_t* bomb);
int getBombX_strength(int* x, bomb_t* bomb);
int getBombY_strength(int* x, bomb_t* bomb);
#endif