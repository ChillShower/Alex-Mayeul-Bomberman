#include "bomb.h"
#include "player.h"
#include "explosion.h"

typedef struct map{

    cell_t* grid;
    int width;
    int height;
    
} map_t;

typedef enum mur {incassable,cassable,air} wallstate_t;

typedef struct cell{
    int x_coord;
    int y_coord;

    enum mur wall_state; 
    player_t* player;
    bomb_t* bomb;//chaque valeur représentera la frame de l'animation ca sera plus simple a animé et 0 veut dire pas de bomb
    explosion_t* explosion;

} cell_t;

int mapInit(map_t* map);
int generateMap(map_t* map);

int getPlayer(cell_t* cell);
int getBomb(cell_t* cell);
int getExplosion(cell_t* cell);
wallstate_t getWallState(cell_t* cell);

int setPlayer(cell_t* cell);
int setBomb(cell_t* cell);
int setExplosion(cell_t* cell);
wallstate_t setWallState(cell_t* cell);