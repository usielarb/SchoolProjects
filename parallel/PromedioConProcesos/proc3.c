#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROC 4
#define N 16

int *A;
int promedio = 0; 

void proceso_padre( int pipefd[NUM_PROC][2] );
void proceso_hijo( int np, int pipefd[] );
void llenarArreglo(int *datos);
int *reservarMemoria();
void imprimirArreglo(int *datos);


int main()
{
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

	A =  reservarMemoria();
	llenarArreglo(A);
	imprimirArreglo(A);

	printf("Probando procesos...\n");

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
	printf("El promedio es: %d\n", promedio);


	free (A);
	return 0;
}

void proceso_padre( int pipefd[NUM_PROC][2] )
{
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
		read( pipefd[numproc][0], &resultado , sizeof(int) );
		close( pipefd[numproc][0] );
		promedio += resultado;
	}
	promedio = promedio >> 4;
	//printf("El promedio es:\t%d\n", promedio);
}

void proceso_hijo( int np, int pipefd[] )
{
	int eleBloque = N / NUM_PROC ;
	int inicio = np * eleBloque;
	int fin = inicio + eleBloque;
	close( pipefd[0] );
	//Opcion 1
	// for (int i = inicio ; i < fin ; i++)
	// 	promedio += A[i];

	//Opcion 2
	for(int register i = np ; i < N ; i += eleBloque)
		promedio += A[i];

	write( pipefd[1], &promedio, sizeof(int));
	close( pipefd[1] );
	exit( np );
}


void llenarArreglo(int *datos)
{
    for (int i = 0; i < N; i++)
    {
        datos[i]=rand()%256;
    }
    
}
void imprimirArreglo(int *datos)
{
    for (int i = 0; i <N; i++)
    {
          if (! (i % 16))
              printf("\n");
        printf("%3d ", datos[i]);
    }
    printf("\n");

    
}


int *reservarMemoria()
{
    int *mem;
    mem = (int *)malloc(N*sizeof(int));
    if (!mem)
    {
        perror("Error al asignar memoria...");
        exit(EXIT_FAILURE);
    }
    return mem;
}
