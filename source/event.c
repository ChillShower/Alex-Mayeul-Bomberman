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

		if (event->keysym.scancode == SPACE_KEY)
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

		if (event->keysym.scancode == SPACE_KEY)
		{
			player->inputs->space = 0;
		}
	}
    return 0;
}

int reactToKey(player_t* player, map_t* map)
{
	if(player->inputs->right == 1)
	{
		playerGoRight(player);
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
		playerPutBomb(player, map);
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
int playerGoRight(player_t* player)
{
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

int playerPutBomb(player_t* player, map_t* map)
{
    int sizeOfCell;
    mapGetSizeOfCell(&sizeOfCell, map);
    int x_grid = (int) ( (double) player->x_coord /  (double) sizeOfCell );
    int y_grid = (int) ( (double) player->y_coord / (double) sizeOfCell );

    cell_t* grid = NULL;
    mapGetGrid(grid, map);

	int width;
    mapGetWidth(&width, map);

	if(grid[x_grid + y_grid * width].bomb == NULL)
	{

    	bomb_t* bomb = malloc(sizeof(bomb_t));
    	bomb->frame = BOMB_FRAME;

    	grid[x_grid + y_grid * width].bomb = bomb;
	}

    return 0;
}