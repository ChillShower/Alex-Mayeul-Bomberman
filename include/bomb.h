<<<<<<< HEAD

=======
#ifndef BOMB_H
#define BOMB_H

#include "sprite.h"
>>>>>>> 481d0bccaa26d81fece76e98b307ac010e068ed4

typedef struct bomb{
    int frame; // quand frame arrive à 0 -> explosion
    sprite_t* sprite;

} bomb_t;

int bombInit(bomb_t* bomb);
int isExploded(bomb_t* bomb);

#endif