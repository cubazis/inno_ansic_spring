//
// Created by cubazis on 24.05.18.
//

#include "binarize.h"
#include "task.h"

void printBitSet(char b[])
{
	int i = 0, j = 0;
	while (b[i] != '\0'){
		if (j == 8 && (b[i+1] != '\0')){
			printf(" ");
			//printf("");
			j = 0;
		}
		printf("%c",b[i]);
		++j;
		++i;
	}
	printf("\n");
}



void bit_sum(char *b, char *o)
{
	int i = 0;
	while (b[i] != '\0'){
		++i;
	}
	--i;
	short int mask = 0;
	for (i; i >= 0 ; --i) {
		if(b[i] == '1' && o[i] == '1'){
			if(mask == 0){
				b[i] = '0';
				mask = 1;
			} else {
				b[i] = '1';
			}
		} else if ((b[i] == '1' && o[i] == '0') || (b[i] == '0' && o[i] == '1')){
			if(mask == 0){
				b[i] = '1';
			} else {
				b[i] = '0';
				mask = 1;
			}
		} else if (b[i] == '0' && o[i] == '0'){
			if(mask == 0){
				b[i] = '0';
			} else {
				b[i] = '1';
				mask = 0;
			}
		}
	}
}

void one_complement(char *b)
{
	int i = 0;
	while (b[i] != '\0'){
		if(b[i] == '1'){
			b[i] = '0';
		} else {
			b[i] = '1';
		}
		++i;
	}
}

void two_complement(char *b)
{
	/** YOUR CODE HERE */
}

char* binarize_u(unsigned long long x)
{
	int c, g, len, i = 0;
	unsigned long long k;

	if (x <= SCHAR_MAX*2+1)
	{
		g = 7;
		len = g + 2;
	}
	else if (x <= USHRT_MAX)
	{
		g = 15;
		len = g + 3;
	}
	else if (x <= UINT_MAX)
	{
		g = 31;
		len = g + 5;
	}
	else
	{
		g = 63;
		len = g + 9;
	}
	char *bin = ALLOCATE(len);

	for (c = g; c >= 0; c--)
	{
		k = x >> c;

		if (((c+1) % 8 == 0) && c != g)
			bin[i++] = ' ';
		if (k & 1)
			bin[i++] = '1';
		else
			bin[i++] = '0';
	}
	bin[i] = '\0';
 	return bin;
}

char* binarize_s(long long y)
{
	int c, g, len, i = 0;
	long long k;

	if (y <= SCHAR_MAX && y >= SCHAR_MIN)
	{
		g = 7;
		len = g + 2;
	}
	else if (y <= SHRT_MAX && y >= SHRT_MIN)
	{
		g = 15;
		len = g + 3;
	}
	else if (y <= INT_MAX && y >=  INT_MIN)
	{
		g = 31;
		len = g + 5;
	}
	else
	{
		g = 63;
		len = g + 9;
	}
	char *bin = ALLOCATE(len);

	for (c = g; c >= 0; c--)
	{
		k = y >> c;

		if (((c+1) % 8 == 0) && c != g)
			bin[i++] = ' ';
		if (k & 1)
			bin[i++] = '1';
		else
			bin[i++] = '0';
	}
	bin[i] = '\0';
	return bin;

}



