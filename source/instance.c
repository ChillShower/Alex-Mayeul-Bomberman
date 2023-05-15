#include "instance.h"

int mapInstanciation(map_t* map, int width, int height, screen_t* screen)
{
    map->width = width;
    map->height = height;

    int screenWidth;
    screenGetWidth(&screenWidth, screen);

    map->sizeOfCell = (int) screenWidth / width;

    return 0;
}

int playerInit(player_t* player, map_t* map, screen_t* screen){

    int screen_width;
    screenGetWidth(&screen_width, screen);

    int screen_height;
    screenGetHeight(&screen_height, screen);

    int map_width;
    mapGetWidth(&map_width,map);

    int map_height;
    mapGetHeight(&map_height, map);

    int sizeOfCell;
    mapGetSizeOfCell(&sizeOfCell, map);

    int x_fake_origin= screen_width/2-sizeOfCell*map_width/2;
    int y_fake_origin= screen_height/2-sizeOfCell*map_height/2;

    setCoordx(player,x_fake_origin);
    setCoordy(player,y_fake_origin);
    setHealth(player,3);
    player->speed=4;

    inputs_t* inputs = malloc(sizeof(inputs_t));
    player->x_strength = 1;
    player->y_strength = 1;
    player->immuned = 0;
    player->death = 0;
    player->frame = FRAME_RATE;
    player->inputs = inputs;
    player->inputs->up=0;
    player->inputs->down=0;
    player->inputs->left=0;
    player->inputs->right=0;
    player->hitbox.h=60;
    player->hitbox.w=60;
    player->hitbox.x=(player->x_coord - player->hitbox.w/2);
    player->hitbox.y=(player->y_coord - player->hitbox.h/2);
    player ->texture_player=NULL;
    return 0;
};

int texturesListInit(SDL_Texture** texturesList, window_t* window)
{
    // JOUEUR:
    texturesList[0] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/bas_1.png");
    texturesList[1] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/bas_2.png");
    texturesList[2] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/bas_3.png");
    texturesList[3] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/gauche_1.png");
    texturesList[4] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/gauche_2.png");
    texturesList[5] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/gauche_3.png");
    texturesList[6] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/droite_1.png");
    texturesList[7] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/droite_2.png");
    texturesList[8] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/droite_3.png");
    texturesList[9] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/haut_1.png");
    texturesList[10] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/haut_2.png");
    texturesList[11] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/haut_3.png");

    // STATIQUE:

// MUR:
    texturesList[12] = IMG_LoadTexture(window->cur_renderer, "resources/static/wall/wall_brittle.png");

// BOMB:

    texturesList[13] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/bomb_1.png");
    texturesList[14] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/bomb_2.png");
    texturesList[15] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/bomb_3.png");

// EXPLOSION:
    texturesList[16] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/explosion_1.png");
    texturesList[17] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/explosion_2.png");
    texturesList[18] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/explosion_3.png");
    texturesList[19] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/explosion_4.png");
    texturesList[20] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/explosion_5.png");
    texturesList[21] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/explosion_6.png");
    texturesList[22] = IMG_LoadTexture(window->cur_renderer, "resources/static/bomb/explosion_7.png");

// MORT:

    texturesList[23] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/mort_1.png");
    texturesList[24] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/mort_2.png");
    texturesList[25] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/mort_3.png");

// GAMEOVER:
    texturesList[26] = IMG_LoadTexture(window->cur_renderer, "resources/static/menu/gameover.png");
    
    return 0;
}