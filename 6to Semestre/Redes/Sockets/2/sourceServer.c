#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]) {
  /* Descriptor del socket  */
  if(argc<3){
    printf("Error\nUsage: %s <Port> <Address>\n",*(argv));
    exit(EXIT_FAILURE);
  }
  int sock,puerto=atoi(argv[1]);
  char *ip=argv[2];
  /* Creacion de la estructura del server  */
  struct sockaddr_in servidor;
  /* Creacion y validacion del socket */
  if((sock=socket(AF_INET, SOCK_STREAM,0))==-1){
    perror("Error al abrir el socket");
    exit(EXIT_FAILURE);
  }
  /* Asignación de datos del server */
  servidor.sin_family = AF_INET;
  servidor.sin_port = htons(puerto);
  servidor.sin_addr.s_addr=inet_addr(ip);
  /* Crea la conexion del puerto del server */
  if(bind(sock,(struct sockaddr*)&servidor,sizeof(servidor))<0){
    perror("Error al hacer el bind de la conexion del socket server");
    exit(EXIT_FAILURE);
  }
  /* Listen se pone a la escucha de peticiones y puede encolar a un cierto numero de peticiones*/
  listen(sock,2);

  /* Estructura que llenara el server con la comunicacion del cliente */
  struct sockaddr_in cliente;
  int tam_cliente=sizeof(cliente);

    while(1) 
    {
        int canal = accept(sock,(struct sockaddr*)&cliente,&tam_cliente);
        if(canal<0){
          close(sock);
          perror("Error al establecer el canal de comunicacion server");
          exit(EXIT_FAILURE);
        }

        char buffer[50];
        //int tam;
        /* Se espera por recibir una respuesta del cliente */
        if(recv(canal,buffer,50,0)<0){
          close(sock);
          close(canal);
          perror("Error en recibir trama del socket server");
          exit(EXIT_FAILURE);
        }
        printf("Mensaje recibido del cliente: %s\n",buffer);
        /* Se crea el buffer con el que se enviara un mensaje desde el cliente */
        strcpy(buffer,"Hola mundo desde socket server");
        if(send(canal,buffer,50,0)==-1){
          close(sock);
          close(canal);
          perror("Error en enviar trama del socket server");
          exit(EXIT_FAILURE);
        }
        printf("Mensaje enviado del server: %s\n",buffer);
        close(canal);

    }


  return 0;
}
