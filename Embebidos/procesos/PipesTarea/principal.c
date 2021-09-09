#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "defs.h"
#include "procesos.h"
#include "helper.h"

int main(){

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
    free (datos);
    return 0;
 
}