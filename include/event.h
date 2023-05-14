#ifndef EVENT_H
#define EVENT_H
//#include "player.h"
//#include "map.h"
#include "renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

/*

SOMMAIRE DES INPUTS:
UP,DOWN, RIGHT, LEFT : mouvements correspondants
ECHAP: Quitter le jeu
ESPACE: Poser une bombe



*/

/* DEFINITION DES INPUTS : */
#define UP_KEY SDL_SCANCODE_UP
#define DOWN_KEY SDL_SCANCODE_DOWN
#define LEFT_KEY SDL_SCANCODE_LEFT
#define RIGHT_KEY SDL_SCANCODE_RIGHT
#define SPACE_KEY SDL_SCANCODE_KP_SPACE

/*__________________________________________*/

void doInput(player_t* player);
int doKeyDown(SDL_KeyboardEvent *event,player_t* player);
int doKeyUp(SDL_KeyboardEvent *event,player_t* player);
int prepareScene(window_t* window);
int presentScene(window_t* window);


// JOUEUR:

int reactToKey(player_t* player, map_t* map, window_t* window);
int playerGoRight(player_t* player, window_t* window);
int playerGoLeft(player_t* player, window_t* window);
int playerGoUp(player_t* player, window_t* window);
int playerGoDown(player_t* player, window_t* window);
int playerPutBomb(player_t* player, map_t* map);
int smthgIsUp(player_t* player, map_t* map, screen_t* screen);
int smthgIsDown(player_t* player, map_t* map, screen_t* screen);
int smthgIsLeft(player_t* player, map_t* map, screen_t* screen);
int smthgIsRight(player_t* player, map_t* map, screen_t* screen);

#endif