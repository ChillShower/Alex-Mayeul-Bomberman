#include "explosion.h"

int explosionInit(explosion_t** explosion){
    explosion_t* temp_explosion= malloc(sizeof(explosion_t));
    temp_explosion->frame = EXPLOSION_FRAME;
    
    *explosion=temp_explosion;
    return 0;
}
int explosionIsFinished(explosion_t* explosion){
    return explosion->frame==0;
}
int explosionActualise(explosion_t* explosion){
    if (explosion->frame>0){
    explosion->frame =explosion->frame -1;
    };

    return 0;  
}
int explosionDestruction(explosion_t** explosion){
    free(*explosion);
    return 0;
}