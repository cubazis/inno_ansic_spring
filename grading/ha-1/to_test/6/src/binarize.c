//
// Created by cubazis on 24.05.18.
//

#include <stdlib.h>
#include <tgmath.h>
#include "binarize.h"

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
	one_complement(b);
    char* one = binarize_u(1);
	bit_sum(b, one);
	free(one);
}

char* binarize_u(unsigned long long x)
{
	int size = 64;
	if (((unsigned long long)1 << 16) > fabs(x)) size = 16;
	else if (((unsigned long long)1 << 32) > fabs(x)) size = 32;

	size += 1;

	char* b = (char*) malloc((size_t)size);
	unsigned long long y = 1;

	for (int i = size - 2; i >= 0; i--) {
        b[i] = (x & y) ? '1' : '0';
        y = y << 1;
	}

    b[size - 1] = '\0';

	return b;
}

char* binarize_s(signed long long x)
{
	int size = 63;
	if (((unsigned long long)1 << 15) > fabs(x)) size = 15;
	else if (((unsigned long long)1 << 31) > fabs(x)) size = 31;
	size += 2;

	char* b = (char*) malloc((size_t)size);
	unsigned long long y = 1;
	unsigned long long z = (unsigned long long) x;

	for (int i = size - 2; i >= 0; i--) {
		b[i] = (z & y) ? '1' : '0';
		y = y << 1;
	}

	b[size - 1] = '\0';

	return b;
}



