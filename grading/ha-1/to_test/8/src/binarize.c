//
// Created by cubazis on 24.05.18.
//

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
    int i = 0;
    while (b[i] != '\0'){
        if(b[i] == '1'){
            b[i] = '0';
        } else {
            b[i] = '1';
        }
        ++i;
    }

    --i;

    // Add 1
    int carryIn = 0;
    for (; i >= 0; --i) {
        if (b[i] != '1') {
            break;
        } else {
            if (carryIn == 0) {
                carryIn = 1;
                b[i] = '0';
            } else {
                b[i] = '1';
            }
        }
    }
}

char* binarize_u(unsigned long long x)
{

    // Store chars in result and j for checking how much binary digits have x
    char temp[64];
    int j = 63;

    // Initializing statement of result all zeros
    for (int i = 0; i < 64; i++) {
        temp[i] = '0';
    }

    /* While x is not equal to zero take its reminder.
     *
     * if it equals to 1 then result's jth cell is equal to 1
     * Otherwise it equals to 0
     *
     * Decrease j and divide x by two
    */
    while (x != 0) {
        if (x % 2) {
            temp[j] = '1';
        } else {
            temp[j] = '0';
        }
        x /= 2;
        j--;
    }

    int smth;
    if (63-j <= 16) {
        smth = 16;
    } else if (63-j <= 32) {
        smth = 32;
    } else {
        smth = 64;
    }

    char result[smth+1];
    result[smth] = '\0';
    char *res = result;

    for (int i = 0; i < smth; i++) {
        result[i] = '0';
    }

    for (int i = 0; j <= 63; j++) {
        result[i] = temp[j];
        i++;
    }

    return res;
}

char* binarize_s(signed long long y)
{
    if (y >= 0) {
        return binarize_u(y);
    } else {
        y *= -1;
        char* result = binarize_u(y);

        two_complement(result);
        return result;
    }
}