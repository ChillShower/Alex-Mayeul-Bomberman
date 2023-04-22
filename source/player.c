#include "../include/player.h"

int getCoordx(player_t* player){
    return player->x_coord;
};

int getCoordy(player_t* player){
   return player->y_coord; 
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
int playerinit(player_t* player){
    setCoordx(player,100);
    setCoordy(player,200);
    setHealth(player,3);
    player->up=0;
    player->down=0;
    player->left=0;
    player->right=0;
    player->hitbox.x=player->x_coord;
    player->hitbox.y=player->y_coord;
    player->hitbox.h=40;
    player->hitbox.w=40;
    player ->texture_player=NULL;
    return 0;
};

int player_rect_actualise(player_t* player){
    player->hitbox.x=player->x_coord;
    player->hitbox.y=player->y_coord;
    return 0;
};

