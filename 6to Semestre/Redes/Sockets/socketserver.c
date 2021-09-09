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
    strcpy(buffer, "Respuesta");
    if ((id = socket(AF_INET, SOCK_STREAM, 0)) < 0) exit (-1);


    //PASO 2: Se conecta
    //bind publica el servicio;
    struct sockaddr_in servidor, cliente;
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(puerto);
    servidor.sin_addr.s_addr = inet_addr(ip); 

    int tam_client = sizeof (cliente);

    if (bind(id,(struct sockaddr *) &servidor, sizeof(servidor)) < 0)
    {
        perror ("Error ena el bind\n");
        exit(-1);
    }


    //Listen se pone a la escucha de peticiones y puede encolar a un cierto numero de peticiones que lllguea

    listen(id, 2);
    int canal;
    //
    if (canal = accept(id, (struct sockaddr *)&cliente, &tam_client ) < 0)
    {
        perror ("Error al crear el canal\n");
        exit(-1);
    }

  
    //comunicacion


    int tam_rec = recv(canal, (void*)buffer, sizeof(buffer), 0);
    buffer[tam_rec]='\0';

    if ( tam_rec < 0)
    {   
        perror("Error al recibir datos\n");
        exit(-1);
    }
    printf ("Mensaje Recibido del cliente: %s\n", buffer);

    if (send(canal, (void*)buffer, strlen(buffer), 0) != strlen(buffer))
    {
        perror("Error al enviar datos\n");
        exit(-1);
    }
    printf ("Mensaje Enviado del cliente: %s\n", buffer);

    sleep(2);

    close(canal);
    
    

    return 0;
    


}