#ifndef MAP_H
#define MAP_H

#include "bomb.h"
#include "player.h"
#include "explosion.h"
#include "sprite.h"
#include "param.h"

typedef enum wallstate{BRITTLE, SOLID, EMPTY} wallstate_t;

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
    int map_coordx;
    int map_coordy;
    int width;
    int height;
    int sizeOfCell; // en pixels
     
} map_t;

int mapInit(map_t* map);
int mapDestruction(map_t* map);
int generateMap(float density, map_t* map);

int mapGetWidth(int* width, map_t* map);
int mapGetHeight(int* height, map_t* map);
int mapGetSizeOfCell(int*size, map_t* map);
int mapGetGrid(cell_t* grid, map_t* map);
int cellGetPlayer(player_t* player, cell_t* cell);
int cellGetBomb(bomb_t* bomb, cell_t* cell);
int cellGetExplosion(explosion_t* explosion, cell_t* cell);
int cellGetWall(wall_t* wall, cell_t* cell);

int mapSetWidth(int width, map_t* map);
int mapSetHeight(int height, map_t* map);
int mapSetGrid(cell_t* grid, map_t* map);
int cellSetPlayer(player_t* player, cell_t* cell);
int cellSetBomb(bomb_t* bomb, cell_t* cell);
int cellSetExplosion(explosion_t* explosion, cell_t* cell);
int cellSetWall(wall_t* wall, cell_t* cell);

#endif