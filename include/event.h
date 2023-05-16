#ifndef EVENT_H
#define EVENT_H
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
#define SPACE_KEY SDL_SCANCODE_SPACE

/*__________________________________________*/

void doInput(player_t* player);
int doKeyDown(SDL_KeyboardEvent *event,player_t* player);
int doKeyUp(SDL_KeyboardEvent *event,player_t* player);
int prepareScene(window_t* window);
int presentScene(window_t* window);


// JOUEUR:

int reactToKey(player_t* player, map_t* map, window_t* window, screen_t* screen, SDL_Texture** texturesList, int* lastKey);
int playerGoRight(player_t* player, window_t* window, SDL_Texture** texturesList);
int playerGoLeft(player_t* player, window_t* window, SDL_Texture** texturesList);
int playerGoUp(player_t* player, window_t* window, SDL_Texture** texturesList);
int playerGoDown(player_t* player, window_t* window, SDL_Texture** texturesList);
int playerPutBomb(player_t* player, map_t* map, window_t* window);
int gridActualisation(player_t* player, map_t* map, screen_t* screen, window_t* window, SDL_Texture** texturesList);
int explosionSetup(cell_t* cell, map_t* map);
int smthgIsUp(player_t* player, map_t* map, screen_t* screen);
int smthgIsDown(player_t* player, map_t* map, screen_t* screen);
int smthgIsLeft(player_t* player, map_t* map, screen_t* screen);
int smthgIsRight(player_t* player, map_t* map, screen_t* screen);
int playerReactToBomb(player_t* player);
int playerActualise(player_t* player, window_t* window, SDL_Texture** texturesList);
int caseOfGameOver(player_t* player);
int returnToRestPose(player_t* player, int lastKey, SDL_Texture** texturesList);
#endif