#include "map.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int mapInit(map_t* map){
    map->grid = malloc(DEFAULT_MAP_WIDTH * DEFAULT_MAP_HEIGHT * sizeof(cell_t));
    map->map_coordx = DEFAULT_SCREEN_WIDTH/2-DEFAULT_SIZE_OF_CELL*DEFAULT_MAP_WIDTH/2;
    map->map_coordy = DEFAULT_SCREEN_HEIGHT/2-DEFAULT_SIZE_OF_CELL*DEFAULT_MAP_HEIGHT/2;
    map->width = DEFAULT_MAP_WIDTH;
    map->height = DEFAULT_MAP_HEIGHT;
    map->sizeOfCell = DEFAULT_SIZE_OF_CELL;
    return 0;
}

int mapDestruction(map_t* map)
{
    free(map->grid);
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

int mapGetSizeOfCell(int* size, map_t* map)
{
    *size = map->sizeOfCell;
    return 0;
}

int mapGetGrid(cell_t* grid, map_t* map){
    grid = map->grid;
    return 0;
}

int mapSetGrid(cell_t* grid, map_t* map){
    map->grid = grid;
    return 0;
}
int generateMap(float density, map_t* map){
    srand(time(NULL)); 

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
            wall_t* wall = NULL;
            
            // Si on se situe dans un coin
            if( (i == 0 || i == 1 || i == map->height -1 || i == map->height - 2) && ( j == 0 || j == map->width-1))
            {
                wall = malloc(sizeof(wall_t));
                *wall = (wall_t) {EMPTY, NULL};
            }
            // Les blocs de ligne et colonne impaires sont incassables (la map doit être de taille impaire)
            else if ( (i % 2 == 1) && (j % 2 == 1) ){
                wall = malloc(sizeof(wall_t));
                *wall = (wall_t) {SOLID, NULL};
            }

            else
            {
                float r = ((float) rand() / (float) RAND_MAX);

                if( r <= density)
                {
                    wall = malloc(sizeof(wall_t));
                    *wall = (wall_t) {BRITTLE, NULL};
                }

                else
                {
                    wall = malloc(sizeof(wall_t));
                    *wall = (wall_t) {EMPTY, NULL};

                }

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
    //printf("la");
    return 0;
}

int cellGetPlayer(player_t* player, cell_t* cell){
    *player = *cell->player;
    return 0;
}

int cellGetBomb(bomb_t* bomb, cell_t* cell){
    *bomb = *cell->bomb;
    return 0;
}

int cellGetExplosion(explosion_t* explosion, cell_t* cell){
    *explosion = *cell->explosion;
    return 0;
}

int cellGetWall(wall_t* wall, cell_t* cell){
    *wall = *cell->wall;
    return 0;
}

int cellSetPlayer(player_t* player, cell_t* cell){
    cell->player = player;
    return 0;
}

int cellSetBomb(bomb_t* bomb, cell_t* cell){
    cell->bomb = bomb;
    return 0;
}

int cellSetExplosion(explosion_t* explosion, cell_t* cell){
    cell->explosion = explosion;
    return 0;
}

int cellSetWall(wall_t* wall, cell_t* cell){
    cell->wall = wall;
    return 0;
}