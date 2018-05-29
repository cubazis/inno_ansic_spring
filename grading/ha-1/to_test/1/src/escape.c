#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern size_t len(const char s[]);

char* escape(const char from[], char to[]) {
//    char* s = malloc(len(from)* sizeof(char)*2+1);
//    s[len(from)* sizeof(char)*2] = '\0';
    size_t c = 0;
    for(int i = 0; from[i] != '\0'; i++, c++) {
        switch(from[i]) {
            case '\t':
                to[c] = '\\';
                to[++c] = 't';
                break;
            case '\n':
                to[c] = '\\';
                to[++c] = 'n';
                break;
            default:
                to[c] = from[i];
                break;
        }
    }
    to[c] = '\0';
    return to;
}

