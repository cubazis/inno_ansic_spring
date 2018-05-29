//
// Created by George Watson on 27/05/2018.
// Task 2.3

#include "task.h"
int number(char c);

// converts hexadecimal to integer
int htoi(const char s[]) {
    int res, c, d, p;
    p = 0;
    res = 0;
    STRING_LEN(p, s);

    // c and d needed for starting from the beginning of number
    c = (p > 2 && (s[1] == 'x' || s[1] == 'X')) ? 2 : 0;
    d = c ? c - 2 : 0;

    // goes through all digits and merge them
    for (;s[c] != '\0'; ++c) {
        res += number(s[c]) * (int)(pow(16, p - d - c - 1));
    }
    return res;
}

// explicit function for calculating the number for digit (e.g B == 11)
int number(char c) {
    return (c - '0') < 10 ? (c - '0') : (
            c - '0' < 23 ? c - '0' - 7 :
            c - '0' - 39
    );
}
