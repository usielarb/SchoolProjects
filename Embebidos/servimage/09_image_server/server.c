/**
 * Joel Hernández @ 2020
 * Github: https://github.com/JoelHernandez343
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>

#include "defs.h"
#include "image.h"

#define LOG "[Server] "
#define CLIENTS 5

int server_socket;

void signal_handler(int sig){
    if (sig == SIGCHLD){
        int status;
        printf(LOG"A child has finished.\n");
        wait(&status);
    }

    else if (sig == SIGINT){
        printf(LOG"Termination requested.\n");
        printf(LOG"Ending server process and freeing up resources.\n");
        
        close(server_socket);
        
        printf(LOG"Finished.\n");

        exit(EXIT_SUCCESS);
    }
}

void initialize_signals(){
    if (signal(SIGCHLD, signal_handler) == SIG_ERR){
        printf(ERR_LOG"Error binding handler w/ SIGCHLD\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, signal_handler) == SIG_ERR){
        printf(ERR_LOG"Error binding handler w/ SIGINT\n");
        exit(EXIT_FAILURE);
    }
}

void initialize_server(){
    struct sockaddr_in server_address;

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    printf(LOG"Creating socket.\n");
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf(ERR_LOG"Couldn't create socket.\n");
        exit(EXIT_FAILURE);
    }

    printf(LOG"Configuring socket.\n");
    if (bind(server_socket, (struct sockaddr *)&(server_address), sizeof(server_address)) < 0){
        printf(ERR_LOG"Socket couldn't be set.\n");
        exit(EXIT_FAILURE);
    }

    printf(LOG"Setting client acceptance.\n");
    if (listen(server_socket, CLIENTS) < 0){
        printf(ERR_LOG"Cliet queue couldn't be set.\n");
        exit(EXIT_FAILURE);
    }
}


void bind_data(char buffer[5 * 32], char *parameters[5]){
    memset(buffer, 0, 5 * 32);

    for (int i = 0; i < 5; ++i){
        parameters[i] = buffer + i * 32;
    }
}

void client_handler(int client_socket){
    printf("[CLIENT] Sending data to client.\n");

    bmp_info_header info;
    unsigned char *image = NULL;
    take_photo(&info, image);
    process_image(&info, image);

    int sent = 0, length = sizeof(bmp_info_header);
    while (sent < length){
        sent += write(client_socket, &info + sent, length - sent);
    }

    sent = 0, length = info.width * info.height * 3;
    while (sent < length){
        sent += write(client_socket, image + sent, length - sent);
    }

    free(image);

    close(client_socket);
    printf("[CLIENT] Image sent.\n");

    exit(EXIT_SUCCESS);
}

void server_process(){
    initialize_signals();
    initialize_server();

    int client_socket;
    while (1){
        printf(LOG"Waiting for connections...\n");
        
        if ((client_socket = accept(server_socket, NULL, NULL)) < 0){
            printf(ERR_LOG"Client couldn't be served\n");
            exit(EXIT_FAILURE);
        }

        if (!fork()){
            client_handler(client_socket);
        }
    }
}