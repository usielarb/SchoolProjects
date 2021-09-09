#include <stdio.h>
#include "defs.h"
#include "procesamiento.h"
#include "archivos.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

extern pthread_mutex_t bloqueo;
extern float *hann, *pulso, *vResultado;


void proceso_hijo( int np, int pipefd[] )
{
    // int inicio = np * eleBloque;
	// int fin = inicio + eleBloque;
    close( pipefd[0] );
    //int nucleo = nh * (N /NUM_HILOS);
    for (int register i = np; i < N; i+=NUM_PROC
        vResultado[i] = pulso[i] * hann[i];

    write( pipefd[1], vResultado + inicio, sizeof(int) * eleBloque );
	close( pipefd[1] );
	exit( np );
}
void proceso_padre( int pipefd[NUM_PROC][2] ){

    register int np;
	pid_t pid;
	int estado, numproc, resultado;
	int eleBloque = N / NUM_PROC;
	int inicio;

	for( np = 0; np < NUM_PROC; np++ )
	{
		pid = wait(&estado);
		numproc = estado >> 8;
		close( pipefd[numproc][1] );
		inicio = numproc * eleBloque;
		read( pipefd[numproc][0], vResultado + inicio , sizeof(int) * eleBloque );
		close( pipefd[numproc][0] );
	}
	





    // int *hilo;
    // for( int nh = 0; nh < NUM_HILOS; nh++ )
	// {
	// 	pthread_join( tids[nh], (void **)&hilo );
	// 	printf("El hilo %d ha terminado\n", *hilo);        
	// }
    guardarDatos(vResultado,"Resultado.dat");
    guardarDatos(hann, "VentanaHann.dat");
}