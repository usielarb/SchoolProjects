#ifndef PROCESOS_H
#define PROCESOS_H

void proceso_hijo(int np, int pipefd[], int datos[]);
void proceso_padre(int pipefd[NUM_PROC][2], int *datos);

#endif
