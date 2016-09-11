/* Compilar com gcc -O0 bakery-nprocs.c -pthread */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 8
#define CARGA 1000000000

#define MAX_REPEAT 20

long volatile compart = 0; //Var. global compartilhada por todos threads
int volatile ticket[MAX_THREADS]; //Ticket a ser retirado
int volatile want[MAX_THREADS]; //define a intencao de entrar na SC



void *threadfunc(void *threadid) { //funcao que inicia com a thread
	int maxticket;
	long j;
	int tid;
	tid = (long)threadid;
	unsigned int semente;
	semente = tid;
	maxticket = ticket[0];
	for(j=0;j<MAX_THREADS;j++){
		if(ticket[j]>maxticket){
			maxticket=ticket[j];
		}
	}
	// Pre-protocolo: escrever aqui
	want[tid]=1;
	ticket[tid]=1+maxticket;
	want[tid]=0;	
	for(j=0;j<MAX_THREADS;j++){
		if(j!=tid){
			while(!(want[j]==0)){};
			while(!(ticket[j]==0||ticket[tid]<ticket[j]||((ticket[tid]==ticket[j]&&tid<j)))){}; 
		}	
	}
	// Fim do pre-protocolo
	//secao critica
	for(j=1;j<CARGA*rand_r(&semente);j++); ////carga comput. artificial
	compart += (1+tid)*10;//incrementa var. global
	//printf("Thread #%ld, ticket=%d, incremento=%ld, compart=%ld\n", 
	// tid, ticket[tid], (1+tid)*10, compart);
	// pos-protocolo: escrever aqui
	ticket[tid]=0;
	// fim do pos-protocolo
	pthread_exit(NULL);
}

int main(void){
	pthread_t threads[MAX_THREADS];

	long i;
	int repeat;

	//printf("Iniciando Main\n");

	for(repeat=0; repeat<MAX_REPEAT; repeat++) {

		for(i=0; i<MAX_THREADS; i++) {
			if(repeat==0)
				ticket[i] = 0;
			//	printf("Main: i=%ld\n",i);
			pthread_create(&threads[i], NULL, threadfunc, (void *) i);
		}

		for(i=0; i<MAX_THREADS; i++) {
			pthread_join(threads[i], NULL);
			//	printf("Main: i=%ld, compart=%ld\n",i, compart);
		}
	}

	if(compart!=7200){                                                        
		printf("%ld\n",compart);                                              
	}
	return 0;
}  
