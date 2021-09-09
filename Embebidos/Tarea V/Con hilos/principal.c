#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "defs.h"
#include "hilos.h"
#include "helper.h"
#include "procesos.h"

pthread_mutex_t bloqueo = PTHREAD_MUTEX_INITIALIZER;
int *A, *B;
double PP = 0 ;  
pthread_t tids[NUM_HILOS];

int main()
{   
	
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe; 
    int nh;
	int nhs[NUM_HILOS], *hilo;
    srand(getpid());
 
    A = reservarMemoria();
    B = reservarMemoria();
	
	

	llenarArreglo(A);
	llenarArreglo(B);

	//imprimirArreglo(A);
	//imprimirArreglo(B);


	

    //imprimirArreglo(datos);


	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
		//printf("todo kul\n");
	}

	funPadre();
	
	


	for( np = 0; np < NUM_PROC; np++ )
	{
		edo_pipe = pipe( &pipefd[np][0] );
		if( edo_pipe == -1 )
		{
			perror("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if( pid == -1 )
		{
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		if( !pid )
		{
			proceso_hijo( np, &pipefd[np][0] );
		}
	}
	proceso_padre( pipefd );

	free(A);
	free(B);
	pthread_mutex_destroy(&bloqueo);
	return 0;

}
