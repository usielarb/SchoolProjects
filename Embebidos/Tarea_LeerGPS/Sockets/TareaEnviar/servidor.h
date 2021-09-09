#ifndef SERVIDOR_H
#define SERVIDOR_H

void inServ();
void cliente(int cliente_sockfd);
void manejador(int sig);

#endif