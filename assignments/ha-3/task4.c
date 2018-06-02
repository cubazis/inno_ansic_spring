#include "stdio.h"

double mySin(double x)
{
	double value = x - (x*x*x)/6;
	return value;
}

double myCos(double x)
{
	double value = 1 - (x*x)/2;
	return value;
}

double myExp(double x)
{
	return 1 + x + x*x/2 + x*x*x/6;
}

int main(int argc, char const *argv[])
{
	int flag = 2; // 0 - sin; 1 - cos; 2 - exp
	double x = 1.34567890;

	double (*ptr[2])(double);

	ptr[0] = myCos;


	/*if (flag == 0)
	{
		ptr = mySin;
	}
	else if (flag == 1)
	{
		ptr = myCos;
	}
	else if (flag == 2)
	{
		ptr = myExp;
	}*/

	printf("%f\n", ptr[0](x));

	return 0;
}