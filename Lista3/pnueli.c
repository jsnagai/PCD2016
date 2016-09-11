/* Compilar com gcc -O0 bakery-nprocs.c -pthread */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 2
#define CARGA 1000000000

#define MAX_REPEAT 20


long volatile compart = 0; //Var. global compartilhada por todos threads
int request = 0; //Ticket a ser retirado
int respond = 0; //define a intencao de entrar na SC
int cont = 0 ;



void *servidor(void *threadid) { //funcao que inicia com a thread
	while(cont<(MAX_THREADS-1)){
		while(!(request!=0)){

		}
		respond=request;  
		cont++;
		while(!(respond==0)){

		}
		request=0;
	}
	pthread_exit(NULL);
}

void *cliente(void *threadid) { //funcao que inicia com a thread
	long j;
	long tid;
	tid = (long)threadid;
	unsigned int semente;
	semente = tid;
	while(respond!=tid){
		request=tid; 
	}
	for(j=1;j<CARGA*rand_r(&semente);j++); ////carga comput. artificial
	compart += (1+tid)*10;//incrementa var. global

	respond = 0;	
	pthread_exit(NULL);
}


int main(void){
	pthread_t threads[MAX_THREADS];

	long i;
	int repeat;

	//printf("Iniciando Main\n");

	for(repeat=0; repeat<MAX_REPEAT; repeat++) {
		cont = i = 0;
		pthread_create(&threads[i], NULL, servidor, (void *) i);
		for(i=1; i<MAX_THREADS; i++) {
			pthread_create(&threads[i], NULL, cliente, (void *) i);
		}

		for(i=0; i<MAX_THREADS; i++) {
			pthread_join(threads[i], NULL);
			//printf("Main: i=%ld, compart=%g\n",i, compart);
		}
	}

	printf("%ld\n",compart);

	return 0;
}  
