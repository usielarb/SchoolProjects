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

float *hann, *pulso, *vResultado;


int main()
{    
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

 
    hann = reservarMemoria();
    pulso = reservarMemoria();
	vResultado = reservarMemoria();

	leerDatos(pulso, "PulseSensor.dat");
	generaHann(hann);

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

	

    //imprimirArreglo(datos);


	// for( nh = 0; nh < NUM_HILOS; nh++ )
	// {
	// 	nhs[nh] = nh;
	// 	pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
	// 	printf("todo kul\n");
	// }

	// funPadre();
	
	free (hann);
	free (pulso);
	free (vResultado);
	
	return 0;

}
