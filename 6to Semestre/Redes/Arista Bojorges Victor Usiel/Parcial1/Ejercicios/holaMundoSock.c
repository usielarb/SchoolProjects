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
    int tam;

    //se crea el socket
    int id;
    id = socket(AF_INET,SOCK_STREAM,0);
    char buffer[50];
    if(id<0){
        perror("no se ha podido abrir el socket");
        exit(-1);
    }
    //se conecta el socket
    struct sockaddr_in servidor;
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(puerto);
    servidor.sin_addr.s_addr = inet_addr(ip);
    
    if(connect(id,(struct sockaddr *)&servidor,sizeof(servidor))<0){
        perror("Error en el connect ");
        exit(-1);
    }
    //comunicacion
    //strcpy(buffer,"Hola mundo");
    int flag=1;
    while (flag==1)
    {
        /* code */
    
    printf ("Mensaje a enviar:\t");
    scanf("%[^\n]", &buffer);
    if (strcmp(buffer, "Exit")== 0)
        {
        printf ("Salida con exito!\n");
        flag=0;
    }
    tam = strlen(buffer);
    if(send(id,(void*)buffer,tam,0) < tam){
        perror("Error en el send CLIENTE ");
        exit(-1);
    }
    if (flag==1)
    {
        printf("\nMensaje enviado %s",buffer);
        if((tam = recv(id,(void*)buffer,sizeof(buffer),0))<0){
            perror("Error en recv CLIENTE ");
            exit(-1);
        }
        buffer[tam] = '\0';
        
    if (strcmp(buffer, "Exit")== 0)
        {
        printf ("Salida con exito!\n");
        flag=0;
        
    }
    else   
    printf("\nMensaje recibido del servidor %s\n",buffer);
    }
    }
    close(id);
    return 0;
}
