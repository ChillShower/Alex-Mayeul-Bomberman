#include "renderer.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    printf("envie de crever pas vrai?\n");
    player_t player;
    setHealth(&player,3);
    healthSubstract(&player,2);
    printf("%d\n",getHealth(&player));
    return 0;
}