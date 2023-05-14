#ifndef INSTANCE_H
#define INSTANCE_H

#include "bomb.h"
#include "explosion.h"
#include "map.h"
#include "player.h"
#include "renderer.h"
#include "event.h"

typedef struct listPlayers{
    player_t* list;
    int numberOfPlayers; // nombre de joueurs actuellement dans la session
    int maxNumber; // nombre maximum de joueurs
} listPlayers_t;

typedef struct instance{
    listPlayers_t listPlayers;
    map_t* map;
    screen_t* screen;
    window_t* window;
} instance_t;

int listPlayersInit(listPlayers_t* list);   
int mapInstanciation(map_t* map, int width, int height, screen_t* screen);
#endif