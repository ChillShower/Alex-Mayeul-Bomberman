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

int reactToKey(player_t* player, map_t* map,window_t* window)
{
	if(player->inputs->right == 1)
	{
		playerGoRight(player,window);
	}

	if(player->inputs->left == 1)
	{
		playerGoLeft(player);
	}

		if(player->inputs->up == 1)
	{
		playerGoUp(player);
	}
		if(player->inputs->down == 1)
	{
		playerGoDown(player);
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
int playerGoRight(player_t* player,window_t* window)
{
	//test_rectangle(window);
    player->x_coord += player->speed;
    return 0;
}

int playerGoLeft(player_t* player)
{
    player->x_coord -= player->speed;
    return 0;
}

int playerGoUp(player_t* player)
{
    player->y_coord -= player->speed;
    return 0;
}

int playerGoDown(player_t* player)
{
    player->y_coord += player->speed;
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


int gridActualisation(player_t* player, map_t* map){
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
                if (explosionIsFinished(cell.explosion))
                {
				//SDL_Delay(10);
				//explosionSetup(cell.bomb, map)

                	explosionDestruction(&map->grid[i+j*grid_width].explosion);
                	map->grid[i+j*grid_width].explosion=NULL;
				
				};
			}
		}
	}
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