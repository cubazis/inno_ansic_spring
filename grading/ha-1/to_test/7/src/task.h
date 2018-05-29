//
// Created by cubazis on 25.05.18.
//

#ifndef TEMPLATE_TASK_H
#define TEMPLATE_TASK_H

#include <stdio.h>
#include "stdlib.h"

#ifndef ALLOCATE
#define ALLOCATE(i)(malloc((i) * sizeof(char)))
#endif

#ifndef STRING_LEN
#define STRING_LEN(j, c) do                \
	{                                  \
		for (;'\0' != (c)[j];(j)++); \
	} while(0)
#endif

/** stub function declaration */

int stub(void);

/** stub array_changer declaration */

char* array_changer(const char c[]);

/** YOUR SOLUTIONS */
char* detab(const char input[]);

char* entab(const char input[]);

char* enter(int n, const char input[]);

char* flush(const char input[]);

int htoi(const char s[]);

char* squeeze(const char s1[], const char s2[]);

int any(const char s1[], const char s2[]);

unsigned setbits(unsigned x, int p, int n, unsigned y);

int binsearch(int x, int v[], int n);

char* escape(const char from[]);

char* expand(const char s1[]);

char* itoa(int n);

char* itob(int n, int b);

int strrindex(const char s[], const  char t[]);

double atofe(const char s[]);

#endif //TEMPLATE_TASK_H
