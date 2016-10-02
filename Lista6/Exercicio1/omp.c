/* ------------------------------------------------------------------------
 * FILE: least-squares.c
 * This program computes a linear model for a set of given data.
 *
 * PROBLEM DESCRIPTION:
 *  The method of least squares is a standard technique used to find
 *  the equation of a straight line from a set of data. Equation for a
 *  straight line is given by 
 *	 y = mx + b
 *  where m is the slope of the line and b is the y-intercept.
 *
 *  Given a set of n points {(x1,y1), x2,y2),...,xn,yn)}, let
 *      SUMx = x1 + x2 + ... + xn
 *      SUMy = y1 + y2 + ... + yn
 *      SUMxy = x1*y1 + x2*y2 + ... + xn*yn
 *      SUMxx = x1*x1 + x2*x2 + ... + xn*xn
 *
 *  The slope and y-intercept for the least-squares line can be 
 *  calculated using the following equations:
 *        slope (m) = ( SUMx*SUMy - n*SUMxy ) / ( SUMx*SUMx - n*SUMxx ) 
 *  y-intercept (b) = ( SUMy - slope*SUMx ) / n
 *
 * AUTHOR: Dora Abdullah (Fortran version, 11/96)
 * REVISED: RYL (converted to C, 12/11/96)
 * ---------------------------------------------------------------------- */
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define max_threads 4

int main(int argc, char **argv) {

	double *x, *y;
	double SUMx, SUMy, SUMxy, SUMxx, SUMres, res, slope,
		   y_intercept, y_estimate, xini, temp, sinal ;
	long int i,n;
	unsigned int seed;
	int aleat;
	double start, end;
	n = 100000000;
	x = (double *) malloc (n*sizeof(double));
	y = (double *) malloc (n*sizeof(double));

	seed = time(NULL);

	aleat =  rand_r(&seed);
	if (aleat > RAND_MAX/3) sinal = 1; else sinal = -1;

	for (i=0; i<n; i++) {
		x[i] = (float)i*10./(float)n;
		temp = (float)rand_r(&seed)/(float)RAND_MAX;
		aleat = rand_r(&seed);
		y[i] = temp*temp*sinal*(float)aleat;
	}


	omp_set_num_threads(max_threads);
	//input
	xini = 0.;
	start = omp_get_wtime();
	omp_set_dynamic(0);
#pragma omp parallel private(i,temp,aleat) shared(x,y) 
	{
		double lSUMx=0.0,lSUMy=0.0,lSUMxx=0.0,lSUMxy=0.0;
		int num = omp_get_thread_num();
#pragma omp for
		for (i=0; i<n; i++) {
			lSUMx = SUMx + x[i];
			lSUMy = SUMy + y[i];
			lSUMxy = SUMxy + x[i]*y[i];
			lSUMxx = SUMxx + x[i]*x[i];
		}
#pragma omp critical
		SUMx += lSUMx;
		SUMy += lSUMy;
		SUMxx += lSUMxx;
		SUMxy += lSUMxy;

#pragma omp barrier
		if(num == 0){
					slope = ( SUMx*SUMy - n*SUMxy ) / ( SUMx*SUMx - n*SUMxx );
					y_intercept = ( SUMy - slope*SUMx ) / n;

		}


	}
	end = omp_get_wtime();

	//Calculate

	printf ("\n");
	printf ("The linear equation that best fits the given data:\n");
	printf ("       y = %6.2lfx + %6.2lf\n", slope, y_intercept);
	printf("tempo: %lf", end - start);
}

