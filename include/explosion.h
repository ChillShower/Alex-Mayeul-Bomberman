#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "param.h"
#include <stdlib.h>

#define EXPLOSION_DURATION  2
#define EXPLOSION_FRAME (FRAME_RATE*EXPLOSION_DURATION)

typedef struct explosion{
    int frame;
    //int x_strength;
    //int y_strength;
} explosion_t;

int explosionInit(explosion_t** explosion);
int explosionIsFinished(explosion_t* explosion);
int explosionActualise(explosion_t* explosion);
int explosionDestruction(explosion_t** explosion);
#endif