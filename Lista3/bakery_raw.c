/* Compilar com gcc -O0 bakery-nprocs.c -pthread */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 8
#define CARGA 1000000000

#define MAX_REPEAT 20

long volatile compart = 0; //Var. global compartilhada por todos threads
int volatile ticket[MAX_THREADS]; //Ticket a ser retirado
int volatile want[MAX_THREADS]; //define a intencao de entrar na SC

void *threadfunc(void *threadid) { //funcao que inicia com a thread
  int maxticket,i;
  long j;
  long tid;
  tid = (long)threadid;

  unsigned int semente;
  semente = tid;

  // Pre-protocolo: escrever aqui

  // Fim do pre-protocolo
  //secao critica
  for(j=1;j<CARGA*rand_r(&semente);j++); ////carga comput. artificial
  compart += (1+tid)*10;//incrementa var. global

  //printf("Thread #%ld, ticket=%d, incremento=%ld, compart=%ld\n", 
  // tid, ticket[tid], (1+tid)*10, compart);

  // pos-protocolo: escrever aqui

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
      ticket[i] = 0;
      //printf("Main: i=%ld\n",i);
      pthread_create(&threads[i], NULL, threadfunc, (void *) i);
    }

    for(i=0; i<MAX_THREADS; i++) {
      pthread_join(threads[i], NULL);
      //printf("Main: i=%ld, compart=%g\n",i, compart);
    }
  }

  if(compart!=7200){
	  printf("%ld\n",compart);
  }
  return 0;
}  
