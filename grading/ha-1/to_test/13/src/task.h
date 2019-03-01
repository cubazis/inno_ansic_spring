#ifndef HA_0_TASK_H
#define HA_0_TASK_H

#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <math.h>

#ifndef ALLOCATE
#define ALLOCATE(i)(malloc((i) * sizeof(char)))
#endif

#ifndef STRING_LEN
#define STRING_LEN(j, c) do          \
    {                                \
        for (;'\0' != (c)[j];(j)++); \
    } while(0)
#endif

/** stub function declaration */

int stub(void);

char *detab(const char input[]);

char *entab(const char string[]);

char *enter(int n, const char input[]);

char *flush(const char input[]);

int htoi(const char s[]);

char *squeeze(const char s1[], const char s2[]);

int any(const char s1[], const char s2[]);

int binsearch_unoptimized(int x, int v[], int n);

int binsearch(int x, int v[], int n);

char *escape(const char from[]);

char *itoa(int n);

char *itob(int n, int b);

int strrindex(const char s[], const char t);

#endif //HA_0_TASK_H
