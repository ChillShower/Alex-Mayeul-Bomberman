#ifndef MAP_H
#define MAP_H

#include "bomb.h"
#include "player.h"
#include "explosion.h"
#include "sprite.h"

typedef enum wallstate{BRITTLE, SOLID} wallstate_t;

typedef struct wall{

    wallstate_t wallstate;
    sprite_t* sprite;

} wall_t;

typedef struct cell{
    int x_coord;
    int y_coord;

    wall_t* wall;
    player_t* player;
    bomb_t* bomb;//chaque valeur représentera la frame de l'animation ca sera plus simple a animé et 0 veut dire pas de bomb
    explosion_t* explosion;

} cell_t;

typedef struct map{

    cell_t* grid;
    int width;
    int height;
    
} map_t;

int mapInit(map_t* map);
int mapDestruction(map_t* map);
int generateMap(map_t* map);

int getPlayer(player_t* player, cell_t* cell);
int getBomb(bomb_t* bomb, cell_t* cell);
int getExplosion(explosion_t* explosion, cell_t* cell);
int getWall(wall_t* wall, cell_t* cell);

int setPlayer(player_t* player, cell_t* cell);
int setBomb(bomb_t* bomb, cell_t* cell);
int setExplosion(explosion_t* explosion, cell_t* cell);
int setWall(wall_t* wall, cell_t* cell);

#endif