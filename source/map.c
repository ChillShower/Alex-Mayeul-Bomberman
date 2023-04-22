#include "map.h"
#include <time.h>
#include <stdlib.h>

int mapInit(map_t* map){
     map->grid = NULL;
     map->width = 0;
     map->height = 0;
     return 0;
}

int mapDestruction(map_t* map)
{
    free(map);
    return 0;
}

int mapSetWidth(int width, map_t* map)
{
    map->width = width;
    return 0;
}

int mapSetHeight(int height, map_t* map)
{
    map->height = height;
    return 0;
}

int mapGetWidth(int* width, map_t* map)
{
    *width = map->width;
    return 0;
}

int mapGetHeight(int* height, map_t* map)
{
    *height = map->height;
    return 0;
}

int generateRandomMap(int density, map_t* map){
    
    srand(time(NULL)); 

    //Assignation d'un nouveau tableau;
    cell_t* grid = malloc(sizeof(cell_t) * map->height * map->width);
    map->grid = grid;

    for(int i = 0; i<map->height; ++i)
    {
        for(int j = 0; j<map->width; ++j)
        {

            /*
            REGLES: Les 4 coins sont vides et laissent la place
            au joueur de placer des bombes sans se suicider.
            Exemple (coin haut gauche)
            ______
            |    * * 
            |  * * * 
            |* * * *
            
            */
            int x_coord = j;
            int y_coord = i;
            player_t* player = NULL;
            bomb_t* bomb = NULL;
            explosion_t* explosion = NULL;
            sprite_t* sprite = NULL;
            wall_t* wall = NULL;

            // Si on ne situe pas dans un coin:
            if ( (i != 0 && i!= 1 && i != map->height-1 && i != map->height-2) || (j != 0 && j != map->width - 1))
            {
                 
                int r = (float) rand() / RAND_MAX;

                if( r <= density)
                {
                    wallstate_t wallstate = BRITTLE;
                    sprite = NULL;
                    
                    wall_t wall_object = {wallstate, sprite};
                    wall = &wall_object;
                }

            }
            else if ( (i % 2 != 0) && (j % 2 != 0) ){
                wallstate_t wallstate = SOLID;
                sprite = NULL;

                wall_t wall_object = {wallstate, sprite};
                wall = &wall_object;
            }
            // Si on se situe dans un coin:
            else
            {
                sprite = NULL;
                wall = NULL;

            }

            // ATTRIBUTION DES PARAMETRES A LA CELLULE:
            map->grid[j + i*map->width].x_coord = x_coord;
            map->grid[j + i*map->width].y_coord = y_coord;
            map->grid[j + i*map->width].wall = wall;
            map->grid[j + i*map->width].player = player;
            map->grid[j + i*map->width].bomb = bomb;
            map->grid[j + i*map->width].explosion = explosion;
            
        }
    }

    return 0;
}

int getPlayer(player_t* player, cell_t* cell){
    player = cell->player;
    return 0;
}

int getBomb(bomb_t* bomb, cell_t* cell){
    bomb = cell->bomb;
    return 0;
}

int getExplosion(explosion_t* explosion, cell_t* cell){
    explosion = cell->explosion;
    return 0;
}

int getWall(wall_t* wall, cell_t* cell){
    wall = cell->wall;
    return 0;
}

int setPlayer(player_t* player, cell_t* cell){
    cell->player = player;
    return 0;
}

int setBomb(bomb_t* bomb, cell_t* cell){
    cell->bomb = bomb;
    return 0;
}

int setExplosion(explosion_t* explosion, cell_t* cell){
    cell->explosion = explosion;
    return 0;
}

int setWall(wall_t* wall, cell_t* cell){
    cell->wall = wall;
    return 0;
}