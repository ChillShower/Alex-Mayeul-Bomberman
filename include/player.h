

typedef struct player{
    float x_coord;
    float y_coord;
    int health;
}player_t;

//init

//coord
float getCoordx(player_t* player);

float getCoordy(player_t* player);

int setCoordx(player_t* player,float x);

int setCoordy(player_t* player,float y);

//health
int getHealth(player_t* player);

int setHealth(player_t* player, int new_health);

int  healthSubstract(player_t* player, int substract);

int healthAdd(player_t* player, int add);

//case
int getCasex(player_t* player);

int getCasey(player_t* player);


