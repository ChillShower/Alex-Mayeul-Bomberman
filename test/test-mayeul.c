#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "instance.h"

int main( int argc, char* args[])
{
    screen_t screen;
    initScreen(&screen);

    window_t window;
    initWindow(&screen, &window);

    SDL_Rect rectArray[DEFAULT_MAP_WIDTH*DEFAULT_MAP_HEIGHT];
    grid_init(&screen, rectArray, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, DEFAULT_SIZE_OF_CELL);

    map_t map;
    mapInit(&map);
    generateMap(0.85, 0.05, &map);

    SDL_Texture* texturesList[60];
    texturesListInit(texturesList, &window);

    int const NUMBER_OF_PLAYERS = 4;
    player_t listOfPlayers[NUMBER_OF_PLAYERS];
    
    for(int i = 0; i<NUMBER_OF_PLAYERS; ++i)
    {
        playerInit(&listOfPlayers[i], i, &map, &screen, texturesList);
    }

    TTF_Font* police = NULL;
    police = TTF_OpenFont("resources/fonts/lunchtime-doubly-so.regular.ttf", 12);
    if(police == 0)
    {
        printf("Probleme de lecture du fichier font..\n");
    }

    SDL_Texture* title = IMG_LoadTexture(window.cur_renderer,"resources/menu/background.png"); //"resources/texts/title.png");
    int titleWidth;
    int titleHeight;
    SDL_QueryTexture(title, NULL, NULL, &titleWidth, &titleHeight);

    buttonstate_t reactionPlay = NONE;
    buttonstate_t reactionQuit = NONE;
/* LANCEMENT DU MENU : */
    while((reactionPlay != CLICKED) && (reactionQuit != CLICKED))
    {
        
    prepareScene(&window);
    SDL_RenderCopy(window.cur_renderer, title, NULL,NULL);

    char* textPlay = "Jouer";
    char* textQuit = "Quitter";
    int width = screen.width/4;
    int height = screen.height/4;
    int xPos = screen.width/2 - width/2;
    int yPos = 1*screen.height/3;
    int deltaButtons = screen.height/3;

    SDL_Rect buttonPlay;
    buttonPlay.x =xPos;
    buttonPlay.y = yPos;
    buttonPlay.w = width;
    buttonPlay.h = height;

    SDL_Rect buttonQuit;
    buttonQuit.x =xPos;
    buttonQuit.y = yPos + deltaButtons;
    buttonQuit.w = width;
    buttonQuit.h = height;

    SDL_Rect listOfButtons[2];
    listOfButtons[0] = buttonPlay;
    listOfButtons[1] = buttonQuit;

    buttonstate_t* listOfReactions[2];
    listOfReactions[0] = &reactionPlay;
    listOfReactions[1] = &reactionQuit;

    doMouse(listOfButtons, listOfReactions, 2);
    doMouse(listOfButtons,listOfReactions,2);
    SDL_Color colorPlay;
    SDL_Color colorQuit;

    colorReactionToMouse(reactionPlay, &colorPlay);
    colorReactionToMouse(reactionQuit, &colorQuit);
    showButton(&window, &screen, texturesList, &buttonPlay, police, textPlay, colorPlay);
    showButton(&window, &screen, texturesList, &buttonQuit, police, textQuit, colorQuit);
    SDL_RenderPresent(window.cur_renderer);
    SDL_Delay(10);
    }
    SDL_Delay(200);
    if(reactionQuit == CLICKED)
    {
        SDL_Texture* alex = IMG_LoadTexture(window.cur_renderer,"resources/menu/alex.png");
        SDL_RenderCopy(window.cur_renderer, alex, NULL,NULL);
        SDL_RenderPresent(window.cur_renderer);
        SDL_Delay(100);
        SDL_DestroyTexture(alex);
        /* Liberation de la memoire : */
    for(int i = 0; i<NUMBER_OF_PLAYERS; ++i)
    {
        playerDestruction(&listOfPlayers[i]);
    }
    mapDestruction(&map);
    texturesListDestroy(texturesList);
    SDL_DestroyRenderer(window.cur_renderer);
    SDL_DestroyWindow(window.cur_window);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;

    }
    
/* FIND DU MENU */
    int pause = 0;
    int lastKey[NUMBER_OF_PLAYERS];
    while (!(caseOfGameOver(listOfPlayers, NUMBER_OF_PLAYERS)))
    {

        prepareScene(&window);
        grid_renderer(&screen, rectArray, &map, &window, texturesList);
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);

        for(int i = 0; i< NUMBER_OF_PLAYERS; ++i)
        {
            if(listOfPlayers[i].health <= 0)
            {
                playerResetInputs(&listOfPlayers[i]);
            }
            returnToRestPose(&listOfPlayers[i],lastKey[i],texturesList);
            reactToKey(&listOfPlayers[i],&map,&window,&screen,texturesList,&lastKey[i]);
            gridActualisation(&map,&screen,&window, texturesList);
            playerActualise(&listOfPlayers[i], &map, &screen, &window, texturesList);
            playerShowUI(&listOfPlayers[i], &window, texturesList, police);
            draw_player(&listOfPlayers[i], &window, police);

        } 
		
        SDL_RenderPresent( window.cur_renderer);
        SDL_Delay(10);

        do{
        doInput(listOfPlayers, NUMBER_OF_PLAYERS, &pause);
        if(pause == 1)
        {
            showEscapeMenu(&window, &screen,texturesList,police);
        }
        
        }while(pause == 1);
        

    }

    SDL_RenderCopy(window.cur_renderer, texturesList[26], NULL,NULL);
    SDL_RenderPresent( window.cur_renderer);
	SDL_Delay(5000);


/* Liberation de la memoire : */
    for(int i = 0; i<NUMBER_OF_PLAYERS; ++i)
    {
        playerDestruction(&listOfPlayers[i]);
    }
    mapDestruction(&map);
    texturesListDestroy(texturesList);
    SDL_DestroyRenderer(window.cur_renderer);
    SDL_DestroyWindow(window.cur_window);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}