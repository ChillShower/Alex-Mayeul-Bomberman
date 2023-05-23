#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include "instance.h"
#include "renderer.h"

#define TRUE   1 
#define FALSE  0 
#define PORT 8080 
/*
int setServer(int* client_socket,int nb_joueur,int* master_socket,int* addrlen,struct sockaddr_in *address){
    int opt = TRUE;  
    int max_clients = nb_joueur , i;  
      
    //struct sockaddr_in address;  
         
   // char buffer[1025];  //data buffer of 1K 
         
    //set of socket descriptors 
     
         
    //a message 
     
     
    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  
         
    //create a master socket 
    if( (*master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(*master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
     
    //type of socket created 
    address->sin_family = AF_INET;  
    address->sin_addr.s_addr = INADDR_ANY;  
    address->sin_port = htons( PORT );  
         
    //bind the socket to localhost port 8888 
    if (bind(*master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(*master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    *addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
         
   
    
         
    return 0;  
}

int receiveFromClient(int* master_socket,int* client_socket,int max_clients,player_t* playerLists,int addrlen,struct sockaddr_in address){
        int new_socket;
        int activity;
        int sd;
        int max_sd;
        //char *message = "ECHO Daemon v1.0 \r\n"; 
        fd_set readfds;
        int buffer[6]; 
        int valread;
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(*master_socket, &readfds);  
        max_sd = *master_socket;  
             
        //add child sockets to set 
        for (int i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(*master_socket, &readfds))  
        {  
            if ((new_socket = accept(*master_socket, 
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
                  (address.sin_port));  
           
            //send new connection greeting message
            /* 
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )  
            {  
                perror("send");  
            } */ 
            /*
                 
           // puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            for (int i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }  
            }  
        }  
             
        //else its some IO operation on some other socket
        
        for (int i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
                 
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((valread = read( sd , buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }  
                     
                //Echo back the message that came in 
                
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';  
                    //send(sd , buffer , strlen(buffer) , 0 );
                    playerLists[buffer[0]].inputs->up=buffer[1];
                    playerLists[buffer[0]].inputs->down=buffer[2];
                    playerLists[buffer[0]].inputs->left=buffer[3];
                    playerLists[buffer[0]].inputs->right=buffer[4];
                    playerLists[buffer[0]].inputs->space=buffer[5];
                } 
                 
            }  
        }  
        

    return 0;
}
int sendToClient(int* data,int* client_socket,int nb_joueur,int size_data){
    for (int i=0;i<nb_joueur;i++){
        send(client_socket[i] , data , size_data , 0 );
    }
    
    return 0;
}


int main(int argc, char const* argv[])
{
    screen_t screen;
    initScreen(&screen);

    window_t window;
    initWindow(&screen, &window);

    SDL_Rect rectArray[DEFAULT_MAP_WIDTH*DEFAULT_MAP_HEIGHT];
    grid_init(&screen, rectArray, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, DEFAULT_SIZE_OF_CELL);

    map_t map;
    mapInit(&map);
    generateMap(0.85, &map);

    //SDL_Texture* texturesList[60];
    //texturesListInit(texturesList, &window);

    int const NUMBER_OF_PLAYERS = 2;
    player_t listOfPlayers[NUMBER_OF_PLAYERS];
    
    for(int i = 0; i<NUMBER_OF_PLAYERS; ++i)
    {
        playerInit(&listOfPlayers[i], &map, &screen,i);
    }
    /*client*/
    /*
    int master_socket;
    int client_socket[NUMBER_OF_PLAYERS];
    int addrlen;
    struct sockaddr_in adress;
    setServer(client_socket,NUMBER_OF_PLAYERS,&master_socket,&addrlen,&adress);

    while (1){
        receiveFromClient(&master_socket,client_socket,NUMBER_OF_PLAYERS,listOfPlayers,addrlen,adress);
        prepareScene(&window);
        for (int i=0;i<NUMBER_OF_PLAYERS;i++){
        if (playerPushUp(&listOfPlayers[i]) && !(smthgIsUp(&listOfPlayers[i], &map, &screen)))
		{

            int x;
	        int y;

	        getPlayerGridCoordinates(&listOfPlayers[i], &screen, &map,&x, &y);
            printf("%d, %d \n", x, y);

            printf("%d, %d\n", listOfPlayers[i].x_coord, listOfPlayers[i].y_coord);
            printf("frame:%d\n", listOfPlayers[i].frame);
        
			playerGoUp(&listOfPlayers[i], &window);
		}

		if (playerPushDown(&listOfPlayers[i]) && !(smthgIsDown(&listOfPlayers[i], &map, &screen)))
		{
            
			playerGoDown(&listOfPlayers[i], &window);
		}

		if (playerPushLeft(&listOfPlayers[i]) && !(smthgIsLeft(&listOfPlayers[i], &map, &screen)))
		{
            
			playerGoLeft(&listOfPlayers[i], &window);
		}

		if (playerPushRight(&listOfPlayers[i]) && !(smthgIsRight(&listOfPlayers[i], &map, &screen)))
		{
            
			playerGoRight(&listOfPlayers[i], &window);
		}

        if (playerPushBomb(&listOfPlayers[i]))
        {
            playerPutBomb(&listOfPlayers[i], &map,&window);
        }

        player_rect_actualise(&listOfPlayers[i]);
        gridActualisation(&listOfPlayers[i],&map);
        draw_player(&listOfPlayers[i], &window);
    }
        grid_renderer(rectArray, &map, &window);
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);
    // closing the listening socket
    //shutdown(server_fd, SHUT_RDWR);
        SDL_RenderPresent( window.cur_renderer);

    }
    return 0;
}
*/

int main(int argc, char const* argv[])
{
    screen_t screen;
    initScreen(&screen);

    window_t window;
    initWindow(&screen, &window);

    SDL_Rect rectArray[DEFAULT_MAP_WIDTH*DEFAULT_MAP_HEIGHT];
    grid_init(&screen, rectArray, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, DEFAULT_SIZE_OF_CELL);

    map_t map;
    mapInit(&map);
    generateMap(0.85,0.05, &map);

    SDL_Texture* texturesList[60];
    texturesListInit(texturesList, &window);

    int const NUMBER_OF_PLAYERS = 2;
    player_t listOfPlayers[NUMBER_OF_PLAYERS];
    
    for(int i = 0; i<NUMBER_OF_PLAYERS; ++i)
    {
        playerInit(&listOfPlayers[i],i, &map, &screen,texturesList);
    }
    TTF_Font* police = NULL;
    police = TTF_OpenFont("resources/fonts/lunchtime-doubly-so.regular.ttf", 12);
    if(police == 0)
    {
        printf("Probleme de lecture du fichier font..\n");
    }

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int buffer[1024];
    //char* hello = "Hello from server";
  
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
  
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
/*
    while(1){
        valread = read(new_socket, buffer, 1024);
        buffer[valread] = '\0';  
    //send(sd , buffer , strlen(buffer) , 0 );
        listOfPlayers[buffer[0]].inputs->up=buffer[1];
        listOfPlayers[buffer[0]].inputs->down=buffer[2];
        listOfPlayers[buffer[0]].inputs->left=buffer[3];
        listOfPlayers[buffer[0]].inputs->right=buffer[4];
        listOfPlayers[buffer[0]].inputs->space=buffer[5];
    //printf("%s\n", buffer);
   // send(new_socket, hello, strlen(hello), 0);
 //   printf("Hello message sent\n");
        
        prepareScene(&window);
        
        doInput(&listOfPlayers[0]);
    for (int i=0;i<NUMBER_OF_PLAYERS;i++){
        if (playerPushUp(&listOfPlayers[i]) && !(smthgIsUp(&listOfPlayers[i], &map, &screen)))
		{

            int x;
	        int y;

	        getPlayerGridCoordinates(&listOfPlayers[i], &screen, &map,&x, &y);
            printf("%d, %d \n", x, y);

            printf("%d, %d\n", listOfPlayers[i].x_coord, listOfPlayers[i].y_coord);
            printf("frame:%d\n", listOfPlayers[i].frame);
        
			playerGoUp(&listOfPlayers[i], &window);
		}

		if (playerPushDown(&listOfPlayers[i]) && !(smthgIsDown(&listOfPlayers[i], &map, &screen)))
		{
            
			playerGoDown(&listOfPlayers[i], &window);
		}

		if (playerPushLeft(&listOfPlayers[i]) && !(smthgIsLeft(&listOfPlayers[i], &map, &screen)))
		{
            
			playerGoLeft(&listOfPlayers[i], &window);
		}

		if (playerPushRight(&listOfPlayers[i]) && !(smthgIsRight(&listOfPlayers[i], &map, &screen)))
		{
            
			playerGoRight(&listOfPlayers[i], &window);
		}

        if (playerPushBomb(&listOfPlayers[i]))
        {
            playerPutBomb(&listOfPlayers[i], &map,&window);
        }

        player_rect_actualise(&listOfPlayers[i]);
        gridActualisation(&listOfPlayers[i],&map);
        draw_player(&listOfPlayers[i], &window);
    }
        grid_renderer(rectArray, &map, &window);
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);
    // closing the listening socket
    //shutdown(server_fd, SHUT_RDWR);
        SDL_RenderPresent( window.cur_renderer);
        SDL_Delay(10);
        int pause = 0;*/
    int lastKey[NUMBER_OF_PLAYERS];
    int pause=0;
    while (!(caseOfGameOver(listOfPlayers, NUMBER_OF_PLAYERS)))
    {
        valread = read(new_socket, buffer, 1024);
        buffer[valread] = '\0';  
    //send(sd , buffer , strlen(buffer) , 0 );
    //printf("id_online: %d\n",buffer[0]);
        if (buffer[0]==1){
        listOfPlayers[buffer[0]].inputs->up=buffer[1];
        listOfPlayers[buffer[0]].inputs->down=buffer[2];
        printf("down:%d\n",buffer[2]);
        listOfPlayers[buffer[0]].inputs->left=buffer[3];
        listOfPlayers[buffer[0]].inputs->right=buffer[4];
        listOfPlayers[buffer[0]].inputs->space=buffer[5];}
    //printf("%s\n", buffer);

        prepareScene(&window);
        grid_renderer(&screen, rectArray, &map, &window, texturesList);
        grid_renderer_first(rectArray, &window, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);

        //reactToKey(&listOfPlayers[0],&map,&window,&screen,texturesList,&lastKey[0]);
        for(int i = 0; i< NUMBER_OF_PLAYERS; ++i)
        {
            
            if(listOfPlayers[i].health <= 0)
            {
                playerResetInputs(&listOfPlayers[i]);
            }
            returnToRestPose(&listOfPlayers[i],lastKey[i],texturesList);
            reactToKey(&listOfPlayers[i],&map,&window,&screen,texturesList,&lastKey[i]);
            gridActualisation(&map,&screen,&window, texturesList);
            playerActualise(&listOfPlayers[i], &map, &screen, &window, texturesList);
            playerShowUI(&listOfPlayers[i], &window, texturesList, police);
            draw_player(&listOfPlayers[i], &window, police);

        } 
		
        SDL_RenderPresent( window.cur_renderer);
        SDL_Delay(10);

        
        doInput(&listOfPlayers[0], 1, &pause);
        /*if(pause == 1)
        {
            showEscapeMenu(&window, &screen,texturesList,police);
        }
        
        }while(pause == 1);*/
        

    }
    

    // closing the connected socket
    for(int i = 0; i<NUMBER_OF_PLAYERS; ++i)
    {
        playerDestruction(&listOfPlayers[i]);
    }
    mapDestruction(&map);
    texturesListDestroy(texturesList);
    SDL_DestroyRenderer(window.cur_renderer);
    SDL_DestroyWindow(window.cur_window);
    TTF_Quit();
    SDL_Quit();
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}