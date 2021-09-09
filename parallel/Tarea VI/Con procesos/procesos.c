#include <stdio.h>
#include "defs.h"
#include "procesamiento.h"
#include "archivos.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//extern pthread_mutex_t bloqueo;
extern float *hann, *pulso, *vResultado, *autocorelacion;


void proceso_hijo( int np, int pipefd[] )
{
    int eleBloque = N / NUM_PROC ;
	int inicio = np * eleBloque;
	int fin = inicio + eleBloque;
    close( pipefd[0] );
    //int nucleo = nh * (N /NUM_HILOS);
    for (int register i = inicio; i < fin; i++)
        vResultado[i] = pulso[i] * hann[i];

    write( pipefd[1], vResultado + inicio, sizeof(int) * eleBloque );
	close( pipefd[1] );
	exit( np );
}
void proceso_hijo_autocorelacion( int np, int pipefd[] )
{
    int eleBloque = N / NUM_PROC ;
	int inicio = np * eleBloque;
	int fin = inicio + eleBloque;
	int register i, j;
	float temp = 0;
    close( pipefd[0] );
    //int nucleo = nh * (N /NUM_HILOS);

	// for (int register i = 0; i < N; i+=1)
	// 	printf("%f, \t", vResultado[i]);


    for ( i = inicio; i < fin; i++, temp = 0)
	{
		for ( j = i; j < N - 1; j++){
        	temp += vResultado[j] * vResultado [j-i];
		}
		autocorelacion[i] = temp;
		printf("%f,\n", temp);
	}

    write( pipefd[1], autocorelacion + inicio, sizeof(int) * eleBloque );
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
    guardarDatos(vResultado,"Resultado.dat");
    guardarDatos(hann, "VentanaHann.dat");
	printf("Hann terminado\n");
}
void proceso_padre_autocorelacion( int pipefd[NUM_PROC][2] ){

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
		read( pipefd[numproc][0], autocorelacion + inicio , sizeof(int) * eleBloque );
		close( pipefd[numproc][0] );
		printf("Proceso de autocorelacion con id %d terminado \n", numproc);
	}
    guardarDatos(autocorelacion,"Autocorelacion.dat");
}