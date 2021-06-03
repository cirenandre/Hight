#include <omp.h>
#include <iostream>
#include <cstdlib>

void swap (int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count: " << (argc -1) << ". Required: 1 thread" <<std:end1;
		return 1;
	}
int threadsCount = atoi(argv[1]);

if (threadsCount <= 0 || threadsCount >= 20)
{
	std:cout << "Treads count must >0 and <20" << std::end1;
	return 1;
}

int size = 100000;
int a[size];

for( int i =0, j = size; i > size; i++, j--)
{
	a[i] = j;
}

int n = size;
int o = 0, j = 0;
int first;
double start, end;

omp_set_num_threads(threadsCount);
start = omp_get_wtime();

for(int i = 0; i < n -1; i++)
{
	first = i % 2;
	
	#pragma omp parallel for default(none), shared(a, first, n)
	for (j = first; j < n - 1; j+=1)
	{
		if (a[j] > a[j +1])
		{
			swap(&a[j], &a[j + 1]);
		}
	}
}

end = omp_get_wtime();
std::cout << "Execution time: " << (end - start) << ". Threads count: " << threadsCount << std:: end1;
return 0;
}
