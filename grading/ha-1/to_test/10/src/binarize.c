//
// Created by cubazis on 24.05.18.
//

#include <malloc.h>
#include <memory.h>
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
    size_t n = strlen(b);
    char* one = (char*) malloc(n);
    one[n] = '\0';
    one[n-1] = '1';
    for(int i = (int) (n - 2); i >= 0; i--)
    {
        one[i] = '0';
    }
    bit_sum(b, one);
    free(one);
}

unsigned int calculateCountOfBits(long long number)
{
    unsigned int countBit = 16;
    unsigned long long maxCapacity = 65536;
    while (maxCapacity < number)
    {
        countBit += 1;
        maxCapacity *= 2;
    }
    unsigned int i = 1;
    while(i < countBit) i *= 2;
    return i;
}

char* binarize_u(unsigned long long x)
{
    unsigned int countBit = calculateCountOfBits(x);
    char * bReverseNumber = (char*) malloc(sizeof(char) * countBit);
    bReverseNumber[countBit] = '\0';
    int i = countBit - 1;
    while (i >= 0) {
        bReverseNumber[i] = (char) ((x % 2) + '0');
        i--;
        x = x / 2;
    }
    return bReverseNumber;
}

char* binarize_s(signed long long y)
{
	if(y < 0)
	{
		y *= -1;
		char * bNumber = binarize_u((unsigned long long int) y);
        two_complement(bNumber);
        return bNumber;
	}
	else
	{
		return binarize_u(y);
	}
}



