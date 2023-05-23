#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "instance.h"

int main( int argc, char* args[])
{
    /* INITIALISATION DES FENETRES ET DU PARAMETRAGE DE RENDU */
    screen_t screen;
    initScreen(&screen);

    window_t window;
    initWindow(&screen, &window);

    /* INITIALISATION DE LA CARTE VIDE COTE SDL (CARTE DE RENDU) */
    SDL_Rect rectArray[DEFAULT_MAP_WIDTH*DEFAULT_MAP_HEIGHT];
    grid_init(&screen, rectArray, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, DEFAULT_SIZE_OF_CELL);

    map_t map;
    mapInit(&map);

    /* PARAMETRAGE DES PROBABILITES D'APPARITION D'UN MUR CASSABLE OU D'UN BONUS */
    float const BRITTLE_DENSITY = 0.85;
    float const BONUS_DENSITY = 0.05;

    generateMap(BRITTLE_DENSITY, BONUS_DENSITY, &map);

    /* CHARGEMENT DES SPRITES */
    SDL_Texture* texturesList[60];
    texturesListInit(texturesList, &window);

    /* CREATION DE LA SESSION DE JEU : INITIALISATION DES JOUEURS */
    int const NUMBER_OF_PLAYERS = 4;
    player_t listOfPlayers[NUMBER_OF_PLAYERS];
    
    for(int i = 0; i<NUMBER_OF_PLAYERS; ++i)
    {
        playerInit(&listOfPlayers[i], i, &map, &screen, texturesList);
    }

    /* CHARGEMENT DE LA POLICE D'ECRITURE (menu, pause et numeros joueurs) */
    TTF_Font* police = NULL;
    police = TTF_OpenFont("resources/fonts/lunchtime-doubly-so.regular.ttf", 12);
    if(police == 0)
    {
        printf("Probleme de lecture du fichier font..\n");
    }

    SDL_Texture* title = IMG_LoadTexture(window.cur_renderer,"resources/interface/menu/background.png"); //"resources/texts/title.png");
    int titleWidth;
    int titleHeight;
    SDL_QueryTexture(title, NULL, NULL, &titleWidth, &titleHeight);

    /* --- LANCEMENT DU MENU DE DEMARRAGE --- */
    buttonstate_t reactionPlay = NONE;
    buttonstate_t reactionQuit = NONE;

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

    /* CREATIONS DES RECTANGLES CORRESPONDANT AUX BOUTONS */
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

    /* Une réaction des bouttons doit-elle être enclenchée ? */
    doMouse(listOfButtons, listOfReactions, 2);
    doMouse(listOfButtons,listOfReactions,2);
    SDL_Color colorPlay;
    SDL_Color colorQuit;

    /* Réaction des bouttons : changement de couleur en fonction de la souris */
    colorReactionToMouse(reactionPlay, &colorPlay);
    colorReactionToMouse(reactionQuit, &colorQuit);
    showButton(&window, &screen, texturesList, &buttonPlay, police, textPlay, colorPlay);
    showButton(&window, &screen, texturesList, &buttonQuit, police, textQuit, colorQuit);
    SDL_RenderPresent(window.cur_renderer);

    /* FRAME_RATE images par seconde */
    SDL_Delay(1000/FRAME_RATE);
    }
    SDL_Delay(200);

    /* FERMETURE DU JEU ET LIBERATION DE LA MEMOIRE INSTANCIEE */

    if(reactionQuit == CLICKED)
    {
        SDL_Texture* alex = IMG_LoadTexture(window.cur_renderer,"/resources/interface/menu/alex.png");
        SDL_RenderCopy(window.cur_renderer, alex, NULL,NULL);
        SDL_RenderPresent(window.cur_renderer);
        SDL_Delay(100);
        SDL_DestroyTexture(alex);
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
    
/* --- FIN DU MENU DE DEMARRAGE : DEMARRAGE DU JEU */

    /* le jeu est-il en pause ? (touche echap)*/
    int pause = 0;
    
    /* 
        dernières touches pressées par chaque joueur
        sert à réinitialiser le sprite joueur dans sa position
        de repos dans la direction vers laquelle il se dirige

     */
    int lastKey[NUMBER_OF_PLAYERS];

    while (!(caseOfGameOver(listOfPlayers, NUMBER_OF_PLAYERS)))
    {

        /* l'ancienne scène est effacée afin de redessiner par dessus */
        prepareScene(&window);

        /* affichage des objets disposés sur la carte avec leurs sprites */
        grid_renderer(&screen, rectArray, &map, &window, texturesList);
        /* affichage du quadrillage et du fond noir en sous couche */
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);

        /* 
            mise à jours des données de tous les objets, joueurs et carte
            suivi de l'affichage de joueur par dessus
        */
        for(int i = 0; i< NUMBER_OF_PLAYERS; ++i)
        {
            if(listOfPlayers[i].health <= 0)
            {
                playerResetInputs(&listOfPlayers[i]);
            }
            /* retour à la position de repos dans le cas où aucun déplacement est enclenché */
            returnToRestPose(&listOfPlayers[i],lastKey[i],texturesList);

            /* pression des touches de contrôle */
            reactToKey(&listOfPlayers[i],&map,&window,&screen,texturesList,&lastKey[i]);
            
            /* information de la grille sont mis à jour */
            gridActualisation(&map,&screen,&window, texturesList);

            /* les données du joueur sont mis à jour en fonction des évènements en cours */
            playerActualise(&listOfPlayers[i], &map, &screen, &window, texturesList);

            /* affichage de l'interface utilisateur */
            playerShowUI(&listOfPlayers[i], &window, texturesList, police);
            draw_player(&listOfPlayers[i], &window, police);

        } 
		
        SDL_RenderPresent( window.cur_renderer);

        /* FRAME_RATE images par seconde */
        SDL_Delay(1000/FRAME_RATE);

        /*le menu pause est-il enclenché ou desenclenché ? */
        do{
        doInput(listOfPlayers, NUMBER_OF_PLAYERS, &pause);
        if(pause == 1)
        {
            showEscapeMenu(&window, &screen,texturesList,police);
        }
        
        }while(pause == 1);
        

    }

    /* GAME OVER à l'écran : */
    SDL_RenderCopy(window.cur_renderer, texturesList[26], NULL,NULL);
    SDL_RenderPresent( window.cur_renderer);
	SDL_Delay(5000);


/* Liberation de la memoire */
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