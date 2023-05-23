#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
#include "instance.h"
#include "renderer.h"

int connectionToServer(int* client_fd){
    int status;
    struct sockaddr_in serv_addr;
    //char* hello = "Hello from client";
    //char buffer[1024] = { 0 };
    if ((*client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if ((status
         = connect(*client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    return 0;
}


int sendToServer(player_t* player,int* input,int* client_fd){
    input[0]=player->id;
    input[1]=player->inputs->up;
    input[2]=player->inputs->down;
    input[3]=player->inputs->left;
    input[4]=player->inputs->right;
    input[5]=player->inputs->space;

    return send(*client_fd,input,sizeof(int)*6,0);
}

int receiveFromServer(int* client_fd,int* data){
    data= malloc(sizeof(int)*1024);
    ssize_t bytes_read = read(*client_fd, data, 1024);
    if (bytes_read == -1) {
        perror("read() error");
        return -1;
    }
    data[bytes_read] = '\0';
    return 0;
}
  
int treatData(player_t* player,map_t* map,int* data){


    /*a faire*/

    free(data);
    data=NULL;
    return 0;
}


int main(int argc, char const* argv[])
{
    int client_fd;
    int send_read;
    //int receive_read;
    if (connectionToServer(&client_fd)!=0){
        return -1; 
    }
        screen_t screen;
    initScreen(&screen);

    window_t window;
   initWindow(&screen, &window);

   // SDL_Rect rectArray[DEFAULT_MAP_WIDTH*DEFAULT_MAP_HEIGHT];
  //  grid_init(&screen, rectArray, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, DEFAULT_SIZE_OF_CELL);

    map_t map;
    mapInit(&map);
    generateMap(0.85,0.05, &map);
    int NUMBER_PLAYER=2;
    int pause =0;
    SDL_Texture* texturesList[60];
    texturesListInit(texturesList, &window);
    player_t listPlayers[NUMBER_PLAYER];
    for (int i=0;i<NUMBER_PLAYER;i++){
         playerInit(&listPlayers[i],i, &map, &screen,texturesList);
    }
   // player_set_texture(&player,&window,"resources/animations/characters/bomberman/bas_1.png");
    int* input = malloc(sizeof(int)*6);
   // int* data=NULL;
    while (1)
    {
        //prepareScene(&window);
        doInput(listPlayers,NUMBER_PLAYER,&pause);     
        send_read=sendToServer(&listPlayers[1],input,&client_fd);


        if (send_read>=0){
        //draw_player(&player, &window);
        //player_rect_actualise(&player);
        
        };
        /*
        if treatData(player_t* player))
        gridActualisation(&player,&map);
        grid_renderer(rectArray, &map, &window);
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);
        
        SDL_RenderPresent( window.cur_renderer);
        
        SDL_Delay(10);
        */
    }
    
    mapDestruction(&map);

    //return EXIT_SUCCESS;

    //send(client_fd, hello, strlen(hello), 0);
    //printf("Hello message sent\n");
    //valread = read(client_fd, buffer, 1024);
    //printf("%s\n", buffer);
  
    // closing the connected socket
    free(input);
    close(client_fd);
    return EXIT_SUCCESS;
    return 0;
}