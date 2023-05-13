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
		bombInit(&map->grid[x_grid + y_grid * width].bomb);
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
                bombDestruction(&map->grid[i+j*grid_width].bomb);
                map->grid[i+j*grid_width].bomb=NULL;
				};
			}
		}
	}
	return 0;
};