#ifndef PARAM_H
#define PARAM_H

// SCREEN PARAMETERS:
#define FRAME_RATE 60
#define DEFAULT_SCREEN_WIDTH 1920
#define DEFAULT_SCREEN_HEIGHT 1080

// GAME PARAMETERS:

#define DEFAULT_SIZE_OF_CELL 100
#define DEFAULT_MAP_WIDTH 11//(DEFAULT_SCREEN_WIDTH/DEFAULT_SIZE_OF_CELL)
#define DEFAULT_MAP_HEIGHT 11//(DEFAULT_SCREEN_HEIGHT/DEFAULT_SIZE_OF_CELL)

// PLAYER PARAMETERS:
#define PLAYER_SPEED_FRAME_RATE 2
#define PLAYER_FRAME_RATE (FRAME_RATE/PLAYER_SPEED_FRAME_RATE)
#define DEFAULT_IMMUNED (BOMB_FRAME)
#define DEFAULT_DEATH 60
/*int x_fake_origin= DEFAULT_SCREEN_WIDTH/2-DEFAULT_SIZE_OF_CELL*DEFAULT_MAP_WIDTH/2;
int y_fake_origin= DEFAULT_SCREEN_HEIGHT/2-DEFAULT_SIZE_OF_CELL*DEFAULT_MAP_HEIGHT/2;
#define DEFAULT_X_GRID_ORIGIN x_fake_origin
#define DEFAULT_Y_GRID_ORIGIN y_fake_origin*/
#endif