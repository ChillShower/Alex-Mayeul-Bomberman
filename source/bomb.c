#include "bomb.h"
#include "param.h"
#include <stdlib.h>

int bombInit(bomb_t** bomb){
    bomb_t* temp_bomb= malloc(sizeof(bomb_t));
    temp_bomb->frame = BOMB_FRAME;
    temp_bomb->state = 0;
    *bomb=temp_bomb;
    return 0;
}
int isExploded(bomb_t* bomb){
    return bomb->frame==0;
}
int bombActualise(bomb_t* bomb){
    if (bomb->frame>0){
    bomb->frame =bomb->frame -1;
    };

    return 0;
}
int bombDestruction(bomb_t** bomb){
    free(*bomb);
    return 0;
}