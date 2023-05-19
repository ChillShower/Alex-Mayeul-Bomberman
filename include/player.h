#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include"param.h"
#include <string.h>
#include "sprite.h"

/* les contrôles prennent la valeur 1 si la touche est activée 0 sinon */
typedef struct inputs{
    int up;
    int down;
    int left;
    int right;
    int space;
} inputs_t;

typedef struct player{

    /* le numéro du joueur*/
    int id;

    /* coordonnées pixels du joueur*/
    int x_coord;
    int y_coord;

    /* coordonnées dans la grille de carte*/
    int x_grid;
    int y_grid;

    /* attributs */
    int speed;
    int health;
    int x_strength;
    int y_strength;

    /* numero de l'image d'animation de mort */
    int death;

    /* numero de l'image d'animation de mort immunité (clignotement) : prend la valeur par défaut, se décremmente, lorsque la valeur atteint 0, le joueur n'est plus immunisé */
    int immuned;

    /* activation ou désactivation des touches de contrôle du joueur */
    inputs_t* inputs;

    /* image du joueur à l'écran et taille de l'image à l'écran*/
    SDL_Texture* texture_player;
    SDL_Rect hitbox;
    SDL_Rect idBox;
    SDL_Color color;

    /* numero de l'image de l'animation de déplacement */
    int frame;
    
}player_t;

//init:
int playerDestruction(player_t* player);

//coord
int getCoordx(int* x_coord, player_t* player);

int getCoordy(int* y_coord, player_t* player);

int getGridy(int* y_grid, player_t* player);

int getGridx(int* x_grid, player_t* player);

int setCoordx(player_t* player,int x);

int setCoordy(player_t* player,int y);

int setGridx(player_t* player);

int setGridy(player_t* player);
//health
int getHealth(player_t* player);

int setHealth(player_t* player, int new_health);

int healthSubstract(player_t* player, int substract);

int healthAdd(player_t* player, int add);
int setPlayerX_strength(int x, player_t* player);
int setPlayerY_strength(int y, player_t* player);
int getPlayerX_strength(int* x, player_t* player);
int getPlayerY_strength(int* x, player_t* player);
int player_rect_actualise(player_t* player);

// Actions:

int playerPushUp(player_t* player);
int playerPushDown(player_t* player);
int playerPushLeft(player_t* player);
int playerPushRight(player_t* player);
int playerPushBomb(player_t* player);
int playerResetInputs(player_t* player);

int playerIsDead(player_t* player);
#endif