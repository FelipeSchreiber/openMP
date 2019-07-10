#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
#define NUM_THREADS 4
double step;

int main()
{
	step =  1.0/(double)num_steps;
	double pi,time1,time2,full_sum;
	double sum[NUM_THREADS];
	int nthreads = 0,i,k;
	for(k = 1;k<=10;k++)
	{
		omp_set_num_threads(k);	
		full_sum = 0.0;
		time1 = omp_get_wtime();
		#pragma omp parallel private(i)
		{
			int nthrds = omp_get_num_threads();
			double partial_sum=0;
			double y;
			int id = omp_get_thread_num();
			#pragma omp single
				  printf(" num_threads = %d",nthrds); 
			if(id == 0) nthreads = nthrds;
			for(i = id;i<num_steps;i+=nthrds)
			{
				y = (i+0.5)*step;
				partial_sum = partial_sum + 4.0/(1.0+y*y);			
			}
			#pragma omp critical
		  		full_sum += partial_sum;
		}
		time2 = omp_get_wtime();		
		pi = step * full_sum;
		printf("\nPI:%.3f TIME DIFF THREADS: %f\n",pi, (time2 - time1) );
	}	
}
