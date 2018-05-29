//
// Created by cubazis on 24.05.18.
//

#include <stdlib.h>
#include <string.h>
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



void bit_sum(char *b, const char *o)
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
	bit_sum(b, binarize_u(1));
}

char* binarize_u(unsigned long long x)
{
    size_t b_len = 33;
    char* b = malloc(b_len);
    memset(b, '0', b_len);
    b[b_len-1] = '\0';
    size_t i = b_len - 1 - 1;
    for (; i >= 0 && x != 0; --i) {
        b[i] = (char)(x % 2 + '0');
        x /= 2;
    }
    b[i] = (char)(x % 2 + '0');

    return b;
}

char* binarize_s(long long y)
{
    char* b = binarize_u(llabs(y));
    if (y < 0) two_complement(b);

    return b;
}



