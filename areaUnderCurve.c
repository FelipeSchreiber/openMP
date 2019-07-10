#include <stdio.h>
#include <omp.h>
static long num_steps = 1000;
#define NUM_THREADS 4
double step;

int main()
{
	step =  1.0/(double)num_steps;
	double pi, sum = 0.0;
	double time1,time2;
	double x;
	int i;
	time1 = omp_get_wtime();
	for(i = 0; i<num_steps; i++)
	{
		x = (i+0.5)*step;
		sum += 4.0/(1.0+x*x);
	}	
	time2 = omp_get_wtime();
	pi = sum*step;
	printf("\nPI:%.3f\n",pi);
	printf("\nTIME DIFF: %f\n",(time2 - time1));
	pi = sum = 0.0;	
	double individualOutput[NUM_THREADS];	
	int nthreads = 0;
	omp_set_num_threads(NUM_THREADS);	
	time1 = omp_get_wtime();
	#pragma omp parallel 
	{
		int nthrds = omp_get_num_threads();
		int j;
		int id = omp_get_thread_num();
		if(id == 0) nthreads = nthrds;
		for(j = id, individualOutput[id]=0.0;j<num_steps;j+=nthrds)
		{
			double y = (j+0.5)*step;
			individualOutput[id] += 4.0/(1.0+y*y);			
		}
	}
	time2 = omp_get_wtime();
	for(int i = 0;i<nthreads;i++)pi += individualOutput[i]*step;
	printf("\nPI:%.3f\n",pi);
	printf("\nTIME DIFF THREADS: %f\n",(time2 - time1));
}
