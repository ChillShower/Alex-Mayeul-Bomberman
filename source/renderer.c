#include <renderer.h>
#include <map.h>


int initScreen(screen_t* screen){
    screen->width=1920;
    screen->height=1080;
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
    *width = screen->wdith;
    return 0;
}
int screenGetHeight(int* height, screen_t* screen){
    *height = screen->height;
    return 0;
}
int screenSetWidth(int width, screen_t* screen){
    screen->widht = width;
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


int grid_init(screen_t* screen,window_t* window,SDL_Rect* rect_array, int* grille, int grid_width,int size_rect){
    int x_fake_origin=screen->width/2-size_rect*grid_width/2;
    int y_fake_origin=screen->height/2-size_rect*grid_width/2;
    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_width;j++){
            initSDL_Rect(&rect_array[i+j*grid_width],x_fake_origin+i*size_rect,y_fake_origin+j*size_rect ,size_rect,size_rect);   
        };
    };
    return 0;

}

int grid_renderer_first(SDL_Rect* array_rect, window_t* window, int* grid, int grid_width){
    SDL_SetRenderDrawColor(window->cur_renderer,255,255,255,255);
    SDL_RenderDrawRects(window->cur_renderer,array_rect,grid_width*grid_width);
    SDL_RenderPresent( window->cur_renderer);
    return 0;
};
/*
int grid_renderer(SDL_Rect* array_rect,SDL_Texture* texture_block, window_t* window, int* grid, int grid_width){
    //SDL_Surface* tmp= SDL_LoadBMP("../assets/text_road.bmp");
    
    //loadTexture(texture_block,"../assets/text1.png",window);
    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_width;j++){
        if (grid[i+j*grid_width]==0){
            
            //SDL_SetRenderDrawColor(window->cur_renderer,255,255,255,255);
            draw_on_rectangle(texture_block,array_rect[i+j*grid_width],window);
            
        };
       if (grid[i+j*grid_width]==1){
            SDL_SetRenderDrawColor(window->cur_renderer,0,0,255,255);
            SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
        };
        if (grid[i+j*grid_width]==2){
            SDL_SetRenderDrawColor(window->cur_renderer,255,0,0,255);
            SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
        };
            
        };
        //SDL_RenderPresent(window->cur_renderer);
    };
    //SDL_FreeSurface(tmp);
   // SDL_free
    
    
    return 0;
};
*/

int grid_renderer(SDL_Rect* array_rect, map_t* map, window_t* window, int* grid){

    cell_t* grid = map->grid;
    int grid_width = mapGetWidth(map);
    int grid_heigh = mapGetHeight(map);

    for(int i=0;i<grid_height;i++){
        for(int j=0;j<grid_width;j++){

            cell_t cell = grid[i + j*grid_width];
            wall_t wall;
            mapGetWall(&wall, &cell);

            if( wall.wallstate == SOLID )
            {
                SDL_SetRenderDrawColor(window->cur_renderer,0,0,255,255);
                SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);
            }
            else if( wall.wallstate == BRITTLE)
            {
                SDL_SetRenderDrawColor(window->cur_renderer,0,255,0,255);
                SDL_RenderFillRect(window->cur_renderer,&array_rect[i+j*grid_width]);   
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

int player_set_texture(player_t* player,window_t* window,char* filename){
    
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	player->texture_player = IMG_LoadTexture(window->cur_renderer, filename);
    return 0;
};

int draw_player(player_t* player, window_t* window)
{
    //SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h);
    SDL_RenderCopy(window->cur_renderer, player ->texture_player, NULL, &(player->hitbox));
    return 0;
}


SDL_Texture* SDL_texture_init(SDL_Texture* texture, window_t* window, char* filename)
{
    return loadTexture(texture,filename, window);
}

