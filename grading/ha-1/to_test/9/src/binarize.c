//
// Created by cubazis on 24.05.18.
//

#include <stdlib.h>
#include "binarize.h"

void printBitSet(char b[]) {
    int i = 0, j = 0;
    while (b[i] != '\0') {
        if (j == 8 && (b[i + 1] != '\0')) {
            printf(" ");
            //printf("");
            j = 0;
        }
        printf("%c", b[i]);
        ++j;
        ++i;
    }
    printf("\n");
}


void bit_sum(char *b, char *o) {
    int i = 0;
    while (b[i] != '\0') {
        ++i;
    }
    --i;
    short int mask = 0;
    for (i; i >= 0; --i) {
        if (b[i] == '1' && o[i] == '1') {
            if (mask == 0) {
                b[i] = '0';
                mask = 1;
            } else {
                b[i] = '1';
            }
        } else if ((b[i] == '1' && o[i] == '0') || (b[i] == '0' && o[i] == '1')) {
            if (mask == 0) {
                b[i] = '1';
            } else {
                b[i] = '0';
                mask = 1;
            }
        } else if (b[i] == '0' && o[i] == '0') {
            if (mask == 0) {
                b[i] = '0';
            } else {
                b[i] = '1';
                mask = 0;
            }
        }
    }
}

void one_complement(char *b) {
    int i = 0;
    while (b[i] != '\0') {
        if (b[i] == '1') {
            b[i] = '0';
        } else {
            b[i] = '1';
        }
        ++i;
    }
}

void two_complement(char *b) {
    one_complement(b);
    int i = 0;
    while (b[i] != '\0') {
        ++i;
    }
    --i;
    while (i >= 0) {
        if (b[i] == '1') {
            b[i] = '0';
            i--;
        } else {
            b[i] = '1';
            break;
        }
    }

}

char *binarize_u(unsigned long long x) {
    int size;

    if (x <= USHRT_MAX) {
        size = sizeof(unsigned short int) * 8 - 1;
    } else if (x <= UINT_MAX) {
        size = sizeof(unsigned int) * 8 - 1;
    } else {
        size = sizeof(unsigned long long) * 8 - 1;
    }
    char *res = malloc(sizeof(char) * size);
    res[size + 1] = '\0';
    int i = size;

    while (x > 0) {
        res[i--] = (char) ((x % 2) + '0');
        x = x / 2;
    }
    while (i >= 0) {
        res[i--] = '0';
    }
    return res;
}

char *binarize_s(signed long long y) {
    int size;

    if (y > 0) {
        if (y <= SHRT_MAX) {
            size = sizeof(signed short int) * 8 - 1;
        } else if (y <= INT_MAX) {
            size = sizeof(signed int) * 8 - 1;
        } else {
            size = sizeof(signed long long) * 8 - 1;
        }
    } else {
        if (y >= SHRT_MIN) {
            size = sizeof(signed short int) * 8 - 1;
        } else if (y >= INT_MIN) {
            size = sizeof(signed int) * 8 - 1;
        } else {
            size = sizeof(signed long long) * 8 - 1;
        }
    }
    char *res = malloc(sizeof(char) * size);
    res[size + 1] = '\0';
    int i = size;

    int sign;
    if (y > 0) {
        sign = 0;
    } else {
        sign = 1;
        y *= -1;
    }

    while (y > 0) {
        res[i--] = (char) ((y % 2) + '0');
        y = y / 2;
    }
    while (i >= 0) {
        res[i--] = '0';
    }
    if (sign) {
        two_complement(res);
    }
    return res;
}



