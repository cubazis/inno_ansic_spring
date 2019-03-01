#ifndef TEMPLATE_TASK_H
#define TEMPLATE_TASK_H

#include <stdio.h>
#include "stdlib.h"

#define ALLOCATE(i)(malloc((i) * sizeof(char)))

#define STRING_LEN(j, c) do                \
	{                                  \
		for (;'\0' != (c)[j];(j)++); \
		(j) = j;                   \
	} while(0)

#define STRING_COPY(a, b, len) do 			\
	{						 				\
		(b) = "";				 			\
		for(int i = 0; i < (len); i++) {	\
			(b) = (a)[(len) - 1 - i] + (b);	\
		}									\
	} while (0)

#define COMPARATOR(res, c1, c2) do                    \
	{                                             \
		char i = 0;                           \
		for (;'\0' != (c1)[i];i++)            \
		{                                     \
			if((c1)[i] != (c2)[i])        \
				{                     \
                                        (res) = 0;    \
				}                     \
			else                          \
				{                     \
                                        (res) = 1;    \
				}                     \
		}                                     \
	} while(0)


int stub(void);

char* array_changer(const char c[]);

char* detab(const char input[]);

char* entab(const char input[]);

char* enter(int n, const char input[]);

char* flush(const char input[]);

int htoi(const char s[]);

char* squeeze(const char s1[], const char s2[]);

int any(const char s1[], const char s2[]);

unsigned setbits(unsigned x, int p, int n, unsigned y);

int binsearch(int x, int v[], int n);

char* escape(char* from);

char* expand(char* s);

char* itoa(int n, const char s[]);

char* itob(int n, const char s[], int b);

int strrindex(char* s, char* t);

double atofe(const char s[]);

#endif //TEMPLATE_TASK_H
