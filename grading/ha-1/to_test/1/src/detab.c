//
// Created by Bogdan on 27.05.2018.
// Task 1.20

#include <stdio.h>
#include <stdlib.h>
#include "task.h"

char* detab(const char input[]) {
    int n = 0;
    while (input[n] != '\0') {
        n++;
    }

    char* output = malloc(n * 4 + 1);

    int i = 0;
    int j = 0;
    while (input[i] != '\0'){
        output[j] = input[i];

        if (input[i] == '\t') {
            for (int k = 0; k < 4; ++k) {
                output[j++] = ' ';
            }
            --j;
        }

        i++;
        j++;
    }

    output[j] = '\0';

    return output;
}
