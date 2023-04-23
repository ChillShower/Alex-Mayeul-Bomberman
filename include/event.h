#ifndef EVENT_H
#define EVENT_H
#include "player.h"
#include "renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define FRAME_RATE = 60

void doInput(player_t* player);
int doKeyDown(SDL_KeyboardEvent *event,player_t* player);
int doKeyUp(SDL_KeyboardEvent *event,player_t* player);
int prepareScene(window_t* window);
int presentScene(window_t* window);

#endif