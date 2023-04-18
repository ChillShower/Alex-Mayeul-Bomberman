#include "../include/player.h"

float getCoordx(player_t* player){
    return player->x_coord;
};

float getCoordy(player_t* player){
   return player->y_coord; 
};

int setCoordx(player_t* player,float x){
    player->x_coord=x;
    return 0;
};

int setCoordy(player_t* player,float y){
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
    return (int)(player->x_coord);
};

int getCasey(player_t* player){
    return (int)(player->y_coord);
}
