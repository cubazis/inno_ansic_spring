#include "task.h"
#include <math.h>
#include <stdbool.h>

size_t len(const char s[]) {
    size_t i = 0;
    while(s[i] != '\0') i++;
    return i;
}

double _atof(const char s[], int len) {
    double n = .0;
    int i = 0, denominator = 10, sign = 1;
    bool dot_found = false;
    if(s[0] == '-') {
        sign = -1;
        i++;
    } else if(s[0] == '+') {
        i++;
    }

    for (; i < len; ++i) {
        if (s[i] == '.') {
            dot_found = true;
        } else {
            n += s[i]-'0';
            n *= 10;
            if (dot_found) {
                denominator *= 10;
            }
        }
    }

    return sign * n / denominator;
}



double atofe(const char s[]) {
    double n = .0;
    int i = 0, exponent = 0, exp_sign = 1;

    for (; s[i] != '\0' && s[i] != 'e' && s[i] != 'E'; ++i) {
        ;
    }
    n = _atof(s, i);

    if(s[++i] == '-') {
        exp_sign = -1;
        i++;
    } else if(s[i] == '+') {
        i++;
    }
    for(; s[i] != '\0'; ++i) {
        exponent += s[i] - '0';
        exponent *= 10;
    }
    exponent /= 10;
    return n * pow(10, exp_sign * exponent);
}