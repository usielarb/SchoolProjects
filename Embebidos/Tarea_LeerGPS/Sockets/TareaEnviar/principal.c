#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "defs.h"
#include "servidor.h"


int sockfd, cliente_sockfd;
int main(int argc, char **argv)
{
    inServ();
    pid_t pid;
    
    for (; EVER;)
	{
		printf("En espera de peticiones de conexión ...\n");
		if ((cliente_sockfd = accept(sockfd, NULL, NULL)) < 0)
		{
			perror("Ocurrio algun problema al atender a un cliente");
			exit(1);
		}
		pid = fork(); 
		if (!pid)
		{
			/*
 *	Inicia la transferencia de datos entre cliente y servidor
 */
			cliente(cliente_sockfd);
		}
	}
	printf("Concluimos la ejecución de la aplicacion Servidor \n");
	/*
 *	Cierre de las conexiones
 */

	close(sockfd);

	return 0;
}
