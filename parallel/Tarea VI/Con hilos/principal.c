#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "defs.h"
#include "hilos.h"
#include "archivos.h"
#include "helper.h"
#include "procesamiento.h"

float *hann, *pulso, *vResultado, *autocorelacion;
pthread_t tids[NUM_HILOS];

int main()
{    
    register int nh;
	int nhs[NUM_HILOS], *hilo;
    srand(getpid());
 
    hann = reservarMemoria();
    pulso = reservarMemoria();
	vResultado = reservarMemoria();
	autocorelacion = reservarMemoria();

	leerDatos(pulso, "PulseSensor.dat");
	generaHann(hann);



	

    //imprimirArreglo(datos);

	//Creacion del ventaneo
	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
		printf("todo kul\n");
	}
	funPadre();

	//implementacion de la autocorelacion
	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		pthread_create( &tids[nh] , NULL, funHilo2, (void *)&nhs[nh] );
		printf("todo kul2\n");
	}
	funPadre2();
	free(hann);
	free(pulso);
	free(vResultado);
	free(autocorelacion);
	
	
	return 0;

}
