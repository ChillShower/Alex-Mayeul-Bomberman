#include "player.h"


int getCoordx(int* x_coord, player_t* player){
    *x_coord = player->x_coord;
    return 0;
};

int getCoordy(int* y_coord, player_t* player){
    *y_coord = player->y_coord;
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