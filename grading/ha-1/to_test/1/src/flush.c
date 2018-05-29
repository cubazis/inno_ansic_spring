//
// Created by George Watson on 28/05/2018.
//

#include "task.h"

// clear all the code from comments
char* flush(const char input[]) {
    int k = 0;
    char str[65534] = {0};
    int p = 0;
    int first = 1;

    // delete all comments
    for (;input[k] != '\0'; ++k) {
        // /* */ in prior.
        if (input[k] == '/' && input[k + 1] != '\0' && input[k + 1] == '*') {
            while (input[k + 1] != '\0')
                if (input[k] == '*' && input[k + 1] == '/') {k++; break;}
                else k++;
            k += 1;
        }
        // here goes // ..
        if (input[k] == '/' && input[k + 1] != '\0' && input[k + 1] == '/') {
            while (input[k + 1] != '\0' && input[k] != '\n') k++;
            if (first) k += 1;
        }
        // check for the first or not (need for deleting newline)
        if (input[k] != '\n') first = 0;
        else first = 1;
        str[p++] = input[k];
    }

    return (str);
}