#ifndef EVENT_H
#define EVENT_H
#include "renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum buttonstate{CLICKED, ON, NONE} buttonstate_t;

void doInput(player_t* listOfPlayers, int numberOfPlayers, int* pause);
int inPause(SDL_KeyboardEvent* event, int* pause);
int doKeyDown(SDL_KeyboardEvent *event,player_t* listOfPlayers, int numberOfPlayers);
int doKeyUp(SDL_KeyboardEvent *event,player_t* listOfPlayers, int numberOfPlayers);

void doMouse(SDL_Rect* buttonHitbox,buttonstate_t** listOfReactions, int numberOfButtons);
int clickOnButton(SDL_Rect* buttonHitbox,buttonstate_t** listOfReactions, SDL_Event* event, int numberOfButtons);
int mouseOnButton(SDL_Rect* buttonHitbox,buttonstate_t** listOfReactions, SDL_Event* event, int numberOfButtons);
int colorReactionToMouse(buttonstate_t reaction,SDL_Color* color);
void showEscapeMenu(window_t* window, screen_t* screen, SDL_Texture** texturesList, TTF_Font* fon);
int prepareScene(window_t* window);
int presentScene(window_t* window);


// JOUEUR:

int reactToKey(player_t* player, map_t* map, window_t* window, screen_t* screen, SDL_Texture** texturesList, int* lastKey);
int playerGoRight(player_t* player, window_t* window, SDL_Texture** texturesList);
int playerGoLeft(player_t* player, window_t* window, SDL_Texture** texturesList);
int playerGoUp(player_t* player, window_t* window, SDL_Texture** texturesList);
int playerGoDown(player_t* player, window_t* window, SDL_Texture** texturesList);
int playerPutBomb(player_t* player, map_t* map, window_t* window);
int gridActualisation(map_t* map, screen_t* screen, window_t* window, SDL_Texture** texturesList);
int explosionSetup(cell_t* cell, map_t* map);
int smthgIsUp(player_t* player, map_t* map, screen_t* screen);
int smthgIsDown(player_t* player, map_t* map, screen_t* screen);
int smthgIsLeft(player_t* player, map_t* map, screen_t* screen);
int smthgIsRight(player_t* player, map_t* map, screen_t* screen);
int playerReactToBomb(player_t* player);
int playerActualise(player_t* player, map_t* map, screen_t* screen, window_t* window, SDL_Texture** texturesList);
int caseOfGameOver(player_t* player, int numberOfPlayers);
int returnToRestPose(player_t* player, int lastKey, SDL_Texture** texturesList);
int playerReactToStar(player_t* player, cell_t* cell);
#endif