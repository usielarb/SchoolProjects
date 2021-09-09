#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Faltan los argumentos IP,puerto");
        exit(-1);
    }
    int puerto = atoi(argv[2]);
    char *ip = argv[1];
    int tam_enviado;
    int flag=1;
    //se crea el socket
    int id;
    id = socket(AF_INET,SOCK_STREAM,0);
    if(id<0){
        perror("no se ha podido abrir el socket");
        exit(-1);
    }
    //publicar la direccion y puerto donde el serv se va a ejecutar
    struct sockaddr_in servidor;
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(puerto);
    servidor.sin_addr.s_addr = inet_addr(ip);
    if(bind(id, (struct sockaddr *)&servidor, sizeof(servidor))<0){
        perror("Error en el bind ");
        exit(-1);
    }

    //listen
    //se pone a la escucha de peticiones y puede encolar a un cierto numero de peticiones que lleguen
    // las va atendiendo una x una
    listen(id, 3);

    //estructura que llenará el serv
    struct sockaddr_in cliente;
    int tam_cliente = sizeof(cliente);
      int tam;
      char buffer[50];
    //devuelve canal donde se va a comunicar cliente y servidor
    while (1) {
        flag=1;
      /* code */
      int canal = accept(id, (struct sockaddr *)&cliente, &tam_cliente);
      if(canal < 0){
          perror("Error al establecer el canal ");
          exit(-1);
      }

      //comunicacion
      //el servidor recibe
      while (flag==1)
      {
      if((tam = recv(canal,(void*)buffer,sizeof(buffer),0))<0){
          perror("Error en  recv ");
          exit(-1);
      }
      buffer[tam] = '\0';
      if (strcmp(buffer, "Exit")== 0) {
          printf ("El cliente cerro la comunicación\n");
          flag=0;
      }
      if (flag==1) 
      {
        printf("\nMensaje recibido del cliente %s\n",buffer);

        //strcpy(buffer,"Hola amigo");
        printf ("Escriba mensaje an enviar:\t");
        scanf("%s", buffer);
        
        tam_enviado = strlen(buffer);
        if(send(canal,(void*)buffer,tam_enviado,0) != tam_enviado){
            perror("Error en el send ");
            exit(-1);
        }
        if (strcmp(buffer, "Exit")== 0) {
          printf ("El server cerro la comunicación\n");
          flag=0;
        }
        else
        printf("\nMensaje enviado al cliente");
      }
      }
      sleep(2);
      close(canal);
    }

    return 0;
}
