#include "bomb.h"
#include "param.h"

#include <stdlib.h>

int bombInit(bomb_t** bomb, player_t* player){
    bomb_t* temp_bomb= malloc(sizeof(bomb_t));
    temp_bomb->frame = BOMB_FRAME;
    temp_bomb->x_strength=player->x_strength;
    temp_bomb->y_strength=player->y_strength;
    *bomb=temp_bomb;
    return 0;
}
int isExploded(bomb_t* bomb){
    return bomb->frame==0;
}

/* Actualisation des données de la bombe à chaque tour */
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
int setBombX_strength(int x, bomb_t* bomb){
    bomb->x_strength=x;
    return 0;
}
int setBombY_strength(int y, bomb_t* bomb){
    bomb->y_strength=y;
    return 0;
}
int getBombX_strength(int* x, bomb_t* bomb){
    *x = bomb->x_strength;
    return 0;
}
int getBombY_strength(int* y, bomb_t* bomb){
    *y=bomb->y_strength;
    return 0;
}