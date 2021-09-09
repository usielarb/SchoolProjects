#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROC 4
#define N 32
#define constante 10

void proceso_hijo(int np, int pipefd[], int datos[]);
void proceso_padre(int pipefd[NUM_PROC][2], int *datos);

void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);
int *reservarMemoria();

void burbuja(int *datos);
void MultiC(int *datos);

int main()
{
    int *datos;
    srand(getpid());
    pid_t pid;
    int pipefd[NUM_PROC][2], edo_pipe;
    printf("Probando procesos...\n");

    datos = reservarMemoria();
    llenarArreglo(datos);
    imprimirArreglo(datos);

    for (register int np = 0; np < NUM_PROC; np++)
    {
    edo_pipe = pipe(&pipefd[np][0]);
        if (edo_pipe == -1)
        {
            perror("Error al crear la tuberia...");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("Error al crear el proceso...");
            exit(EXIT_FAILURE);
        }
        if (!pid)
        {
            proceso_hijo(np, &pipefd[np][0],datos);
        }
    }
    proceso_padre(pipefd, datos);
    return 0;
    
}
void proceso_hijo(int np, int pipefd[], int datos[])
{
    int resultado;
    close(pipefd[0]);
    if (np == 0)
    {
        burbuja(datos);
        //imprimirArreglo(datos);
        write (pipefd[1], datos, sizeof(int) * N);
        }
    else if (np ==1)
    {
        MultiC(datos);
        write (pipefd[1], datos, sizeof(int) * N);
        }
    else if (np ==2)
    {
        resultado = sacarPromedio(datos); 
        write (pipefd[1], &resultado, sizeof(int));
        }
    else if (np ==3)
    {
        resultado = contarPares(datos); 
        write (pipefd[1], &resultado, sizeof(int));
        }
    
    close(pipefd[1]);
    exit(np);
}

void proceso_padre(int pipefd[NUM_PROC][2], int *datos)
{
    register int np;
    pid_t pid;
    int estado, nproc, resultado;
    for(np = 0 ; np < NUM_PROC; np++)
    {
        pid = wait(&estado);
        nproc = estado >> 8;
        printf("Proceso %d terminado.\n", nproc);

        switch (nproc)
        {
        case 0:
            read(pipefd[nproc][0], datos, sizeof(int)*N);
            close(pipefd[nproc][1]);
            printf ("El proceso %d con pind %d ordeno el arreglo", estado, pid);
            imprimirArreglo(datos);
            
            break;
        case 1:
            read(pipefd[nproc][0], datos, sizeof(int) * N);
            close(pipefd[nproc][1]);
            printf ("El proceso %d con pind %d Multiplico * %d el arreglo: \n", estado, pid, constante);
            imprimirArreglo(datos);
            break;
        case 2:
            read(pipefd[nproc][0], &resultado, sizeof(int));
            close(pipefd[nproc][1]);
            printf ("El proceso %d con pind %d obtubo el siguiente promedio del arreglo: %d\n", estado, pid, resultado);
            break;
        case 3:
            read(pipefd[nproc][0], &resultado, sizeof(int));
            close(pipefd[nproc][1]);
            printf ("El proceso %d con pind %d conto los siguientes pares: %d\n", estado, pid, resultado);
            break;
        
        default:
            printf("error, no se encontro opcion para este hijo\n");
            break;
        }
        close(pipefd[nproc][0]);
    }
}


void llenarArreglo(int *datos)
{
    for (int i = 0; i < N; i++)
        datos[i]=rand()%256;
    
}
void imprimirArreglo(int *datos)
{
    for (int i = 0; i <N; i++)
    {
          if (! (i % 12))
              printf("\n");
        printf("%4d ", datos[i]);
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

void burbuja(int *datos)
{
    //imprimirArreglo(datos);
    //printf ("---");
    int aux;
    for (int j = 0; j < N; j++)
    {
        for (int  i = 0; i < N-j; i++)
        {
            if (datos[i] > datos[i+1])
            {
                aux = datos[i];
                datos[i] = datos[i+1];
                datos[i+1] = aux;
            }
        }
    }
    //imprimirArreglo(datos);
}
void MultiC(int *datos)
{
    for (int i = 0; i < N; i++)
        datos[i] = datos[i] * constante;
}
int sacarPromedio(int *datos)
{
    int suma = 0, promedio = 0;
    int register i;
    for ( i = 0; i < N; i++)
        suma+=datos[i];
    promedio = suma / N;
    return promedio;    
}
int contarPares(int *datos)
{
    int cont = 0;
    int register i;
    for ( i = 0; i < N; i++)
    {
        if (!(datos[i] % 2))
            cont++;
    }
    //printf ("%d pares\n", cont);
    return cont;
}