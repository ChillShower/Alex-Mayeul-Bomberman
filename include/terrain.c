import "data.c"

enum mur {incassable,cassable,air};

struct case{
    enum mur wall_state; 
    int player;
    int bomb;//chaque valeur représentera la frame de l'animation ca sera plus simple a animé et 0 veut dire pas de bomb
    int explosion;//same

};


