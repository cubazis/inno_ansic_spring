//
// Created by Bogdan on 28.05.2018.
// Task 3.3

#include <stdlib.h>
#include <stdbool.h>
#include "task.h"

// expands list from a-z to abc...xyz
char* expand(const char s1[]) {
    char* output = malloc(1024);

    int starting_symbol = -1;
    int i = 0;
    int j = 0;

    while (s1[i] != '\0') {
        if (s1[i] == '-') {
            if (starting_symbol != -1 && s1[i + 1] != '\0' && s1[i + 1] != '-') {
                int ending_symbol = (int)(s1[i + 1]);

                j--;

                if (starting_symbol < ending_symbol) {
                    for (char c = starting_symbol; c <= ending_symbol; ++c) {
                        output[j++] = c;
                    }
                } else {
                    for (char c = starting_symbol; c >= ending_symbol; --c) {
                        output[j++] = c;
                    }
                }

                starting_symbol = ending_symbol;
                i++;
            } else {
                starting_symbol = -1;
                output[j++] = s1[i];
            }
        } else {
            starting_symbol = (int)(s1[i]);
            output[j++] = s1[i];
        }

        i++;
    }

    output[j] = '\0';

    return output;
}