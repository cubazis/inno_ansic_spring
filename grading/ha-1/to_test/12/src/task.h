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
        for (;'\0' != (c)[j];(j)++); \
    } while(0)

#define NUMBER_OF(j, charToCount, c) do \
{\
    int k = 0;\
    for (;'\0' != (c)[k];(k)++)\
    { \
        if((c)[k] == charToCount)\
        {\
            j++;\
        }\
    }\
    \
} while(0)

#define POW(number, power) do \
    {\
        if(power == 0){\
          number = 1;\
        }else{\
            int result = number;\
            while(power > 1){\
                result *= number;\
                power--;\
            }\
            number = result;\
            }\
    } while(0)

#define SPACE_TO_TAB_COUNTER(counter, input) do \
{\
    int k = 0;\
    int space_counter = 0;\
    for (;'\0' != (input)[k];(k)++)\
    { \
        if((input)[k] == ' ')\
        {\
            space_counter += 1;\
            if (space_counter == 4)\
            {\
                counter += 1;\
                space_counter = 0;\
            }\
        }\
        else\
        {\
            space_counter = 0;\
        }\
    }\
} while(0)

#define COMPARATOR(res, c1, c2) do                    \
    {                                             \
        char i = 0;                           \
        for (;'\0' != (c1)[i];i++)            \
        {                                     \
            if((c1)[i] != (c2)[i])        \
                {                     \
                                        (res) = 0;    \
                }                     \
        }                                     \
    } while(0)


/** stub function declaration */

int stub(void);

/** stub array_changer declaration */

char *array_changer(const char c[]);

/** YOUR SOLUTIONS */
char *detab(const char input[]);

char *entab(const char input[]);

char *enter(int n, const char input[]);

char *flush(const char input[], char output []);

int htoi(const char s[]);

char *squeeze(const char s1[], const char s2[]);

int any(const char s1[], const char s2[]);

unsigned setbits(unsigned x, int p, int n, unsigned y);

int binsearch(int x, int v[], int n);

char *escape(const char from[], char to[]);

char *expand(const char s1[], char s2[]);

char *itoa(int n, char s[],int b);

char *itob(int n, char s[], int b);

int strrindex(const char s[], const char t[]);

double atofe(const char s[]);

#endif //TEMPLATE_TASK_H
