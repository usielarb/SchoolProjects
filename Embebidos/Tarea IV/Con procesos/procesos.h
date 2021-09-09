#ifndef HILOS_H
#define HILOS_H

void proceso_hijo( int np, int pipefd[] );
void proceso_padre( int pipefd[NUM_PROC][2] );
#endif