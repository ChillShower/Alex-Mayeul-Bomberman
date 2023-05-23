#include "event.h"

// CONTROLS PARAMETERS:

const int UP_KEY[4] = {SDL_SCANCODE_UP, SDL_SCANCODE_W, SDL_SCANCODE_2, SDL_SCANCODE_7};
const int DOWN_KEY[4] = {SDL_SCANCODE_DOWN,SDL_SCANCODE_S, SDL_SCANCODE_3,SDL_SCANCODE_8};
const int LEFT_KEY[4] = {SDL_SCANCODE_LEFT, SDL_SCANCODE_A, SDL_SCANCODE_1, SDL_SCANCODE_6};
const int RIGHT_KEY[4] = {SDL_SCANCODE_RIGHT,SDL_SCANCODE_D, SDL_SCANCODE_4,SDL_SCANCODE_9};
const int SPACE_KEY[4] = {SDL_SCANCODE_SPACE,SDL_SCANCODE_X, SDL_SCANCODE_5,SDL_SCANCODE_0};

void doInput(player_t* listOfPlayers, int numberOfPlayers, int* pause)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
			
				doKeyDown(&event.key, listOfPlayers, numberOfPlayers);
				break;

			case SDL_KEYUP:
				inPause(&event.key, pause);
				doKeyUp(&event.key,listOfPlayers, numberOfPlayers);
				break;

			default:
				break;
		}
	}
	
}

int inPause(SDL_KeyboardEvent* event, int* pause)
{
	if(event->repeat == 0)
	{
		if(event->keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			if (*pause == 1)
			{
				*pause = 0;
			}
			else if(*pause == 0)
			{
				*pause =1;
			}
		}
	}
	return 0;
	
}

void doMouse(SDL_Rect* listOfButtons, buttonstate_t** listOfReactions, int numberOfButtons)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				
				clickOnButton(listOfButtons, listOfReactions,&event, numberOfButtons);
				break;

			default:

				mouseOnButton(listOfButtons,listOfReactions, &event, numberOfButtons);
				break;
		}
	}
	
}

int mouseOnButton(SDL_Rect* listOfButtons, buttonstate_t** listOfReactions, SDL_Event* event, int numberOfButtons)
{
	for(int i = 0; i< numberOfButtons; ++i)
	{
	int xPos = listOfButtons[i].x;
    int yPos = listOfButtons[i].y;
    int width = listOfButtons[i].w;
    int height= listOfButtons[i].h;

	if ((xPos <= event->button.x &&event->button.x <= xPos + width) && (yPos <= event->button.y &&event->button.y <= yPos + height))
	{
		*listOfReactions[i] = ON;
	}
	else
	{
		*listOfReactions[i] = NONE;
	}
	}
	return 0;
}

int clickOnButton(SDL_Rect* listOfButtons,buttonstate_t** listOfReactions, SDL_Event* event, int numberOfButtons)
{
	for(int i = 0; i< numberOfButtons; ++i)
	{
	int xPos = listOfButtons[i].x;
    int yPos = listOfButtons[i].y;
    int width = listOfButtons[i].w;
    int height= listOfButtons[i].h;

	if ((xPos <= event->button.x &&event->button.x <= xPos + width) && (yPos <= event->button.y &&event->button.y <= yPos + height))
	{
		*listOfReactions[i] = CLICKED;
		return 1;
	}
	}
	return 0;
}

int colorReactionToMouse(buttonstate_t reaction,SDL_Color* color)
{
	if(reaction == CLICKED)
    {
        color->r = 255;
        color->g = 0;
        color->b = 0;
       	color->a = 255;
    }
    if(reaction == ON)
    {
        color->r = 0;
        color->g = 0;
        color->b = 255;
        color->a = 255;
    }
    if(reaction == NONE)
    {
       	color->r = 255;
        color->g = 255;
        color->b = 255;
        color->a = 255;
    }
	return 0;
}

int doKeyDown(SDL_KeyboardEvent *event,player_t* listOfPlayers, int numberOfPlayers)
{
	
	if (event->repeat == 0)
	{
		for(int i = 0; i<numberOfPlayers; ++i)
		{
		if (event->keysym.scancode == UP_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->up = 1;
		}

		if (event->keysym.scancode == DOWN_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->down = 1;
		}

		if (event->keysym.scancode == LEFT_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->left = 1;
		}

		if (event->keysym.scancode == RIGHT_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->right = 1;
		}

		if (event->keysym.scancode == SPACE_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->space = 1;
		}
		}
	}
    return 0;
}

int  doKeyUp(SDL_KeyboardEvent *event,player_t* listOfPlayers, int numberOfPlayers)
{
	if (event->repeat == 0)
	{
		for(int i = 0; i<numberOfPlayers; ++i)
		{
		if (event->keysym.scancode == UP_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->up = 0;
		}

		if (event->keysym.scancode == DOWN_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->down = 0;
		}

		if (event->keysym.scancode == LEFT_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->left = 0;
		}

		if (event->keysym.scancode == RIGHT_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->right = 0;
		}

		if (event->keysym.scancode == SPACE_KEY[listOfPlayers[i].id])
		{
			listOfPlayers[i].inputs->space = 0;
		}
		}
	}
    return 0;
}

int reactToKey(player_t* player, map_t* map,window_t* window,screen_t* screen, SDL_Texture** texturesList, int* lastKey)
{
	if(playerPushRight(player) && !(smthgIsRight(player, map, screen)))
	{
		playerGoRight(player,window, texturesList);
		*lastKey = RIGHT_KEY[player->id];
	}

	if(playerPushLeft(player) && !(smthgIsLeft(player, map, screen)))
	{
		playerGoLeft(player,window, texturesList);
		*lastKey = LEFT_KEY[player->id];
	}

	if(playerPushUp(player) && !(smthgIsUp(player, map, screen)))
	{
		playerGoUp(player,window, texturesList);
		*lastKey = UP_KEY[player->id];
	}
	if(playerPushDown(player) && !(smthgIsDown(player, map, screen)))
	{
		playerGoDown(player,window, texturesList);
		*lastKey = DOWN_KEY[player->id];
	}
	if(playerPushBomb(player))
	{
		playerPutBomb(player, map,window);
		*lastKey = SPACE_KEY[player->id];
	}

	return 0;
}

int returnToRestPose(player_t* player, int lastKey, SDL_Texture** texturesList)
{
	if(lastKey == RIGHT_KEY[player->id])
	{
		player_set_texture(player, texturesList[6]);
	}
	if(lastKey == LEFT_KEY[player->id])
	{
		player_set_texture(player, texturesList[5]);
	}
	if(lastKey == UP_KEY[player->id])
	{
		player_set_texture(player, texturesList[9]);
	}
	if(lastKey == DOWN_KEY[player->id])
	{
		player_set_texture(player, texturesList[0]);
	}

	return 0;
}

int prepareScene(window_t* window)
{
	SDL_SetRenderDrawColor(window->cur_renderer, 96, 128, 255, 255);
	SDL_RenderClear(window->cur_renderer);
    return 0;
}
int presentScene(window_t* window)
{
	SDL_RenderPresent(window->cur_renderer);
	return 0;
}


void showEscapeMenu(window_t* window, screen_t* screen, SDL_Texture** texturesList, TTF_Font* police)
{
    char* textPause = "PAUSE";
    int width = screen->width/4;
    int height = screen->height/4;
    int xPos = screen->width/2 - width/2;
    int yPos = 1*screen->height/3;
    SDL_Rect buttonPause;
    buttonPause.x =xPos;
    buttonPause.y = yPos;
    buttonPause.w = width;
    buttonPause.h = height;

    SDL_Color colorPause = {255, 255, 255, 255};

    showButton(window, screen, texturesList, &buttonPause, police, textPause, colorPause);

    SDL_RenderPresent(window->cur_renderer);
    SDL_Delay(10);
}
int playerGoRight(player_t* player, window_t* window, SDL_Texture** texturesList)
{
    player->x_coord += player->speed;
	if( (2*PLAYER_FRAME_RATE/3 < player->frame) && (player->frame <=PLAYER_FRAME_RATE))
	{
		player_set_texture(player, texturesList[6]);
	}
	if( (PLAYER_FRAME_RATE/3< player->frame) && (player->frame <=2*PLAYER_FRAME_RATE/3) )
	{
		player_set_texture(player, texturesList[7]);
	}

	if( (0<=player->frame) && (player->frame <=2*PLAYER_FRAME_RATE/3) )
	{
		player_set_texture(player, texturesList[8]);
	}
	
    return 0;
}

int playerGoLeft(player_t* player, window_t* window, SDL_Texture** texturesList)
{
    player->x_coord -= player->speed;
	if( (2*PLAYER_FRAME_RATE/3 < player->frame) && (player->frame <=PLAYER_FRAME_RATE))
	{
		player_set_texture(player, texturesList[3]);
	}
	if( (PLAYER_FRAME_RATE/3< player->frame) && (player->frame <=2*PLAYER_FRAME_RATE/3) )
	{
		player_set_texture(player, texturesList[4]);
	}

	if( (0<=player->frame) && (player->frame <=2*PLAYER_FRAME_RATE/3) )
	{
		player_set_texture(player, texturesList[5]);
	}
	
	
    return 0;
}

int playerGoUp(player_t* player, window_t* window, SDL_Texture** texturesList)
{
    player->y_coord -= player->speed;
	
	if( (2*PLAYER_FRAME_RATE/3 < player->frame) && (player->frame <=PLAYER_FRAME_RATE))
	{
		player_set_texture(player, texturesList[9]);
	}
	if( (PLAYER_FRAME_RATE/3< player->frame) && (player->frame <=2*PLAYER_FRAME_RATE/3) )
	{
		player_set_texture(player, texturesList[10]);
	}

	if( (0<=player->frame) && (player->frame <=PLAYER_FRAME_RATE/3) )
	{
		player_set_texture(player, texturesList[11]);
	}
	
    return 0;
}

int playerGoDown(player_t* player, window_t* window, SDL_Texture** texturesList)
{
    player->y_coord += player->speed;
	if( (2*PLAYER_FRAME_RATE/3 < player->frame) && (player->frame <=PLAYER_FRAME_RATE))
	{
		player_set_texture(player, texturesList[0]);
	}
	if( (PLAYER_FRAME_RATE/3< player->frame) && (player->frame <=2*PLAYER_FRAME_RATE/3) )
	{
		player_set_texture(player, texturesList[1]);
	}

	if( (0<=player->frame) && (player->frame <=2*PLAYER_FRAME_RATE/3) )
	{
		player_set_texture(player, texturesList[2]);
	}
	
    return 0;
}

int playerPutBomb(player_t* player, map_t* map,window_t* window)
{
    int sizeOfCell;
    mapGetSizeOfCell(&sizeOfCell, map);
    int x_grid ;
    int y_grid ;
	setGridx(player);
	setGridy(player);
	getGridx(&x_grid,player);
	getGridy(&y_grid,player);

	int width;
    mapGetWidth(&width, map);
	
	if(map->grid[x_grid + y_grid * width].bomb == NULL)
	{
		bombInit(&map->grid[x_grid + y_grid * width].bomb,player);
	}
    return 0;
}

int gridActualisation(map_t* map, screen_t* screen, window_t* window, SDL_Texture** texturesList){
	wall_t wall;
    cell_t cell;
    int grid_width;
    mapGetWidth(&grid_width, map);

    int grid_height;
    mapGetHeight(&grid_height, map);

    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_height;j++){

            cell = map->grid[i + j*grid_width];
            cellGetWall(&wall, &cell);
			if (cell.bomb !=NULL){
				bombActualise(cell.bomb);

				
                if (isExploded(cell.bomb))
                {
					explosionSetup(&cell, map);     

					bombDestruction(&map->grid[i+j*grid_width].bomb);
                	map->grid[i+j*grid_width].bomb=NULL;
					
				
				};
			};
			
			if (cell.explosion !=NULL){
				explosionActualise(cell.explosion);

                if (explosionIsFinished(cell.explosion))
                {
                	explosionDestruction(&map->grid[i+j*grid_width].explosion);
                	map->grid[i+j*grid_width].explosion=NULL;
				
				
			}
			}
		}
	}
	return 0;
};

int playerReactToStar(player_t* player, cell_t* cell)
{
	player->x_strength += 1;
	player->y_strength += 1;

	cell->wall->wallstate = EMPTY;

	return 0;
}


int explosionSetup(cell_t* cell, map_t* map){
	int x =cell->x_coord;
	int y =cell->y_coord;
	int x_power;
	int y_power;
	getBombX_strength(&x_power,cell->bomb);
	getBombY_strength(&y_power,cell->bomb);
	int grid_width;
	mapGetWidth(&grid_width, map);
	explosionInit((&map->grid[x+y*grid_width].explosion));
   int grid_height;

    mapGetHeight(&grid_height, map);
	int condition_droite=0;
	int condition_gauche=0;
	for (int i=1;i<x_power+1;i++){

		if(x+i>=grid_width){
			condition_droite=1;
		}
		
		if(x-i<0){
			condition_gauche=1;
		};
		if (condition_droite==0){
			if (map->grid[x+i+y*grid_width].wall->wallstate==SOLID){
				condition_droite=1;
			}
			if (map->grid[x+i+y*grid_width].wall->wallstate ==BRITTLE){
				map->grid[x+i+y*grid_width].wall->wallstate=EMPTY;
			};
			if (map->grid[x+i+y*grid_width].bomb !=NULL){
				map->grid[x+i+y*grid_width].bomb->frame=0;
			};
			if (map->grid[x+i+y*grid_width].explosion !=NULL){
				map->grid[x+i+y*grid_width].explosion->frame=EXPLOSION_FRAME;
			};
			if (map->grid[x+i+y*grid_width].explosion ==NULL && condition_droite==0){
				explosionInit(&map->grid[x+i+y*grid_width].explosion);
				map->grid[x+i+y*grid_width].explosion->frame=EXPLOSION_FRAME;
				
			};					
		}
		
	
		
		if (condition_gauche==0){
			if (map->grid[x-i+y*grid_width].wall-> wallstate==SOLID){
				condition_gauche=1;
			}
			if (map->grid[x-i+y*grid_width].wall->wallstate ==BRITTLE){
			map->grid[x-i+y*grid_width].wall->wallstate=EMPTY;
			};
			if (map->grid[x-i+y*grid_width].bomb !=NULL){
				map->grid[x-i+y*grid_width].bomb->frame=0;
			};
			if (map->grid[x-i+y*grid_width].explosion !=NULL){
				map->grid[x-i+y*grid_width].explosion->frame=EXPLOSION_FRAME;
			};
			if (map->grid[x-i+y*grid_width].explosion ==NULL && condition_gauche==0){
				explosionInit(&map->grid[x-i+y*grid_width].explosion);
				map->grid[x-i+y*grid_width].explosion->frame=EXPLOSION_FRAME;
			};					
		};
		
	};

	int condition_haut=0;
	int condition_bas=0;
	for (int j=1;j<y_power+1;j++){

		if(y+j>=grid_height){
			condition_haut=1;
		}
		
		if(y-j<0){
			condition_bas=1;
		};
		if (condition_haut==0){
			if (map->grid[x+(y+j)*grid_width].wall->wallstate==SOLID){
				condition_haut=1;
			}
			if (map->grid[x+(y+j)*grid_width].wall->wallstate ==BRITTLE){
				map->grid[x+(y+j)*grid_width].wall->wallstate=EMPTY;
			};
			if (map->grid[x+(y+j)*grid_width].bomb !=NULL){
				map->grid[x+(y+j)*grid_width].bomb->frame=0;
			};
			if (map->grid[x+(y+j)*grid_width].explosion !=NULL){
				map->grid[x+(y+j)*grid_width].explosion->frame=EXPLOSION_FRAME;
			};
			if (map->grid[x+(y+j)*grid_width].explosion ==NULL && condition_haut==0){
				explosionInit(&map->grid[x+(y+j)*grid_width].explosion);
				map->grid[x+(y+j)*grid_width].explosion->frame=EXPLOSION_FRAME;
			};					
		}
		if (condition_bas==0){
			if (map->grid[x+(y-j)*grid_width].wall->wallstate==SOLID){
				condition_bas=1;
			}
			if (map->grid[x+(y-j)*grid_width].wall->wallstate ==BRITTLE){
				map->grid[x+(y-j)*grid_width].wall->wallstate=EMPTY;
			};
			if (map->grid[x+(y-j)*grid_width].bomb !=NULL){
				map->grid[x+(y-j)*grid_width].bomb->frame=0;
			};
			if (map->grid[x+(y-j)*grid_width].explosion !=NULL){
				map->grid[x+(y-j)*grid_width].explosion->frame=EXPLOSION_FRAME;
			};
			if (map->grid[x+(y-j)*grid_width].explosion ==NULL && condition_bas==0){
				explosionInit(&map->grid[x+(y-j)*grid_width].explosion);
				map->grid[x+(y-j)*grid_width].explosion->frame=EXPLOSION_FRAME;
			};					
		};
		
	};
	
	return 0;
}
int smthgIsUp(player_t* player, map_t* map, screen_t* screen)
{

	// On gère en premier le cas particulier de si le joueur n'a pas changé de case.
	int xBefore;
	int yBefore;
	getPlayerGridCoordinates(player, screen, map,&xBefore, &yBefore);

	player->y_coord -= player->speed;

	int x;
	int y;
	getPlayerGridCoordinates(player, screen, map,&x, &y);

	if(xBefore == x && yBefore == y && IsPlayerInMap(player, screen, map))
	{
		return 0;
	}

	if(!(IsPlayerInMap(player, screen, map)))
	{
		player->y_coord += player->speed;
		return 1;
	}
	if ((map->grid[x + y*map->width].bomb == NULL) && (!(map->grid[x + y*map->width].wall->wallstate == SOLID ) && !(map->grid[x + y*map->width].wall->wallstate == BRITTLE )))
	{
		player->y_coord += player->speed;
		return 0;
	}

	player->y_coord += player->speed;

	return 1;
}
int smthgIsDown(player_t* player, map_t* map, screen_t* screen)
{

	// On gère en premier le cas particulier de si le joueur n'a pas changé de case.
	int xBefore;
	int yBefore;
	getPlayerGridCoordinates(player, screen, map,&xBefore, &yBefore);

	player->y_coord += player->speed;

	int x;
	int y;

	getPlayerGridCoordinates(player, screen, map,&x, &y);

	if(xBefore == x && yBefore == y && IsPlayerInMap(player, screen, map))
	{
		return 0;
	}

	if(!(IsPlayerInMap(player, screen, map)))
	{
		player->y_coord -= player->speed;
		return 1;
	}
	if ((map->grid[x + y*map->width].bomb == NULL) && (!(map->grid[x + y*map->width].wall->wallstate == SOLID ) && !(map->grid[x + y*map->width].wall->wallstate == BRITTLE )))
	{
		player->y_coord -= player->speed;
		return 0;
	}

	player->y_coord -= player->speed;

	return 1;
}
int smthgIsLeft(player_t* player, map_t* map, screen_t* screen)
{


	// On gère en premier le cas particulier de si le joueur n'a pas changé de case.
	int xBefore;
	int yBefore;
	getPlayerGridCoordinates(player, screen, map,&xBefore, &yBefore);

	player->x_coord -= player->speed;

	int x;
	int y;

	getPlayerGridCoordinates(player, screen, map,&x, &y);

	if(xBefore == x && yBefore == y && IsPlayerInMap(player, screen, map))
	{
		return 0;
	}

	if(!(IsPlayerInMap(player, screen, map)))
	{
		player->x_coord += player->speed;
		return 1;
	}
	if ((map->grid[x + y*map->width].bomb == NULL) && (!(map->grid[x + y*map->width].wall->wallstate == SOLID ) && !(map->grid[x + y*map->width].wall->wallstate == BRITTLE )))
	{
		player->x_coord += player->speed;
		return 0;
	}

	player->x_coord += player->speed;

	return 1;
}
int smthgIsRight(player_t* player, map_t* map, screen_t* screen)
{


	// On gère en premier le cas particulier de si le joueur n'a pas changé de case.
	int xBefore;
	int yBefore;
	getPlayerGridCoordinates(player, screen, map,&xBefore, &yBefore);

	player->x_coord += player->speed;

	int x;
	int y;

	getPlayerGridCoordinates(player, screen, map,&x, &y);

	if(xBefore == x && yBefore == y && IsPlayerInMap(player, screen, map))
	{
		return 0;
	}

	if(!(IsPlayerInMap(player, screen, map)))
	{
		player->x_coord -= player->speed;
		return 1;
	}
	if ((map->grid[x + y*map->width].bomb == NULL) && (!(map->grid[x + y*map->width].wall->wallstate == SOLID ) && !(map->grid[x + y*map->width].wall->wallstate == BRITTLE )))
	{
		player->x_coord -= player->speed;
		return 0;
	}

	player->x_coord -= player->speed;

	return 1;
}

int playerReactToBomb(player_t* player)
{
	if(player->health <= 0)
	{
		return 0;
	}
	else if (player->immuned > 0)
	{
		return 0;
	}
	else{
		player->health -= 1;
		player->immuned = DEFAULT_IMMUNED;
		return 0;
	}
}

int playerActualise(player_t* player, map_t* map, screen_t* screen, window_t* window, SDL_Texture** texturesList)
{
	cell_t cell;
	int grid_width;
    mapGetWidth(&grid_width, map);

    int grid_height;
    mapGetHeight(&grid_height, map);

    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_height;j++){
			cell = map->grid[i + j*grid_width];

			if (cell.explosion !=NULL){
				int xGrid;
				int yGrid;
				getPlayerGridCoordinates(player, screen, map, &xGrid, &yGrid);
				if(xGrid == i && yGrid == j){
					playerReactToBomb(player);
				}
			}

			if (cell.wall->wallstate == STAR)
			{
				int xGrid;
				int yGrid;
				getPlayerGridCoordinates(player, screen, map, &xGrid, &yGrid);
				if(xGrid == i && yGrid == j){
					playerReactToStar(player, &map->grid[i+j*grid_width]);
				}
			}

		}
	}

	if (player->immuned > 0)
	{
		player->immuned -= 1;
	}

	if(player->frame <= 0)
	{
		player->frame = PLAYER_FRAME_RATE;
	}
	else
	{
		player->frame -= 1;
	}
	

	/* ANIMATION IMMUNE:*/

	if( (5*DEFAULT_IMMUNED/6 < player->immuned) && (player->immuned <=DEFAULT_IMMUNED))
	{
		SDL_SetTextureAlphaMod(player->texture_player, 0);
	}

	if( (4*DEFAULT_IMMUNED/6 < player->immuned) && (player->immuned <=5*DEFAULT_IMMUNED/6))
	{
		SDL_SetTextureAlphaMod(player->texture_player, 255);
	}

	if( (3*DEFAULT_IMMUNED/6 < player->immuned) && (player->immuned <=4*DEFAULT_IMMUNED/6))
	{
		SDL_SetTextureAlphaMod(player->texture_player, 0);
	}

	if( (2*DEFAULT_IMMUNED/6 < player->immuned) && (player->immuned <=3*DEFAULT_IMMUNED/6))
	{
		SDL_SetTextureAlphaMod(player->texture_player, 255);
	}

	if( (1*DEFAULT_IMMUNED/6 < player->immuned) && (player->immuned <=2*DEFAULT_IMMUNED/6))
	{
		SDL_SetTextureAlphaMod(player->texture_player, 0);
	}

	if( (0 < player->immuned) && (player->immuned <=1*DEFAULT_IMMUNED/6))
	{
		SDL_SetTextureAlphaMod(player->texture_player, 255);
	}

	/* FIN */

	if(player->immuned == 0)
	{
		SDL_SetTextureAlphaMod(player->texture_player, 255);
	}

	if(playerIsDead(player))
	{
		player->death = DEFAULT_DEATH;
		player->health = -1; // le joueur est en train de mourir
	}

	if( (2*DEFAULT_DEATH/3 < player->death) && (player->death <= DEFAULT_DEATH))
	{
		player_set_texture(player, texturesList[23]);
	}

	if( (1*DEFAULT_DEATH/3 < player->death) && (player->death <= 2*DEFAULT_DEATH))
	{
		player_set_texture(player, texturesList[24]);
	}

	if( (0< player->death) && (player->death <= DEFAULT_DEATH/3))
	{
		player_set_texture(player, texturesList[25]);
	}

	if(player->death > 0)
	{
		player->death -= 1;
	}

	if(player->death == 0 && player->health == -1)
	{
		player_set_texture(player, texturesList[25]);
	}
	player_rect_actualise(player);


	return 0;
}

int caseOfGameOver(player_t* player, int numberOfPlayers)
{
	int numberOfDeaths= 0;
	for(int i = 0; i<numberOfPlayers; ++i)
	{
		if( (player[i].health == -1) && (player[i].death == 0))
		{
			numberOfDeaths += 1;
		}
	}
	
	return numberOfDeaths == numberOfPlayers - 1;
}