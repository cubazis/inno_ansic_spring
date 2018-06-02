#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
	int size = 10;
	int *array = (int*)malloc(sizeof(int)*size);
	
	for (int i = 0; i < size; ++i)
	{
		array[i] = i;
		printf("%i\n", array[i]);
	}

	int *pointer = array + size/2;

	printf("%i\n", pointer[0]);

	return 0;
}