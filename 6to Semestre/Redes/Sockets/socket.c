#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main (int argc, char *argv[])
{

    if (argc != 3)
    {
        printf ("Parametros incorrectos\n");
        exit(-1);
    }
    int puerto = atoi(argv[2]);
    char *ip =argv[1];
     //PASO 1: Se crea el socket
    int id;
    char buffer[50];
    strcpy(buffer, "Hola Mundo");
    
    if ((id = socket(AF_INET, SOCK_STREAM, 0)) < 0) exit (-1);

    //PASO 2: Se conecta
    struct sockaddr_in servidor;
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(puerto);
    servidor.sin_addr.s_addr = inet_addr(ip); 
    if ((connect(id,(struct sockaddr *)&servidor, sizeof(servidor))) < 0)
    {
        perror("ErrorConect\n");
        exit(-1);
    }
    //comunicacion

    if (send(id, (void*)buffer, strlen(buffer), 0) < strlen(buffer))
    {
        perror("Error al enviar datos\n");
        exit(-1);
    }
    printf ("Mensaje Enviado del serviro: %s\n", buffer);

    int tam_rec = recv(id, (void*)buffer, sizeof(buffer), 0);
    buffer[tam_rec]='\0';

    if ( tam_rec < 0)
    {   
        perror("Error al recibir datos\n");
        exit(-1);
    }
    printf ("Mensaje Recibido del serviro: %s\n", buffer);

    close(id);
    
    

    return 0;
    


}