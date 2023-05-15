#include "event.h"

void doInput(player_t* player)
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
				doKeyDown(&event.key, player);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key,player);
				break;

			default:
				break;
		}
	}
}

int doKeyDown(SDL_KeyboardEvent *event,player_t* player)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == UP_KEY)
		{
			player->inputs->up = 1;
		}

		if (event->keysym.scancode == DOWN_KEY)
		{
			player->inputs->down = 1;
		}

		if (event->keysym.scancode == LEFT_KEY)
		{
			player->inputs->left = 1;
		}

		if (event->keysym.scancode == RIGHT_KEY)
		{
			player->inputs->right = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			player->inputs->space = 1;
		}
	}
    return 0;
}

int  doKeyUp(SDL_KeyboardEvent *event,player_t* player)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == UP_KEY)
		{
			player->inputs->up = 0;
		}

		if (event->keysym.scancode == DOWN_KEY)
		{
			player->inputs->down = 0;
		}

		if (event->keysym.scancode == LEFT_KEY)
		{
			player->inputs->left = 0;
		}

		if (event->keysym.scancode == RIGHT_KEY)
		{
			player->inputs->right = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			player->inputs->space = 0;
		}
	}
    return 0;
}

int reactToKey(player_t* player, map_t* map,window_t* window, SDL_Texture** texturesList)
{
	if(player->inputs->right == 1)
	{
		playerGoRight(player,window, texturesList);
	}

	if(player->inputs->left == 1)
	{
		playerGoLeft(player,window, texturesList);
	}

		if(player->inputs->up == 1)
	{
		playerGoUp(player,window, texturesList);
	}
		if(player->inputs->down == 1)
	{
		playerGoDown(player,window, texturesList);
	}
		if(player->inputs->space == 1)
	{
		playerPutBomb(player, map,window);
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
int playerGoRight(player_t* player, window_t* window, SDL_Texture** texturesList)
{
	//test_rectangle(window);
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

	if( (0<=player->frame) && (player->frame <=2*PLAYER_FRAME_RATE/3) )
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
	//test_rectangle(window);
    int sizeOfCell;
    mapGetSizeOfCell(&sizeOfCell, map);
    int x_grid ;
    int y_grid ;
	setGridx(player);
	setGridy(player);
	getGridx(&x_grid,player);
	getGridy(&y_grid,player);
    //cell_t* grid = NULL;
    //mapGetGrid(&grid, map);

	int width;
    mapGetWidth(&width, map);
	
	if(map->grid[x_grid + y_grid * width].bomb == NULL)
	{
		//bomb_t* bomb=NULL; //= malloc(sizeof(bomb_t));
    	//bomb->frame=BOMB_FRAME;
		bombInit(&map->grid[x_grid + y_grid * width].bomb,player);
		//if(map->grid[x_grid + y_grid * width].bomb !=NULL){
		//test_rectangle(window);
			//bombDestruction((map->grid[x_grid + y_grid * width].bomb));
			//map->grid[x_grid + y_grid * width].bomb=NULL;
		//};
		//test_rectangle(window);
    	//grid[x_grid + y_grid * width].bomb = &bomb;
		//test_rectangle(window);
	}
    return 0;
}

int gridActualisation(player_t* player, map_t* map, screen_t* screen, window_t* window, SDL_Texture** texturesList){
	wall_t wall;
    cell_t cell;
    int grid_width;
    mapGetWidth(&grid_width, map);

    int grid_height;
    mapGetHeight(&grid_height, map);

    for(int i=0;i<grid_width;i++){
        for(int j=0;j<grid_height;j++){

            cell = map->grid[i + j*grid_width];
            /*mur*/
            cellGetWall(&wall, &cell);
			if (cell.bomb !=NULL){
				bombActualise(cell.bomb);
                //bombDestruction(cell.bomb);
				
                if (isExploded(cell.bomb))
                {
				//SDL_Delay(10);
					//test_rectangle(window);
					explosionSetup(&cell, map);     

					bombDestruction(&map->grid[i+j*grid_width].bomb);
                	map->grid[i+j*grid_width].bomb=NULL;
					//explosionInit(&map->grid[i+j*grid_width].explosion);
					
				
				};
			};
			
			if (cell.explosion !=NULL){
				explosionActualise(cell.explosion);
                //bombDestruction(cell.bomb);
				//test_rectangle(window);
				int xGrid;
				int yGrid;
				getPlayerGridCoordinates(player, screen, map, &xGrid, &yGrid);

                if (explosionIsFinished(cell.explosion))
                {
				//SDL_Delay(10);
				//explosionSetup(cell.bomb, map)

                	explosionDestruction(&map->grid[i+j*grid_width].explosion);
                	map->grid[i+j*grid_width].explosion=NULL;
				
				}
				else if(xGrid == i && yGrid == j){
					playerReactToBomb(player);
				}
				
			}
		}
	}
	playerActualise(player, window, texturesList);
	return 0;
};


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
			/*x_case*/
	//cell_t current_cell_right;
	//wall_t current_wall_right;
	//cell_t current_cell_left;
	//wall_t map->grid[x-i+y*grid_width].wall;

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
			//current_cell_right= map->grid[x+i+y*grid_width];
			//cellGetWall(&current_wall_right,&current_cell_right);
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
			//map->grid[x-i+y*grid_width].cell= map->grid[x-i+y*grid_width];
			//cellGetWall(&map->grid[x-i+y*grid_width].wall,&map->grid[x-i+y*grid_width]);
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
	/*y_case*/
	//cell_t current_cell_up;
	//wall_t current_wall_up;
	//cell_t current_cell_down;
	//wall_t current_wall_down;
	
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
			//map->grid[x+(y+j)*grid_width]= map->grid[x+(y+j)*grid_width];
			//cellGetWall(&map->grid[x+(y+j)*grid_width].wall,&map->grid[x+(y+j)*grid_width]);
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
			//current_cell_down= map->grid[x+(y-j)*grid_width];
			//cellGetWall(&map->grid[x+(y-j)*grid_width].wall,&map->grid[x+(y-j)*grid_width]);
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
	if (map->grid[x + y*map->width].bomb == NULL && map->grid[x + y*map->width].wall->wallstate == EMPTY)
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
	if (map->grid[x + y*map->width].bomb == NULL && map->grid[x + y*map->width].wall->wallstate == EMPTY)
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
	if (map->grid[x + y*map->width].bomb == NULL && map->grid[x + y*map->width].wall->wallstate == EMPTY)
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
	if (map->grid[x + y*map->width].bomb == NULL && map->grid[x + y*map->width].wall->wallstate == EMPTY)
	{
		player->x_coord -= player->speed;
		return 0;
	}

	player->x_coord -= player->speed;

	return 1;
}

int playerReactToBomb(player_t* player)
{
	if(playerIsDead(player))
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

int playerActualise(player_t* player,window_t* window, SDL_Texture** texturesList)
{
	if (player->immuned > 0)
	{
		player->immuned -= 1;
	}

	if(player->frame < 0)
	{
		player->frame = PLAYER_FRAME_RATE;
	}

	if(player->frame > 0)
	{
		player->frame -= 1;
	}
	
	else
	{
		player->frame = PLAYER_FRAME_RATE;
	}

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

	player_rect_actualise(player);


	return 0;
}

int caseOfGameOver(player_t* player)
{
	if( (player->health == -1) && (player->death == 0))
	{
		return 1;
	}
	return 0;
}