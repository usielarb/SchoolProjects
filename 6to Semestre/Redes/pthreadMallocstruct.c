#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct {
    char e[60];
    int b;
    float c;
} estructura;
void *thread(void*);
void *thread2(void*);
void *thread3(void*);

int main(int argc,char *argv[]){
	if(argc<2){
		printf("Error ejecuta como %s <numero>\n",*argv);
		exit(1);
	}
	int p=atoi(*(argv+1)),i;
    estructura *j;
	pthread_t *t, *t2,*t3;
    
	j=(estructura*)malloc(sizeof(estructura)*p);
	t=(pthread_t*)malloc(sizeof(pthread_t)*p);
    t2=(pthread_t*)malloc(sizeof(pthread_t)*p);
    t3=(pthread_t*)malloc(sizeof(pthread_t)*p);
    for (i=0;i<p;i++)
        printf("%s, %d, %f",(j+i)->e,(j+i)->b, (j+i)->c);
	for(i=0;i<p;i++){
		*(j+i);
		pthread_create(&(*(t+i)),NULL,thread,(j+i));
		pthread_create(&(*(t2+i)),NULL,thread2,(j+i));
		pthread_create(&(*(t3+i)),NULL,thread3,(j+i));
	}
	printf("Proceso padre\n");
	for(i=0;i<p;i++){
		pthread_join(*(t),NULL);
	}
    for (i=0;i<p;i++)
        printf("%s, %d, %f",(j+i)->e,(j+i)->b, (j+i)->c);

	free(t);
	free(j);
	return 0;
}

void *thread(void *arg){

	*arg.e = 'a';
        //pthread_exit(*arg);
}
void *thread2(void *arg){

	*arg.b = 0;
        //pthread_exit(*arg);
}
void *thread3(void *arg){

	*arg.c=1.1;
        //pthread_exit(*arg);
}
