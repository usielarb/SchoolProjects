#include <stdio.h>
#include "defs.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

extern int *A, *B;
extern double PP; 


void proceso_hijo( int np, int pipefd[] )
{
	double aux=0;
    // int inicio = np * eleBloque;
	// int fin = inicio + eleBloque;
    close( pipefd[0] );
    //int nucleo = nh * (N /NUM_HILOS);
    for (int register i = np; i < N; i+=NUM_PROC)
        aux += A[i] * B[i];


    write( pipefd[1], &aux, sizeof(double) );
	close( pipefd[1] );
	exit( np );
}
void proceso_padre( int pipefd[NUM_PROC][2] ){

    register int np;
	pid_t pid;
	int estado, numproc;
	double temp, final = 0;

	for( np = 0; np < NUM_PROC; np++ )
	{
		pid = wait(&estado);
		numproc = estado >> 8;
		close( pipefd[numproc][1] );
		read( pipefd[numproc][0], &temp ,sizeof(double) );
		close( pipefd[numproc][0] );
		printf("El proceso %d ha terminado \n ", numproc);
		final += temp;
	}
	
	printf("Resultado del producto punto es: \t%.0lf\n", final);




    // int *hilo;
    // for( int nh = 0; nh < NUM_HILOS; nh++ )
	// {
	// 	pthread_join( tids[nh], (void **)&hilo );
	// 	printf("El hilo %d ha terminado\n", *hilo);        
	// }

}