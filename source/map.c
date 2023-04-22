#include "map.h"

int mapInit(map_t* map){
     map->grid = NULL;
     map->width = 0;
     map->height = 0;
}
int generateMap(map_t* map){
    
}

int getPlayer(player_t* player, cell_t* cell){
    player = cell->player;
}

int getBomb(bomb_t* bomb, cell_t* cell){
    bomb = cell->bomb;
}

int getExplosion(explosion_t* explosion, cell_t* cell){
    explosion = cell->explosion;
}

int getWall(wall_t* wall, cell_t* cell){
    wall = cell->wall;
}

int setPlayer(player_t* player, cell_t* cell){
    cell->player = player;
}

int setBomb(bomb_t* bomb, cell_t* cell){
    cell->bomb = bomb;
}

int setExplosion(explosion_t* explosion, cell_t* cell){
    cell->explosion = explosion;
}

int setWall(wall_t* wall, cell_t* cell){
    cell->wall = wall;
}