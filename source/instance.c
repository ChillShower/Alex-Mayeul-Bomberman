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

int playerInit(player_t* player, int id, map_t* map, screen_t* screen, SDL_Texture** texturesList){

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

    player->id =id;
    player ->texture_player=texturesList[0];

    int x_fake_origin= screen_width/2-sizeOfCell*map_width/2;
    int y_fake_origin= screen_height/2-sizeOfCell*map_height/2;
    if (id >= 4)
    {
        id = rand() % 4;
    }

    if(id == 0)
    {
        setCoordx(player,x_fake_origin + sizeOfCell/2);
        setCoordy(player,y_fake_origin + sizeOfCell/2);
    }
    if(id == 1)
    {
        setCoordx(player,x_fake_origin + map_width*sizeOfCell - sizeOfCell/2);
        setCoordy(player,y_fake_origin + sizeOfCell/2);
    }
    if(id == 2)
    {
        setCoordx(player,x_fake_origin + sizeOfCell/2);
        setCoordy(player,y_fake_origin + map_height*sizeOfCell - sizeOfCell/2);
    }
    if(id == 3)
    {
        setCoordx(player,x_fake_origin + map_width*sizeOfCell - sizeOfCell/2);
        setCoordy(player,y_fake_origin + map_height*sizeOfCell - sizeOfCell/2);
    }
    
    setHealth(player,3);
    player->speed=4;

    inputs_t* inputs = malloc(sizeof(inputs_t));
    player->x_strength = 1;
    player->y_strength = 1;
    player->immuned = 0;
    player->death = 0;
    player->frame = PLAYER_FRAME_RATE;
    player->inputs = inputs;
    player->inputs->up=0;
    player->inputs->down=0;
    player->inputs->left=0;
    player->inputs->right=0;
    player->inputs->space=0;
    player->hitbox.h=2*DEFAULT_SIZE_OF_CELL/3;
    player->hitbox.w=2*DEFAULT_SIZE_OF_CELL/3;
    player->hitbox.x=(player->x_coord - player->hitbox.w/2);
    player->hitbox.y=(player->y_coord - player->hitbox.h/2);
    player->idBox.h=40;
    player->idBox.w=40;
    player->idBox.x=(player->x_coord - player->hitbox.w/2 - player->idBox.h/2);
    player->idBox.y=(player->y_coord - 3*player->hitbox.h/2 - player->idBox.w/2);
    SDL_Color color = {rand() % 256, rand() % 256, rand() % 256, 255 };
    player->color = color;

    return 0;
};

int texturesListInit(SDL_Texture** texturesList, window_t* window)
{
    /*
        Cette fonction sert à charger toutes les textures avant d'être en jeu afin de 
        libérer de la charge à l'ordinateur pendant le cours du jeu.
    
    */
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


// MUR:
    texturesList[12] = IMG_LoadTexture(window->cur_renderer, "resources/objects/wall/wall_brittle.png");

// BOMB:
    texturesList[13] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/bomb_3.png");
    texturesList[14] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/bomb_2.png");
    texturesList[15] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/bomb_1.png");
    
   

// EXPLOSION:
    texturesList[16] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/explosion_1.png");
    texturesList[17] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/explosion_2.png");
    texturesList[18] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/explosion_3.png");
    texturesList[19] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/explosion_4.png");
    texturesList[20] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/explosion_5.png");
    texturesList[21] = IMG_LoadTexture(window->cur_renderer, "resources/objects/bomb/explosion_6.png");
    texturesList[22] = IMG_LoadTexture(window->cur_renderer, "resources/objetcs/bomb/explosion_7.png");

// MORT:

    texturesList[23] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/mort_1.png");
    texturesList[24] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/mort_2.png");
    texturesList[25] = IMG_LoadTexture(window->cur_renderer, "resources/animations/characters/bomberman/mort_3.png");

// GAMEOVER:
    texturesList[26] = IMG_LoadTexture(window->cur_renderer, "resources/interface/menu/gameover.png");

// STAR:

    texturesList[27] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_1.png");
    texturesList[28] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_2.png");
    texturesList[29] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_3.png");
    texturesList[30] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_4.png");
    texturesList[31] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_5.png");
    texturesList[32] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_6.png");
    texturesList[33] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_7.png");
    texturesList[34] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_8.png");
    texturesList[35] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_9.png");
    texturesList[36] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_10.png");
    texturesList[37] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_11.png");
    texturesList[38] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_12.png");
    texturesList[39] = IMG_LoadTexture(window->cur_renderer, "resources/animations/star/star_13.png");
    texturesList[40] = IMG_LoadTexture(window->cur_renderer, "resources/interface/UI/heart.png");

// MENU:

    texturesList[41] = IMG_LoadTexture(window->cur_renderer, "resources/interface/menu/empty_button.png");
    texturesList[42] = IMG_LoadTexture(window->cur_renderer, "resources/interface/UI/icon.png");
    texturesList[43] = IMG_LoadTexture(window->cur_renderer, "resources/interface/UI/dead_icon.png");
    return 0;
}

int texturesListDestroy(SDL_Texture** texturesList)
{
    for(int i = 0; i<41; ++i)
    {
        SDL_DestroyTexture(texturesList[i]);
    }
    return 0;
}