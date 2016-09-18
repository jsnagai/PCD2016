#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define N 100000
#define max_thread 2

pthread_mutex_t sa; 
pthread_mutex_t so; 
pthread_mutex_t sb; 

void *p1(void *threadarg)
{
	sleep(0.25);
	pthread_mutex_lock(&sa);
	printf("C");
	pthread_mutex_unlock(&sb);
	printf("E");
	pthread_mutex_lock(&so);
	printf("O");
	pthread_exit(NULL);

}
void *p2(void *threadarg)
{

	printf("A");
	pthread_mutex_unlock(&sa);
	pthread_mutex_lock(&sb);
	printf("R");
	pthread_mutex_unlock(&so);
	pthread_exit(NULL);
}



int main(){
	int j,t,cj=0,rc;
	unsigned int seed =time(NULL);
	pthread_t p[2];
	pthread_mutex_lock(&sa);
	pthread_mutex_lock(&sb);
	pthread_mutex_lock(&so);
	struct timeval  inicio, final2;
	gettimeofday(&inicio, NULL);
	pthread_create(&p[0],NULL, &p1	,(void*)NULL);	
	pthread_create(&p[1],NULL, &p2	,(void*)NULL);	
	pthread_join(p[0],NULL);
	pthread_join(p[1],NULL);
	gettimeofday(&final2, NULL);
	//	printf("\n %lf:milisegundos",(double) (1000.0 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000.0));
	printf("\n");
	return 0;
}
