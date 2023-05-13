#ifndef BOMB_H
#define BOMB_H

#include "param.h"

#define BOMB_DURATION  3
#define BOMB_FRAME (FRAME_RATE*BOMB_DURATION)

#include <sprite.h>

typedef struct bomb{
    int frame; // quand frame arrive à 0 -> explosion
    //sprite_t* sprite;
    int state;

} bomb_t;

int bombInit(bomb_t** bomb);
int isExploded(bomb_t* bomb);
int bombActualise(bomb_t* bomb);
int bombDestruction(bomb_t** bomb);

#endif