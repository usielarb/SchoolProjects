#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    char a[60];
    int b;
    float c;
}est;

void *thread(void* arg);

int main(int argc,char *argv[]){
	if(argc<2){
		printf("Error ejecuta como %s <numero>\n",*argv);
		exit(1);
	}
	int p=atoi(*(argv+1)),i;
    //int p=3, i;
    est *j;
	pthread_t *t;
	j=(est*)malloc(sizeof(int)*p);
	t=(pthread_t*)malloc(sizeof(pthread_t)*p);
   
    for(i=0;i<p;i++)
        *(j+i).a=35+i;
        *(j+i).b=35+i;
        *(j+i).c=35+i;
        printf ("%s, %d, %f\n", (*(j+i)).a,(*(j+i)).b,(*(j+i)).c); 
    }
	for(i=0;i<p;i++){
		//*(j+i)=i;
		pthread_create(&(*(t+i)),NULL,thread,(void*)(j+i));
	}
        pthread_join(*(t+i),NULL);
	printf("Proceso padre\n");
	free(t);
	free(j);
	return 0;
}

void *thread(void *arg){
    est *aux,*dos;
    aux = (est*)arg;
    printf ("1\n");
        printf ("%s, %d, %f\n", ((aux))->a,((aux))->b,((aux))->c); 
    
    pthread_exit(dos);
}

