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
	int i = 0, j = 0;
	while (b[i] != '\0'){
		++i;
	}
	char one[i];
	while (j < i){
		one[j] = '0';
		++j;
	}
	one[j-1] = '1';
	one[j] = '\0';
	one_complement(b);
	bit_sum(b, one);
}

char* binarize_u(unsigned long long x)
{
	unsigned long long mask = 1;
	int size;
/*    if(x <= 255){
        size = 1 * 8 - 1;
    }
    else */if(x <= USHRT_MAX){
		size = sizeof(unsigned short int) * 8 - 1;
	} else if(x <= UINT_MAX){
		size = sizeof(unsigned int) * 8 - 1;
	} else{
		size = sizeof(unsigned long long) * 8 - 1;
	}
	mask <<= size;
	char* c = ALLOCATE(size);
	int j = 0, i;
	while (j <= size){
		c[j] = '0';
		++j;
	}
	for(j = 0, i = size; j <= size; ++j, --i)
	{
		c[j] = (char) ((x & mask) ? '1' : '0');
		x <<= 1;
	}
	c[j] = '\0';
	return c;
}

char* binarize_s(signed long long y)
{
	int sign = 0;
	unsigned long long x;
	if(y < 0) {
		if(y == LONG_MIN){
			x = LONG_MAX+1;
		} else {
			x = (unsigned long long)(-y);
		}
		sign = 1;
	} else {
		x = (unsigned long long)y;
	}
	unsigned long long mask = 1;
	int size;
/*    if(x <= 255){
        size = 1 * 8 - 1;
    }
    else */ if(x <= USHRT_MAX){
		size = sizeof(unsigned short int) * 8 - 1;
	} else if(x <= UINT_MAX){
		size = sizeof(unsigned int) * 8 - 1;
	} else{
		size = sizeof(unsigned long long) * 8 - 1;
	}
	mask <<= size;
	char* c = ALLOCATE(size);
	int j = 0, i;
	while (j <= size){
		c[j] = '0';
		++j;
	}
	for(j = 0, i = size; j <= size; ++j, --i)
	{
		c[j] = (char) ((x & mask) ? '1' : '0');
		x <<= 1;
	}
	c[j] = '\0';
	if(sign == 1){
		two_complement(c);
	}
	return c;
}



