#include "../include/renderer.h"
#include "../include/player.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    printf("envie de crever pas vrai?\n");
    player_t player;
    setHealth(&player,3);
    healthSubstract(&player,2);
    printf("%d\n",getHealth(&player));
    return 0;
}