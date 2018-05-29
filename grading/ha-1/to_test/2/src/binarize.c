//
// Created by cubazis on 24.05.18.
//

#include "binarize.h"
#include <string.h>

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
    if (b[0] == '1') {
        int i = strlen(b) - 1;
        char carry = '0';
        if (b[i] == '1') {
            carry = '1';
            b[i] = '0';
        } else {
            b[i] = '1';
        }
        --i;
        while (carry == '1') {
            if (b[i] == '1') {
                b[i] = '0';
            } else {
                b[i] = '1';
                carry = '0';
            }
            --i;
        }
    }
}

char* binarize_u(unsigned long long x)
{
    int k = 0;
    char* res = malloc(64 + 1);

    if (x == 0) {
        res[k] = '0';
        ++k;
    }
    else {
        while (x > 0) {
            int mod = x % 2;
            res[k] = mod == 1 ? '1' : '0';
            x /= 2;
            ++k;
        }

        //reverse res array
        for (int i = 0; i <= (k - 1) / 2; ++i) {
            char buf = res[i];
            res[i] = res[k - 1 - i];
            res[k - 1 - i] = buf;
        }
    }
	res[k] = '\0';

    char* result;
    int p;
    if (k <= 16) {
        p = 16;
    }
    else if (k <= 32) {
        p = 32;
    }
    else if (k <= 64) {
        p = 64;
    }
    result = malloc(p + 1);
    char* temp = malloc(p - k + 1); // for forward zeros
    for (int i = 0; i < p - k; ++i) { temp[i] = '0'; }
    temp[p - k] = '\0';
    if (p != k) {
        strcpy(result, temp);
        result = strcat(result, res);
    }
    else {
        strcpy(result, res);
    }

	return result;
}

char* binarize_s(signed long long y)
{
    if (y >= 0) {
        return binarize_u(y);
    }
    int k = 0;
	char* res = malloc(64 + 1);

	unsigned long long yy;
	yy = -y;

    while (yy > 0) {
        int mod = yy % 2;
        res[k] = mod == 1 ? '1' : '0';
        yy /= 2;
        ++k;
    }

    res[k] = '0';

    //reverse res array
    for (int i = 0; i <= k / 2; ++i) {
        char buf = res[i];
        res[i] = res[k - i];
        res[k - i] = buf;
    }

    ++k;
    res[k] = '\0';
    one_complement(res);

    two_complement(res);

    if (res[1] == '1') {
        ++res;
        --k;
    }

    char* result;
    int p;
    if (k <= 16) {
        p = 16;
    }
    else if (k <= 32) {
        p = 32;
    }
    else if (k <= 64) {
        p = 64;
    }
    result = malloc(p + 1);
    char* temp = malloc(p - k + 1); // for forward ones
    for (int i = 0; i < p - k; ++i) { temp[i] = '1'; }
    temp[p - k] = '\0';
    if (p != k) {
        strcpy(result, temp);
        result = strcat(result, res);
    }
    else {
        strcpy(result, res);
    }

    return result;
}
