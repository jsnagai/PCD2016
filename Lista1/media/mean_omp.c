/*
 * =====================================================================================
 *
 *       Filename:  exercicio11.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23/08/2016 11:14:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#define N 10000000
#define max_threads 1


int main(){
	double sum;
	int i,j;
	double *arr1;
	arr1 = (double*)malloc(N*sizeof(double));

	unsigned int seed=time(NULL);
	
	double start, end;
	omp_set_num_threads(max_threads); 
	int aux;
	start = omp_get_wtime();
#pragma omp parallel default(none) private(i,j,seed) shared(arr1) reduction(+:sum)
	{
		for(i=0;i<N;i+=max_threads){
			arr1[i]=rand_r(&seed);
			sum+=arr1[i];
		}
	}
		
	end = omp_get_wtime();
	printf("media: %lf tempo : %lf",sum/N,end-start);
	
		return 0;

}





