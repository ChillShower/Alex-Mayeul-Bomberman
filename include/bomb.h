#include "sprite.h"

typedef struct bomb{
    int frame; // quand frame arrive à 0 -> explosion
    sprite_t* sprite;

} bomb_t;

int bombInit(bomb_t* bomb);
int isExploded(bomb_t* bomb);