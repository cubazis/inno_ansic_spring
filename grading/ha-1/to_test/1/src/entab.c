//
// Created by Bogdan on 27.05.2018.
// Task 1.21

#include <stdio.h>
#include <stdlib.h>
#include "task.h"

char* entab(const char input[]) {
    int n = 0;
    while (input[n] != '\0') {
        n++;
    }

    char* output = malloc(n * 4 + 1);

    int i = 0;
    int j = 0;
    int space_counter = 0;

    while (input[i] != '\0') {
        output[j] = input[i];

        if (input[i] == ' ') {
            space_counter++;
            if (space_counter == 4) {
                space_counter = 0;
                j -= 3;
                output[j] = '\t';
            }
        } else {
            space_counter = 0;
        }
        i++;
        j++;

    }

    output[j] = '\0';

    return output;
}
