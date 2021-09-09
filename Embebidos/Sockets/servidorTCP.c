#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PUERTO 5000		//Número de puerto asignado al servidor
#define COLA_CLIENTES 5 //Tamaño de la cola de espera para clientes
#define TAM_BUFFER 100
#define EVER 1

void manejador(int sig);
void cliente(int cliente_sockfd);

	int sockfd, cliente_sockfd;
int main(int argc, char **argv)
{
	pid_t pid;
	struct sockaddr_in direccion_servidor; //Estructura de la familia AF_INET, que almacena direccion

	if (signal(SIGUSR1, manejador) == SIG_ERR)
	{
		perror("Error enel manejador");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, manejador) == SIG_ERR)
	{
		perror("Error enel manejador");
		exit(EXIT_FAILURE);
	}
	/*
 *	AF_INET - Protocolo de internet IPV4
 *  htons - El ordenamiento de bytes en la red es siempre big-endian, por lo que
 *  en arquitecturas little-endian se deben revertir los bytes
 *  INADDR_ANY - Se elige cualquier interfaz de entrada
 */
	memset(&direccion_servidor, 0, sizeof(direccion_servidor)); //se limpia la estructura con ceros
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);
	direccion_servidor.sin_addr.s_addr = INADDR_ANY;

	/*
 *	Creacion de las estructuras necesarias para el manejo de un socket
 *  SOCK_STREAM - Protocolo orientado a conexión
 */
	printf("Creando Socket ....\n");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
	}
	/*
 *  bind - Se utiliza para unir un socket con una dirección de red determinada
 */
	printf("Configurando socket ...\n");
	if (bind(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0)
	{
		perror("Ocurrio un problema al configurar el socket");
		exit(1);
	}
	/*
 *  listen - Marca al socket indicado por sockfd como un socket pasivo, esto es, como un socket
 *  que será usado para aceptar solicitudes de conexiones de entrada usando "accept"
 *  Habilita una cola asociada la socket para alojar peticiones de conector procedentes
 *  de los procesos clientes
 */
	printf("Estableciendo la aceptacion de clientes...\n");
	if (listen(sockfd, COLA_CLIENTES) < 0)
	{
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
		exit(1);
	}
	/*
 *  accept - Aceptación de una conexión
 *  Selecciona un cliente de la cola de conexiones establecidas
 *  se crea un nuevo descriptor de socket para el manejon 
 *  de la nueva conexion. Apartir de este punto se debe
 *  utilizar el nuevo descriptor de socket
 *  accept - ES BLOQUEANTE
 */
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

void cliente(int cliente_sockfd)
{
	char leer_mensaje[TAM_BUFFER];
	printf("Se aceptó un cliente, atendiendolo \n");
	if (read(cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0)
	{
		perror("Ocurrio algun problema al recibir datos del cliente");
		exit(EXIT_FAILURE);
	}
	printf("El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
	if (write(cliente_sockfd, "Bienvenido cliente", 19) < 0)
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(EXIT_FAILURE);
	}
	kill(getppid(), SIGUSR1);
	close(cliente_sockfd);
	exit(0);
}

void manejador(int sig)
{
	int estado;
	pid_t pid;
	if (sig == SIGUSR1)
	{
		printf("Se recibio la señal de usuario 1 en el servidor\n");
		pid = wait(&estado);
		printf("Termino el proceso %d con estado: %d\n", pid, estado >> 8);
	}
	else if (sig == SIGINT)
	{
		printf("Se recibio la señal SIGINT en el servidor\n Concluimos la aplicaion del servidor\n");
		close(cliente_sockfd);
		close(sockfd);
		kill(getppid(), SIGUSR1);
	 	exit(0);
	}
	//close(cliente_sockfd);
	//exit(0);
}
