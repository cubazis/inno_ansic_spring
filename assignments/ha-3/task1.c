#include "stdio.h"

union randomValue
{
	double d[2];
	int in[4];
	char ch[16];
} myUnion;

int main(int argc, char const *argv[])
{
	//printf("%i\n", (int)sizeof(double));	
	//printf("%i\n", (int)sizeof(int));	
	//printf("%i\n", (int)sizeof(char));

	myUnion.d[0] = 1.6;
	myUnion.d[1] = 3.1415926;

	printf("%f\n", myUnion.d[0]);

	myUnion.in[0] = 134567;
	myUnion.in[1] = 208376;
	myUnion.in[2] = 3876;
	myUnion.in[3] = 4769;

	printf("%f\n", myUnion.d[0]);

	return 0;
}