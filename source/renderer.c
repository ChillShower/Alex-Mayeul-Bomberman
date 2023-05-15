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
        window->cur_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen->width, screen->height, SDL_WINDOW_FULLSCREEN_DESKTOP );
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
    return 0;
};

int destroyWindow(window_t* window){
    
    //Destroy window
    SDL_DestroyWindow( window->cur_window );
    SDL_DestroyRenderer(window ->cur_renderer);
    //Quit SDL subsystems
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

int grid_renderer(SDL_Rect* array_rect, map_t* map, window_t* window, SDL_Texture** texturesList){

    int grid_width;
    mapGetWidth(&grid_width, map);

    int grid_height;
    mapGetHeight(&grid_height, map);
    
    wall_t wall;
    cell_t cell;
    
    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_height;j++){

            cell = map->grid[i + j*grid_width];
            /*mur*/
            cellGetWall(&wall, &cell);
            if( wall.wallstate == SOLID)
            {
                SDL_SetRenderDrawColor(window->cur_renderer,92, 64, 51,255);
                SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
            }
            else if( wall.wallstate == BRITTLE)
            {
                SDL_SetRenderDrawColor(window->cur_renderer,0,255,0,255);
                SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
                SDL_RenderCopy(window->cur_renderer, texturesList[12], NULL,&array_rect[i+j*grid_width]);
            }

            else if(wall.wallstate == EMPTY)
            {
                //bomb_t* bomb=NULL;
                //cellGetBomb(bomb,&cell);
                if(cell.bomb !=NULL)
                {
                    //test_rectangle(window);
                    //SDL_SetRenderDrawColor(window->cur_renderer,255, 182, 193,255);
                    //SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
                    if( (2*BOMB_FRAME/3 < cell.bomb->frame) && (cell.bomb->frame <=BOMB_FRAME))
	                {
                        printf("OUI\n");
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
                    //bombActualise(cell.bomb);
                    
                    if (isExploded(cell.bomb))
                    {
                      //  bombDestruction(cell.bomb);
                    //    cell.bomb=NULL;
                      //  SDL_SetRenderDrawColor(window->cur_renderer,0,0,0,255);
                        SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
                    }
                    //bombActualise(cell.bomb);
                    
                    if (isExploded(cell.bomb))
                    {
                      //  bombDestruction(cell.bomb);
                    //    cell.bomb=NULL;
                      //  SDL_SetRenderDrawColor(window->cur_renderer,0,0,0,255);
                        SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
                    }
                };
                if(cell.explosion !=NULL)
                {
                    //test_rectangle(window);
                    //SDL_SetRenderDrawColor(window->cur_renderer,88, 41, 0,255);
                    //SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);

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
                    //SDL_RenderCopy(window->cur_renderer, texturesList[16], NULL,&array_rect[i+j*grid_width]);
                    //bombActualise(cell.bomb);
                    
                    if (explosionIsFinished(cell.explosion))
                    {
                      //  bombDestruction(cell.bomb);
                    //    cell.bomb=NULL;
                    test_rectangle(window);
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


SDL_Texture* loadTexture(SDL_Texture *texture,char *filename, window_t* window)
{
    SDL_Texture *texture_block;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture_block = IMG_LoadTexture(window->cur_renderer, filename);
   
	return texture_block;
}
int draw_on_rectangle(SDL_Texture * texture,SDL_Rect rectangle,window_t* window)
{
    SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h);
    SDL_RenderCopy(window->cur_renderer, texture, NULL, &rectangle);
    return 0;
}

int player_set_texture(player_t* player,SDL_Texture* texture){
    
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	player->texture_player = texture;
    return 0;
};

int draw_player(player_t* player, window_t* window)
{
    //int x;
    //SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h);
    SDL_RenderCopy(window->cur_renderer, player ->texture_player, NULL, &(player->hitbox));
    
    //setGridy(player);
    //getGridy(&x,player);
    /*if (x==0){
    SDL_Rect rectangle={0,0,40,40};
    SDL_SetRenderDrawColor(window->cur_renderer,0,0,0,255);
    SDL_RenderFillRect(window->cur_renderer,&rectangle);
    };*/
    return 0;
}


SDL_Texture* SDL_texture_init(SDL_Texture* texture, window_t* window, char* filename)
{
    return loadTexture(texture,filename, window);
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

int test_rectangle(window_t* window){
    SDL_Rect rectangle={0,0,40,40};
    SDL_SetRenderDrawColor(window->cur_renderer,0,0,0,255);
    SDL_RenderFillRect(window->cur_renderer,&rectangle);
    return 0;
}