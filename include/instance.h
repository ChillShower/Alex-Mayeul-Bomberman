#ifndef INSTANCE_H
#define INSTANCE_H

#include "bomb.h"
#include "explosion.h"
#include "instance.h"
#include "map.h"
#include "player.h"
#include "renderer.h"
#include "terrain.h"

typedef struct listPlayers{
    player_t* list;
    int numberOfPlayers; // nombre de joueurs actuellement dans la session
    int maxNumber; // nombre maximum de joueurs
} listPlayers_t;

typedef struct instance{
    listPlayers_t listPlayers;
    map_t* map;
} instance_t;

int listPlayersInit(listPlayers_t* list);   


#endif