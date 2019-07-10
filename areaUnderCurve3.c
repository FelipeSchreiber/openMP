#include <stdio.h>
#include <omp.h>
static long num_steps = 1000;
#define NUM_THREADS 3
double step;

int main()
{
	step =  1.0/(double)num_steps;
	//OMP_WAIT_POLICY=passive;
	double pi;
	int j;
	double avg_time = 0.0;
	#pragma omp parallel for reduction (+:avg_time)	schedule(auto)	num_threads(NUM_THREADS)
		for(j = 0;j<1000;j++)
		{	
			int i;		
			double time1,time2;
			double sum = 0,x;
			time1 = omp_get_wtime();
			#pragma omp parallel for reduction (+:sum) num_threads(NUM_THREADS) schedule(auto)
				for(i = 0; i<num_steps; i++)
				{
					x = (i+0.5)*step;
					sum += 4.0/(1.0+x*x);
				}
				time2 = omp_get_wtime();
				pi = sum*step;
				avg_time += (time2 - time1);
		}	
	
	printf("\nPI:%.8f\n",pi);
	printf("\nTIME DIFF AVG: %f\n",avg_time/1000);
	//printf("\nTOTAL CORES: %i\n",(int)omp_num_procs());
	//pi = sum = 0.0;	
}
