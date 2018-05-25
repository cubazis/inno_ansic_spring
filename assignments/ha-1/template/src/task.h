//
// Created by cubazis on 25.05.18.
//

#ifndef TEMPLATE_TASK_H
#define TEMPLATE_TASK_H

#include <stdio.h>
#include "stdlib.h"

#define ALLOCATE(i)(malloc((i) * sizeof(char)))

#define STRING_LEN(j, c) do                \
	{                                  \
		for (;'\0' != (c)[i];i++); \
		(j) = i;                   \
	} while(0)                         \

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


/** stub function declaration */

int stub(void);

/** stub array_changer declaration */

char* array_changer(const char c[]);

/** YOUR SOLUTIONS */
char* detab(const char input[]);

char* entab(const char input[]);

char* enter(int n, const char input[]);

char* flush(const char input[]);


#endif //TEMPLATE_TASK_H
