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