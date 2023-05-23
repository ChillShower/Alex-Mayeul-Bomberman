#include "../include/renderer.h"

int initScreen(screen_t* screen){
    screen->width= DEFAULT_SCREEN_WIDTH;
    screen->height= DEFAULT_SCREEN_HEIGHT;
    return 0;

}

int initWindow(screen_t* screen,window_t* window){
    window->cur_window=NULL;
    window->screenSurface=NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    else
    {
        window->cur_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen->width, screen->height,  SDL_WINDOW_SHOWN);
        if( window->cur_window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }

    };
    window->cur_renderer=SDL_CreateRenderer(window->cur_window,-1,SDL_RENDERER_ACCELERATED);
        if( window->cur_renderer == NULL )
        {
            printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    if(TTF_Init() < 0){
	fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	exit(EXIT_FAILURE);
    }

    return 0;
};

int destroyWindow(window_t* window){
    

    SDL_DestroyWindow( window->cur_window );
    SDL_DestroyRenderer(window ->cur_renderer);

    SDL_Quit();
    return 0;
};

int screenGetWidth(int* width, screen_t* screen){
    *width = screen->width;
    return 0;
}
int screenGetHeight(int* height, screen_t* screen){
    *height = screen->height;
    return 0;
}
int screenSetWidth(int width, screen_t* screen){
    screen->width = width;
    return 0;
}
int screenSetHeight(int height, screen_t* screen){
    screen->height = height;
    return 0;
}

int initSDL_Rect(SDL_Rect * pos, int x, int y, unsigned int w, unsigned int h){
	if(pos == NULL) return 1;
	pos->x = x;      //abscisse
	pos->y = y;     //ordonnées
	pos->w = w;    //longueur
	pos->h = h;   //largeur
    return 0;
};


int grid_init(screen_t* screen,SDL_Rect* rect_array, int grid_width, int grid_height, int size_rect){

    int x_fake_origin= screen->width/2-size_rect*grid_width/2;
    int y_fake_origin= screen->height/2-size_rect*grid_height/2;
    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_height;j++){
            initSDL_Rect(&(rect_array[i+j*grid_width]),x_fake_origin+i*size_rect,y_fake_origin+j*size_rect ,size_rect,size_rect);   
        };
    };
    return 0;

}

int grid_renderer_first(SDL_Rect* array_rect, window_t* window, int grid_width, int grid_height){
    SDL_SetRenderDrawColor(window->cur_renderer,255,255,255,255);
    SDL_RenderDrawRects(window->cur_renderer,array_rect,grid_width*grid_height);
    return 0;
};

int grid_renderer(screen_t* screen, SDL_Rect* array_rect, map_t* map, window_t* window, SDL_Texture** texturesList){

    int grid_width;
    mapGetWidth(&grid_width, map);

    int grid_height;
    mapGetHeight(&grid_height, map);
    
    wall_t wall;
    cell_t cell;
    
    SDL_SetRenderDrawColor(window->cur_renderer, 0,0,0,255);
    SDL_RenderFillRects(window->cur_renderer, array_rect, grid_width*grid_height);
    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_height;j++){

            cell = map->grid[i + j*grid_width];

            cellGetWall(&wall, &cell);
            if( wall.wallstate == SOLID)
            {
                SDL_SetRenderDrawColor(window->cur_renderer,92, 64, 51,255);
                SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
            }
            else if( wall.wallstate == BRITTLE)
            {
                SDL_RenderCopy(window->cur_renderer, texturesList[12], NULL,&array_rect[i+j*grid_width]);
            }
            else if( wall.wallstate == STAR)
            {
                SDL_RenderCopy(window->cur_renderer, texturesList[27], NULL,&array_rect[i+j*grid_width]);
            }

            else if(wall.wallstate == EMPTY)
            {

                if(cell.bomb !=NULL)
                {

                    if( (2*BOMB_FRAME/3 < cell.bomb->frame) && (cell.bomb->frame <=BOMB_FRAME))
	                {
		                SDL_RenderCopy(window->cur_renderer, texturesList[13], NULL,&array_rect[i+j*grid_width]);
	                }
	                if( (BOMB_FRAME/3< cell.bomb->frame) && (cell.bomb->frame <=2*BOMB_FRAME/3) )
	                {
		                SDL_RenderCopy(window->cur_renderer, texturesList[14], NULL,&array_rect[i+j*grid_width]);
	                }

	                if( (0<=cell.bomb->frame) && (cell.bomb->frame <=2*BOMB_FRAME/3) )
	                {
		                SDL_RenderCopy(window->cur_renderer, texturesList[15], NULL,&array_rect[i+j*grid_width]);
	                }

                };
                if(cell.explosion !=NULL)
                {

                        if( (6*EXPLOSION_FRAME/7<=cell.explosion->frame) && (cell.explosion->frame <=7*EXPLOSION_FRAME/7) )
	                    {
		                    SDL_RenderCopy(window->cur_renderer, texturesList[16], NULL,&array_rect[i+j*grid_width]);
	                    }
                        if( (5*EXPLOSION_FRAME/7<=cell.explosion->frame) && (cell.explosion->frame <=6*EXPLOSION_FRAME/7) )
	                    {
		                    SDL_RenderCopy(window->cur_renderer, texturesList[17], NULL,&array_rect[i+j*grid_width]);
	                    }
                        if( (4*EXPLOSION_FRAME/7<=cell.explosion->frame) && (cell.explosion->frame <=5*EXPLOSION_FRAME/7) )
	                    {
		                    SDL_RenderCopy(window->cur_renderer, texturesList[18], NULL,&array_rect[i+j*grid_width]);
	                    }
                        if( (3*EXPLOSION_FRAME/7<=cell.explosion->frame) && (cell.explosion->frame <=4*EXPLOSION_FRAME/7) )
	                    {
		                    SDL_RenderCopy(window->cur_renderer, texturesList[19], NULL,&array_rect[i+j*grid_width]);
	                    }
                        if( (2*EXPLOSION_FRAME/7<=cell.explosion->frame) && (cell.explosion->frame <=3*EXPLOSION_FRAME/7) )
	                    {
		                    SDL_RenderCopy(window->cur_renderer, texturesList[20], NULL,&array_rect[i+j*grid_width]);
	                    }
                        if( (EXPLOSION_FRAME/7<=cell.explosion->frame) && (cell.explosion->frame <=2*EXPLOSION_FRAME/7) )
	                    {
		                    SDL_RenderCopy(window->cur_renderer, texturesList[21], NULL,&array_rect[i+j*grid_width]);
	                    }
                        if( (0<=cell.explosion->frame) && (cell.explosion->frame <=EXPLOSION_FRAME/7) )
	                    {
		                    SDL_RenderCopy(window->cur_renderer, texturesList[22], NULL,&array_rect[i+j*grid_width]);
	                    }
                    
                    if (explosionIsFinished(cell.explosion))
                    {
                        SDL_SetRenderDrawColor(window->cur_renderer,0,0,0,255);
                        SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
                    }
                }  
                else if(cell.bomb==NULL && cell.explosion==NULL)
                {
                SDL_SetRenderDrawColor(window->cur_renderer,0,0,0,255);
                SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
                
                }
            }
   
        };

    };
    
    return 0;
};

int playerShowUI(player_t* player, window_t* window,SDL_Texture** texturesList, TTF_Font* police)
{
        // AFFICHAGE DE L'UI:
    SDL_Rect numberRect;
    char str[2];
    sprintf(str, "%d", player->id);
    SDL_Surface * surf = TTF_RenderText_Solid(police, str, player->color);
    SDL_Texture* text = SDL_CreateTextureFromSurface(window->cur_renderer, surf);
    initSDL_Rect(&numberRect,2*DEFAULT_SIZE_OF_HEART/3,player->id*DEFAULT_SIZE_OF_HEART + 2*DEFAULT_SIZE_OF_HEART/3 ,DEFAULT_SIZE_OF_HEART/2,DEFAULT_SIZE_OF_HEART/2);

    if(player->health > 0)
    {
        SDL_Rect UI[player->health+1];
        initSDL_Rect(&(UI[0]),0,player->id*DEFAULT_SIZE_OF_HEART ,DEFAULT_SIZE_OF_HEART,DEFAULT_SIZE_OF_HEART);
        SDL_RenderCopy(window->cur_renderer, texturesList[42], NULL, &UI[0]);
        SDL_RenderCopy(window->cur_renderer, text,NULL, &numberRect);

        SDL_DestroyTexture(text);
        for(int i = 1; i< player->health+1; ++i)
        {
            initSDL_Rect(&(UI[i]),i*DEFAULT_SIZE_OF_HEART,player->id*DEFAULT_SIZE_OF_HEART ,DEFAULT_SIZE_OF_HEART,DEFAULT_SIZE_OF_HEART);
            SDL_RenderCopy(window->cur_renderer, texturesList[40], NULL, &UI[i]);
        }
    }
    if(player->health < 0)
    {
        SDL_Rect UI[1];
        initSDL_Rect(&(UI[0]),0,player->id*DEFAULT_SIZE_OF_HEART ,DEFAULT_SIZE_OF_HEART,DEFAULT_SIZE_OF_HEART);
        SDL_RenderCopy(window->cur_renderer, texturesList[43], NULL, &UI[0]);
        SDL_RenderCopy(window->cur_renderer, text,NULL, &numberRect);
    }
    return 0;
}

SDL_Texture* loadTexture(SDL_Texture *texture,char *filename, window_t* window)
{
    SDL_Texture *texture_block;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture_block = IMG_LoadTexture(window->cur_renderer, filename);
   
	return texture_block;
}

int player_set_texture(player_t* player,SDL_Texture* texture){
	player->texture_player = texture;
    return 0;
};

int draw_player(player_t* player, window_t* window, TTF_Font* police)
{
    char str[2];
    sprintf(str, "%d", player->id);
    SDL_Surface * surf = TTF_RenderText_Solid(police, str, player->color);
    SDL_Texture* text = SDL_CreateTextureFromSurface(window->cur_renderer, surf);
    SDL_RenderCopy(window->cur_renderer, text, NULL, &(player->idBox));
    SDL_RenderCopy(window->cur_renderer, player ->texture_player, NULL, &(player->hitbox));
    return 0;
}

int showButton(window_t* window, screen_t* screen, SDL_Texture** texturesList, SDL_Rect* buttonHitbox, TTF_Font* font, char* text, SDL_Color color)
{
    int xPos = buttonHitbox->x;
    int yPos = buttonHitbox->y;
    int width = buttonHitbox->w;
    int height= buttonHitbox->h;

    SDL_Rect buttonBackground;
    buttonBackground.w = width;
    buttonBackground.h = height;
    buttonBackground.x = xPos;
    buttonBackground.y = yPos;

    SDL_Texture* texture_target = SDL_CreateTexture(window->cur_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, buttonBackground.w, buttonBackground.h);
    SDL_SetTextureBlendMode(texture_target, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(window->cur_renderer, texture_target);

    SDL_Texture* buttonBackgroundTexture = NULL;
    buttonBackgroundTexture = texturesList[41];
    SDL_RenderCopy(window->cur_renderer, buttonBackgroundTexture, NULL, NULL);

    SDL_Rect textBox;
    textBox.w = buttonBackground.w/2;
    textBox.h = 2*buttonBackground.h/3;
    textBox.x = buttonBackground.w/4;
    textBox.y = buttonBackground.h/4;

    SDL_Surface * textSurf = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window->cur_renderer, textSurf);
    SDL_RenderCopy(window->cur_renderer, textTexture, NULL, &textBox);

    SDL_SetRenderTarget(window->cur_renderer, NULL);
    SDL_RenderCopy(window->cur_renderer, texture_target, NULL, &buttonBackground);

    SDL_DestroyTexture(texture_target);
    SDL_DestroyTexture(textTexture);
    return 0;
}

int getPlayerGridCoordinates(player_t* player, screen_t* screen, map_t* map, int* x, int* y)
{
    int x_coord;
    getCoordx(&x_coord, player);

    int y_coord;
    getCoordy(&y_coord, player);

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

    int diffx = x_coord - x_fake_origin;
    int diffy = y_coord - y_fake_origin;

    *x = diffx/sizeOfCell;
    *y = diffy/sizeOfCell;

    return 0;
// Valeur de vérité : la coordonnée est-elle en dehors de la carte?
}

int IsPlayerInMap(player_t* player, screen_t* screen, map_t* map)
{
        int x_coord;
    getCoordx(&x_coord, player);

    int y_coord;
    getCoordy(&y_coord, player);

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

    int diffx = x_coord - x_fake_origin;
    int diffy = y_coord - y_fake_origin;

    return !(diffx <0 || diffx/sizeOfCell > map->width-1 || diffy < 0 || diffy/sizeOfCell  > map->height-1);
}