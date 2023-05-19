#include "player.h"


int getCoordx(int* x_coord, player_t* player){
    *x_coord = player->x_coord;
    return 0;
};

int getCoordy(int* y_coord, player_t* player){
    *y_coord = player->y_coord;
    return 0;
};

int getGridy(int* y_grid, player_t* player){
    *y_grid=player->y_grid;
    return 0;
};

int getGridx(int* x_grid, player_t* player){
    
    *x_grid = player->x_grid;
    return 0;
};

int setCoordx(player_t* player,int x){
    player->x_coord=x;
    return 0;
};

int setCoordy(player_t* player,int y){
    player->y_coord=y;
    return 0;
};

int setGridx(player_t* player){
    int x_grid_coord= player->x_coord-(DEFAULT_SCREEN_WIDTH/2-DEFAULT_SIZE_OF_CELL*DEFAULT_MAP_WIDTH/2);
    player->x_grid= (int)((double)x_grid_coord/(double)DEFAULT_SIZE_OF_CELL);
    return 0;
};

int setGridy(player_t* player){
    int y_grid_coord= player->y_coord-(DEFAULT_SCREEN_HEIGHT/2-DEFAULT_SIZE_OF_CELL*DEFAULT_MAP_HEIGHT/2);
    player->y_grid = (int)((double)y_grid_coord/(double)DEFAULT_SIZE_OF_CELL);
    return 0;
};

int getHealth(player_t* player){
    return player->health;
};

int setHealth(player_t* player, int new_health){
    player->health=new_health;
    return 0;
};

int healthSubstract(player_t* player, int substract){
    player->health=player->health-substract;
    return 0;
};

int healthAdd(player_t* player, int add){
    player->health=player->health+add;
    return 0;
};

int setPlayerX_strength(int x, player_t* player){
    player->x_strength=x;
    return 0;
}
int setPlayerY_strength(int y, player_t* player){
    player->y_strength=y;
    return 0;
}
int getPlayerX_strength(int* x, player_t* player){
    *x = player->x_strength;
    return 0;
}
int getPlayerY_strength(int* y, player_t* player){
    *y=player->y_strength;
    return 0;
}

int getCasex(player_t* player){
    return (player->x_coord);
};

int getCasey(player_t* player){
    return (player->y_coord);
}

int playerDestruction(player_t* player)
{
    free(player->inputs);
    free(player->texture_player);
    return 0;
}

int player_rect_actualise(player_t* player){
    player->hitbox.x=(player->x_coord - player->hitbox.w/2);
    player->hitbox.y=(player->y_coord - player->hitbox.h/2);
    player->idBox.x=(player->x_coord - player->hitbox.w/2 + player->idBox.h/4);
    player->idBox.y= (player->y_coord - 3*player->hitbox.h/2 + player->idBox.w/2);
    return 0;
};

int playerPushUp(player_t* player)
{
    return player->inputs->up;
}

int playerPushDown(player_t* player)
{
    return player->inputs->down;
}

int playerPushLeft(player_t* player)
{
    return player->inputs->left;
}

int playerPushRight(player_t* player)
{
    return player->inputs->right;
}

int playerPushBomb(player_t* player)
{
    return player->inputs->space;
}

int playerResetInputs(player_t* player)
{
    player->inputs->up = 0;
    player->inputs->down = 0;
    player->inputs->left = 0;
    player->inputs->right = 0;
    player->inputs->space = 0;
    return 0;
}

int playerIsDead(player_t* player)
{
    return player->health == 0;
}