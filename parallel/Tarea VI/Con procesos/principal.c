#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "defs.h"
#include "procesos.h"
#include "archivos.h"
#include "helper.h"
#include "procesamiento.h"

float *hann, *pulso, *vResultado, *autocorelacion;


int main()
{    
	pid_t pid, pid2;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;
	int pipefd2[NUM_PROC][2], edo_pipe2;

 
    hann = reservarMemoria();
    pulso = reservarMemoria();
	vResultado = reservarMemoria();
	autocorelacion = reservarMemoria();

	leerDatos(pulso, "PulseSensor.dat");
	generaHann(hann);

	//Implementacion del ventaneo
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

// for (int register i = 0; i < N; i++)
// {
// 	printf("%f, \t", vResultado[i]);
// }

//Implementacion de la autocorelacion
	//leerDatos(vResultado, "Resultado.dat");
	for( np = 0; np < NUM_PROC; np++ )
	{
		edo_pipe2 = pipe( &pipefd2[np][0] );
		if( edo_pipe == -1 )
		{
			perror("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}

		pid2 = fork();
		if( pid2 == -1 )
		{
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		if( !pid2 )
		{
			proceso_hijo_autocorelacion( np, &pipefd2[np][0] );
		}
	}
	proceso_padre_autocorelacion( pipefd2 );

	
	free (hann);
	free (pulso);
	free (vResultado);
	free (autocorelacion);
	
	return 0;

}
