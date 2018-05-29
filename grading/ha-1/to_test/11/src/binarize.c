//
// Created by cubazis on 24.05.18.
//

#include <stdbool.h>
#include <stdlib.h>
#include "binarize.h"
#include "task.h"

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
    int i = 0;
    while (b[i] != '\0') {
        if (b[i] == '1') {
            b[i] = '0';
        } else {
            b[i] = '1';
        }
        ++i;
    }
    for (i--; i >= 0; i--) {
        b[i]++;
        if (b[i] == '2')
            b[i] = '0';
        else break;
    }
}

char *binarize_u(unsigned long long x) {
    char a[100];
    for (int i = 0; i < 100; i++) {
        a[i] = '0';
    }
    bool is_l = false;
    bool is_ll = false;
    for (int i = 0; i < 16; i++) {
        a[i] = x % 2 + '0';
        x /= 2;
    }
    if (x != 0) {
        for (int i = 16; i < 32; i++) {
            a[i] = x % 2 + '0';
            x /= 2;
        }
        is_l = true;
    }

    if (x != 0) {
        for (int i = 32; i < 64; i++) {
            a[i] = x % 2 + '0';
            x /= 2;
        }
        is_ll = true;
    }

    char *b = malloc((is_ll ? 65 : (is_l ? 32 : 17)) * sizeof(char));
    for (int i = (is_ll ? 63 : (is_l ? 31 : 15)), j = 0; i >= 0;) {
        b[j++] = a[i--];
    }
    b[(is_ll ? 64 : (is_l ? 32 : 16))] = '\0';
    return b;

}

char *binarize_s(signed long long x) {

    if (x == -32768) return "1000000000000000";
    if (x == -2147483648) return "10000000000000000000000000000000";
    if (x == -9223372036854775808) return "1000000000000000000000000000000000000000000000000000000000000000";

    bool is_negative = x < 0;
    x = llabs(x);
    char a[100];
    for (int i = 0; i < 100; i++) {
        a[i] = '0';
    }
    bool is_l = false;
    bool is_ll = false;
    for (int i = 0; i < 15; i++) {
        a[i] = x % 2 + '0';
        x /= 2;
    }
    if (x != 0) {
        for (int i = 15; i < 31; i++) {
            a[i] = x % 2 + '0';
            x /= 2;
        }
        is_l = true;
    }

    if (x != 0) {
        for (int i = 31; i < 63; i++) {
            a[i] = x % 2 + '0';
            x /= 2;
        }
        is_ll = true;
    }

    if (is_negative) {
        for (int i = 0; i < (is_ll ? 64 : (is_l ? 32 : 16)); i++) {
            a[i] = (a[i] == '1' ? '0' : '1');
        }

        for (int i = 0; i < (is_ll ? 64 : (is_l ? 32 : 16)); i++) {
            a[i]++;
            if (a[i] == '2')
                a[i] = '0';
            else break;
        }
    }

    char *b = malloc((is_ll ? 65 : (is_l ? 33 : 17)) * sizeof(char));
    for (int i = (is_ll ? 63 : (is_l ? 31 : 15)), j = 0; i >= 0;) {
        b[j++] = a[i--];
    }
    b[(is_ll ? 64 : (is_l ? 32 : 16))] = '\0';
    return b;
}



