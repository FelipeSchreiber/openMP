#include <omp.h>
#include <stdio.h>

int main()
{
	#pragma omp parallel
	{
  	int ID = omp_get_thread_num();
		printf("HELLO%i\n",ID);
		printf("WORLD%i\n",ID);
	}
	return 0;
}
