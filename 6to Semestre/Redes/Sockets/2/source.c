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
  /* Variables para el manejo de sockets y la ip */
  int sock,puerto=atoi(argv[1]);
  char *ip=argv[2];
  /* Creacion de la estructura del server  */
  struct sockaddr_in cliente;
  /* Creacion y validacion del socket */
  if((sock=socket(AF_INET, SOCK_STREAM,0))==-1){
    perror("Error al abrir el socket cliente");
    exit(EXIT_FAILURE);
  }
  /* Asignación de datos  del puerto y del cliente */
  cliente.sin_family = AF_INET;
  cliente.sin_port = htons(puerto);
  cliente.sin_addr.s_addr=inet_addr(ip);
  /* Genera un punto de conexion con el servidor */
  if(connect(sock,(struct sockaddr*)&cliente,sizeof(struct sockaddr_in))<0){
    close(sock);
    perror("Error en crear la conexion del socket cliente");
    exit(EXIT_FAILURE);
  }
  /* Se crea el buffer con el que se enviara un mensaje desde el cliente */
  char buffer[50];
  strcpy(buffer,"Hola mundo desde socket desde el cliente\0");
  int valor;
  if((valor=send(sock,buffer,50,0))!=sizeof(buffer)){
    close(sock);
    perror("Error en enviar trama del socket cliente");
    exit(EXIT_FAILURE);
  }
  printf("Mensaje enviado: %s\n",buffer);
  int tam;
  /* Se espera por recibir una respuesta del servidor */
  if(recv(sock,buffer,50,0)<0){
    close(sock);
    perror("Error en recibir trama del socket cliente");
    exit(EXIT_FAILURE);
  }
  tam=strlen(buffer);
  buffer[tam]='\0';
  printf("Mensaje recibido: %s",buffer);
  close(sock);
  return 0;
}
