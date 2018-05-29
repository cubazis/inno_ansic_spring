//
// Created by cubazis on 25.05.18.
//

#include <stdbool.h>
#include <memory.h>
#include "task.h"

/** The stub function
 *  just to demonstrate how to work with ck_assert
 *  please look for test case for stub function in test_task.c
 */

int stub(void) {
    return 42;
}

/** The array_changer function
 *  just to demonstrate how to work with returning of array from function
 *
 *  1) C language doesn't have strings
 *  2) array in a C language is just a segment of memory
 *  3) C lang doesn't have ability to pass array as parameter in a function
 *  4) we suppose that you don't know about memory allocation through pointers
 *
 *  so, we provide you simple demo function which change 'c' char in input array
 *  	input parameter: constant array of chars
 *  	output: pointer to memory segment in which resulting array starts
 *
 *  	extra stuff: we provide you three define macros in task.h.
 *  		you can use them in your solutions
 *  		if you don't want to use them please, don't delete them - somebody may use it
 *
 *  please look for test case for array_changer function in test_task.c
 */

char *array_changer(const char c[]) {
    char j = 0;
    int size = 0;
    STRING_LEN(size, c);
    char *b = ALLOCATE(size);

    for (; j < size;) {
        if (c[j] == 'c')
            b[j] = 'b';
        else
            b[j] = c[j];
        j++;
    }
    return b;
}

/** YOUR SOLUTIONS */

char *detab(const char input[]) {
    /** JUST TO CHECK */
    char *c = ALLOCATE(10);
    return c;
}

char *entab(const char input[]) {
    int size = 0;
    STRING_LEN(size, input);

    char *c = ALLOCATE(size);

    int sp_count = 0;
    int in_index = 0;
    int c_index = 0;
    while (in_index < size) {
        if (input[in_index] == ' ') {
            sp_count++;
            if (sp_count == 4) {
                sp_count = 0;
                c[c_index] = '\t';
                c_index++;
            }
        } else {
            if (sp_count > 0) {
                while (sp_count > 0) {
                    c[c_index] = ' ';
                    c_index++;
                    sp_count--;
                }

            }
            c[c_index] = input[in_index];
            c_index++;
        }
        in_index++;
    }
    return c;
}

int htoi(const char s[]) {
    int size = 0;
    STRING_LEN(size, s);

    int integ = 0;
    int cur;
    int pow = 1;
    for (int i = size - 1; i >= 0; i--) {
        if (s[i] == 'x' || s[i] == 'X') {
            if (s[i - 1] == '0')
                break;
        }
        cur = s[i];
        if (cur >= 97 && cur <= 122) // If letter is small
            cur -= 87;
        else {
            if (cur >= 65 && cur <= 90) // If letter is capital
                cur -= 55;
            else {
                if (cur >= 48 && cur <= 57) { // If digit
                    cur -= 48;
                } else {
                    return -1; // Undefined behaviour
                }
            }
        }
        integ += cur * pow;
        pow *= 16;
    }
    return integ;
}

/**
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to
 * the rightmost n bits of y, leaving the other bits unchanged.
 * @param x initial bits
 * @param p start position of setting
 * @param n how many bits to set
 * @param y taking n most right bits from this
 * @return bits with replaced values
 */
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned y_mask = (unsigned) ((2 << (n - 1)) - 1);
    unsigned y_copy = y & y_mask;

    unsigned x_copy = x;
    unsigned x_mask = (unsigned) ((2 << (n - 1)) - 1);
    x_mask = x_mask << p - n + 1;
    y_copy = y_copy << p - n + 1;
    x_copy = x_copy & ~x_mask;
    x_copy = x_copy | y_copy;
    return x_copy;
}

/** Write the function any (s 1, s2 ), which returns the first location
in the string s 1 where any character from the string s2 occurs, or -1 if s 1
contains no characters from s2. (The standard library function strpbrk does
the same job but returns a pointer to the location.)
 **/
int any(const char s1[], const char s2[]) {
    int i;
    int j;
    bool b = 0;
    int location;

    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                location = i;
                return location;
            }
        }
    }

    if (b == 0) {
        return -1;
    }
}

/**
 * Write an alternate version of squeeze (s1,s2) that deletes
 * each character in s 1 that matches any character in the string s2
 */
char *squeeze(const char s1[], const char s2[]) {
    int i;
    int j;
    int k = 0;
    char *s3[sizeof(s1) + 1]; //s3 - array of letters were not met in s2
    int count_match = 0;
    for (i = 0; s1[i] != '\0'; i++) {

        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                count_match++;
            }

        }
        if (count_match == 0) { //if there were no such letter in 2nd string, add it to s3
            s3[k] = &s1[i];
            k++;
        }
        count_match = 0;
    }

    if (k == 0){ return "";}
    return *s3;
}

/**
 * Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1 into
 * the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to
 * handle cases like a-b-c and a-zO-9 and -a-z. Arrange that a leading or trailing - is taken literally
 * "-a-z" >> "-abc...xyz"
 * "a-z-" >>" abc...xyz-"
 * "a-b-c" >> "abc"
 * "a-z0-c" >> "abcdefghijklmnopqrstuvwxyz0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abc"
 * @param s1 input string
 * @return expanded string
 */
char *expand(const char s1[]) {
    int size = 0;
    int out_length = 0;
    int subrange_length = 0;
    short range = false; // Determines whether we're expanding the range (e.g. a-z)

    /* Calculate the length of input and output strings */
    for (; '\0' != s1[size]; size++) {
        if (s1[size] == '-') {
            // Are there symbols before and after the dash?
            if (size - 1 >= 0 && s1[size + 1] != '\0') {
                // Calculate how many symbols between these two
                subrange_length = s1[size + 1] - s1[size - 1] + 1;
                // In case if range is negative
                if (subrange_length < 0)
                    subrange_length *= -1;
                out_length += subrange_length;
                size++;
            } else
                out_length++;
        } else
            out_length++;
    }

    char *c = ALLOCATE(out_length);
    int out_ind = 0;
    for (int i = 0; i < size; i++) {
        if (s1[i] == '-') {
            if (i - 1 >= 0 && i + 1 < size) {
                for (char ch = s1[i - 1] + 1; ch < s1[i + 1]; ch++) {
                    c[out_ind] = ch;
                    out_ind++;
                }
            } else {
                c[out_ind] = s1[i];
                out_ind++;
            }
        } else {
            c[out_ind] = s1[i];
            out_ind++;
        }
    }
    c[out_ind] = '\0';
    return c;
}

int strrindex(const char s[], const  char t[]) {
    int s_size = 0;
    int t_size = 0;
    STRING_LEN(s_size, s);
    STRING_LEN(t_size, t);
    s_size -= 1;
    t_size -= 1;
    int i, j, k;
    int last_found = -1;

    for (i = s_size; s[i] != '\0'; i--) {
        for (j = i, k = t_size; t[k] != '\0' && s[j] == t[k]; j--, k--);
        if (k < 0)
            last_found = i;
    }
    return s_size - last_found;
}

int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2; //calculate mid beforehead
    while (low <= high && x != v[mid]) {
        if (x < v[mid]) //only 1 comparision
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low + high) / 2;
    }
    if (x == v[mid])
        return mid;
    else
        return -1;
}

char* escape(const char from[]) {
    char c;
    char a;
    char * to[2 * sizeof(from) + 1];
    int i = 0;
    int j = 0;

    while ((c = from[i]) != '\0') {
        switch (c) {
            case '\n':
                to[j++] =  "\\";
                to[j] = "n";
                j++;
                j++;
                i++;
                break;
            case '\t':
                to[j++] = "\\";
                to[j] = "t";
                j++;
                j++;
                i++;
                break;
            default:
                a = from[i];
                to[j] = &a;
                j++;
                i++;
                break;
        }
    }
    to[j] = '\0';
    return * to;}

char *itoa(int y) {
    int num = 0;
    while (y >= 1) {
        y = y / 2;
        num++;
    }
    char *binary[num + 1];
    int i = 0;
    bool minus = false;
    if (y < 0) {
        minus = true;
    }
    if (minus) {
        y = (-1 * y) - 1;
    }

    while (y >= 1) {
        char a = y % 2;
        binary[i] = &a;
        y = y / 2;
        i++;
    }

    char *answ[num + 1];
    int k = 0;

    if (minus) {
        for (int j = i - 1; j >= 0; j--) {
            char a = 1;
            if (binary[j] == &a) {
                answ[k] = 0;
                k++;
            } else { char a = 1;answ[k] = &a;k++; }
        }
    } else {
        for (int j = i - 1; j >= 0; --j) {
            answ[k] = binary[j];k++;
        }
    }

    return * answ;
}

/** Write the function itob (n,s ,b) that converts the integer n
into a base b character representation in the string s. In particular,
i tob (n,s, 16) formats nas a hexadecimal integer in s. 0
 **/

char * itob(int n, int b)
{
    int i;
    int sign;
    int r;
    char s[n];

    sign = n;
    i = 0;
    do {
        r = n % b;
        if (sign < 0)
            r = -r;
        s[i++] = (char) (r > 9 ? (r - 10 + 'A') : (r + '0'));
    } while (n /= b);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    int j;
    int t;

    for (j = 0; s[j] != '\0'; j++)
        ;
    for (i = 0, --j; j > i; i++, j--) {
        t = s[j];
        s[j] = s[i];
        s[i] = (char) t;
    }

    return s;
}

double atofe(const char s[])
{
    double res = 0.0, exponent = 0.0;
    int i = 0, c, sign = 1, flag = 0, k = 0;
    if(s[0] == '-')
        sign = -1;
    while( (c = s[i++]) != '\0')
    {
        if(c == 'e' || c =='E')
        {
            exponent = atof(&s[i]);
            break;
        }
        if(c == '.')
            flag = 1;
        else if(c >= '0' && c <= '9' )
        {
            if(flag == 1)
                ++k;
            res = (c - '0') + (res * 10);
        }
    }

    exponent -= k;

    if(exponent < 0)
        while(exponent++)
            res /= 10.0;
    else if(exponent > 0)
        while(exponent--)
            res *= 10.0;

    return sign * res;
}
/** GET FROM task.h */