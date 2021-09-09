#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct 
{
  int canal;
  pthread_t t;
  int id;
}parametro;

void* hilo(void *arg);

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Faltan los argumentos IP,puerto");
        exit(-1);
    }
    int puerto = atoi(argv[2]);
    char *ip = argv[1];
    int tam_enviado, num=0;
    int flag=1;
    pthread_t *t;
    
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
    listen(id, 10);

    //estructura que llenará el serv  
    struct sockaddr_in cliente;
    int tam_cliente = sizeof(cliente);
      
      
    //devuelve canal donde se va a comunicar cliente y servidor
    //int *canal;
    parametro *par;

    while (1) 
    {
        
      /* code */
        par =(parametro*)malloc(sizeof(parametro));
        //canal = (int *)malloc(sizeof(int));
        //t = (pthread_t*) malloc(sizeof(pthread_t));
        par->canal= accept(id, (struct sockaddr *)&cliente, &tam_cliente);
        num++;
        par->id =num;
      if(par->canal < 0){
          perror("Error al establecer el canal ");
          //exit(-1);
      }
      else
      {
          pthread_create(&(par->t), NULL, hilo,(void*)par);
          printf ("Hilo creado con exito\n");
      }
    }
      
      
      

    return 0;
}

void *hilo(void* arg)
{
    //comunicacion
    //el servidor recibe
    char buffer[50];
    parametro* inf;  
    int tam, flag=1, tam_enviado;
    inf = (parametro *) arg;
    while (flag==1)
      {
      if((tam = recv(inf->canal,(void*)buffer,sizeof(buffer),0))<0){
          perror("Error en  recv ");
          exit(-1);
      }
      buffer[tam] = '\0';
      if (strcmp(buffer, "Exit")== 0) {
          printf ("El cliente cerro la comunicación %d\n", inf->id);
          flag=0;
      }
      if (flag==1) 
      {
        printf("\n%d - Mensaje recibido del cliente %s\n",inf->id,buffer);

        //strcpy(buffer,"Hola amigo");
        printf ("%d - Escriba mensaje an enviar:\t", inf->id);
        scanf("%[^\n]", &buffer);
        
        tam_enviado = strlen(buffer);
        if(send(inf->canal,(void*)buffer,tam_enviado,0) != tam_enviado){
            perror("Error en el send ");
            exit(-1);
        }
        if (strcmp(buffer, "Exit")== 0) {
          printf ("El server cerro la comunicación %d\n", inf->id);
          flag=0;
        }
        else
        printf("\nMensaje enviado al cliente %d", inf->id);
      }
      }
      sleep(2);
      close(inf->canal);
      free(inf);
}


