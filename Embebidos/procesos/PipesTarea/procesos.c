#include <stdio.h>
#include "defs.h"
#include "procesamiento.h"
#include "helper.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



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