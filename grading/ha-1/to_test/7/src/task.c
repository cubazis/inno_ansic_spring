//
// Created by cubazis on 25.05.18.
//

#include <stdbool.h>
#include "task.h"
#include <limits.h>

/** The stub function
 *  just to demonstrate how to work with ck_assert
 *  please look for test case for stub function in test_task.c
 */

int stub(void)
{
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

char* array_changer(const char c[])
{
	char j = 0;
	int size = 0;
	STRING_LEN(size, c);
	char* b = ALLOCATE(size);

	for (;j < size;) {
		if(c[j] == 'c')
			b[j] = 'b';
		else
			b[j] = c[j];
		j++;
	}
	return b;
}

/** YOUR SOLUTIONS */

char* detab(const char input[])
{
	/** JUST TO CHECK */
    int size = 0,tabs=0;
    STRING_LEN(size, input);

    for(int i=0;i<size;i++){
        if(input[i]=='\t')
            tabs++;
    }
    int new_size=size+tabs*3;
	char* c = ALLOCATE(new_size+1);
	int j=0;
	for(int i=0;i<size;i++){
        if (input[i] == '\t') {
            for (int k = 0; k < 4; k++)
                c[j++] = ' ';
        } else
            c[j++] = input[i];
	}
	c[j]='\0';
	return c;
}

int htoi(const char s[]) {
    int i = 0, n;
    n = 0;
    if (s[0] == '0')
        if (s[1] == 'x' || s[1] == 'X')
            i = 2;
    for (i; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F'); i++)
        if (s[i] >= '0' && s[i] <= '9')
            n = 16 * n + (s[i] - '0');
        else if (s[i] >= 'a' && s[i] <= 'f')
            n = 16 * n + (s[i] - 'a' + 10);
        else if (s[i] >= 'A' && s[i] <= 'F')
            n = 16 * n + (s[i] - 'A' + 10);
    return n;
}


char *escape(const char from[]) {
    int n = 0;
    int i = 0;
    int j = 0;
    char c;
    while ((c = from[n]) != '\0') n++;

    char *to = malloc((2 * n) * sizeof(char));
    while ((c = from[i]) != '\0') {
        switch (c) {
            case '\n':
                to[j++] = '\\';
                to[j++] = 'n';
                break;
            case '\t':
                to[j++] = '\\';
                to[j++] = 't';
                break;
            case '\a':
                to[j++] = '\\';
                to[j++] = 'a';
                break;
            case '\b':
                to[j++] = '\\';
                to[j++] = 'b';
                break;
            case '\v':
                to[j++] = '\\';
                to[j++] = 'v';
                break;
            case '\f':
                to[j++] = '\\';
                to[j++] = 'f';
                break;
            case '\r':
                to[j++] = '\\';
                to[j++] = 'r';
                break;
            case '\'':
                to[j++] = '\\';
                to[j++] = '\\';
                break;
            default:
                to[j++] = from[i];
                break;
        }

        i++;
    }
    to[j] = '\0';
    return
            to;
}

char *entab(const char input[]) {
    int size = 0;
    STRING_LEN(size, input);
    char *c = ALLOCATE(size + 1);

    int i, k;
    for (i = 0, k = 0; i < size; i++, k++) {
        if (i < (size - 3) && input[i] == ' ' && input[i + 1] == ' ' && input[i + 2] == ' ' &&
            input[i + 3] == ' ') {
            c[k] = '\t';
            i += 3;
        } else c[k] = input[i];
    }

    c[k] = '\0';
    return c;
}

char *expand(const char s1[]) {

    int size = 0, new_size = 0;
    STRING_LEN(size, s1);

    for (int i = 0; i < size; i++) {
        if (s1[i + 1] == '-' && s1[i + 2] != '\0' && s1[i] <= s1[i + 2] &&
            (('a' <= s1[i] && s1[i] <= 'z') || ('A' <= s1[i] && s1[i] <= 'Z') ||
             ('0' <= s1[i] && s1[i] <= '9')) &&
            (('a' <= s1[i + 2] && s1[i + 2] <= 'z') || ('A' <= s1[i + 2] && s1[i + 2] <= 'Z') ||
             ('0' <= s1[i + 2] && s1[i + 2] <= '9'))) {
            new_size += s1[i + 2] - s1[i] + 1;
            i += 1;
        } else {
            new_size++;
        }
    }

    char *c = ALLOCATE(new_size + 1);

    int j = 0, last_used = 0;
    for (int i = 0; s1[i] != '\0'; ++i) {
        if (s1[i + 1] == '-' && s1[i + 2] != '\0' && s1[i] <= s1[i + 2] &&
            (('a' <= s1[i] && s1[i] <= 'z') || ('A' <= s1[i] && s1[i] <= 'Z') ||
             ('0' <= s1[i] && s1[i] <= '9')) &&
            (('a' <= s1[i + 2] && s1[i + 2] <= 'z') || ('A' <= s1[i + 2] && s1[i + 2] <= 'Z') ||
             ('0' <= s1[i + 2] && s1[i + 2] <= '9'))) {
            int k = 0;
            if (last_used)
                k++;
            while (k <= s1[i + 2] - s1[i])
                c[j++] = (char) (s1[i] + k++);
            if ((s1[i + 3] != '\0' && s1[i + 3] == '-') && (s1[i + 4] != '\0') && s1[i + 2] <= s1[i + 4] &&
                (('a' <= s1[i + 2] && s1[i + 2] <= 'z') || ('A' <= s1[i] && s1[i] <= 'Z') ||
                 ('0' <= s1[i + 2] && s1[i + 2] <= '9')) &&
                (('a' <= s1[i + 4] && s1[i + 4] <= 'z') || ('A' <= s1[i + 4] && s1[i + 4] <= 'Z') ||
                 ('0' <= s1[i + 4] && s1[i + 4] <= '9'))) {
                i++;
                last_used = 1;
            } else {
                i += 2;
                last_used = 0;
            }
        } else {
            c[j++] = s1[i];
        }
    }
    c[j] = '\0';
    return c;
}

int strrindex(const char s[], const char t[]) {
    int size_s = 0;
    int size_t = 0, last = -1;
    int consist = 0;

    STRING_LEN(size_s, s);

    STRING_LEN(size_t, t);
    if (size_t > size_s) return -1;
    for (int i = 0; i <= size_s - size_t; i++) {
        if (s[i] == t[0]) {
            consist = 1;
            int p = i;

            for (int j = 0; j < size_t; j++) {
                if (s[p] != t[j]) {
                    consist = 0;
                    break;
                }
                p++;
            }
            if (consist == 1)
                last = i;
        }
    }
    return last;
}

char *enter(int n, const char input[]) {
    int size = 0;
    STRING_LEN(size, input);

    int newlines = size / n;
    char *res = ALLOCATE(size + newlines);

    int count = 0;
    int pos = 0;
    for (int i = 0; i < size; ++i) {
        if (input[i] == '\n') {
            count = 0;
            res[pos++] = input[i++];
        } else if (count == n) {
            count = 0;
            res[pos++] = '\n';
        }
        count++;
        res[pos++] = input[i];
    }
    res[pos] = '\0';
    return res;
}

char *squeeze(const char s1[], const char s2[]) {
    int size1 = 0;
    STRING_LEN(size1, s1);
    char *res = ALLOCATE(size1);

    int size2 = 0;
    STRING_LEN(size2, s2);

    short isin;
    int i, j, pos = 0;
    for (i = 0; i < size1; ++i) {
        isin = 0;
        for (j = 0; j < size2; ++j) {
            if (s1[i] == s2[j]) {
                isin = 1;
            }
        }
        if (!isin)
            res[pos++] = s1[i];
    }
    res[pos] = '\0';

    return res;
}

int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (v[mid] < x)
            low = mid + 1;
        else
            high = mid;
    }
    if (v[high] == x)
        return high;
    return -1;
}

int reqmem(int n) {
    int size = 0;
    if (n <= 0)
        ++size;
    while (n != 0) {
        n /= 10;
        ++size;
    }
    return size;
}

char *itoa(int n) {
    int pos, sign, isminint = 0;
    int size = reqmem(n) + 1;
    char *s = ALLOCATE(size);

    if (n == INT_MIN) {
        n = n + 1;
        isminint = 1;
    }
    if ((sign = n) < 0)
        n = -n;

    pos = 0;
    do {
        s[pos++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) {
        s[pos++] = '-';
    }

    if (isminint) {
        s[0]++;
    }

    int c, i, j = size - 1;
    for (i = 0, --j; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    s[pos] = '\0';
    return s;
}

#define true 1
#define false 0

char *flush(const char input[]) {
    //size of input string
    int size = 0;
    int i = 0;
    int j = 0;
    // it's 0 if loop is in quotes, otherwise - 1
    int closed = true;

    STRING_LEN(size, input);
    char *b = ALLOCATE(size);

    for (; i < size;) {
        // if we reached end of string
        if (input[i] == '\0') {
            b[j] = input[i];
            break;
            // if we entered in the quotes
        } else if (input[i] == '\"') {

            // reverse it when enter/exit quotes
            if (closed == true) {
                closed = false;
            } else {
                closed = true;
            }

            b[j++] = input[i++];
            //if we reached // comment
        } else if (input[i] == '/' && input[i + 1] == '/' && closed == true) {
            i += 2;
            // skip all char until end of line
            while (input[i] != '\n' && input[i] != '\0') {
                ++i;
            }
            // if we reach /** comment
        } else if (input[i] == '/' && input[i + 1] == '*' && closed == true) {
            i += 2;
            // skip all chars until end of comment */
            while ((input[i] != '*' || input[i + 1] != '/') && input[i] != '\0') {
                ++i;
            }
            //delete */ chars at the end of comment
            if (input[i] == '*') {
                i += 2;
            }
        } else {
            b[j++] = input[i++];
        }
    }

    return b;
}

int any(const char s1[], const char s2[]) {
    int i = 0;
    int j;

    //check every char in s2
    while (s2[i] != '\0') {
        j = 0;
        //iterate through the s1 in order to find s2[i]
        while (s1[j] != '\0') {
            //checks equality of symbols
            if (s2[i] == s1[j]) {
                return j;
            }
            j++;
        }
        i++;
    }
    // if there is no match
    return -1;
}

char *itob(int n, int b) {
    int quotient, remainder, i, j, size;
    char tmp;

    size = 0;
    quotient = n;
    while (quotient != 0) {
        size++;
        quotient = quotient / b;
    }
    char *arr = ALLOCATE(size + 1);

    //restriction on bases is 36
    //function can convert integers into bases no more that 36
    char base[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (b < 2 || b > 36) {

        return "";

    } else if (n == 0) {
        return "0";
    } else {

        quotient = n;

        if (n < 0) {
            quotient = 0 - quotient;
        }

        i = 0;

        while (quotient != 0) {
            remainder = quotient % b;
            arr[i++] = base[remainder];
            quotient = quotient / b;
        }

        if (n < 0) {
            arr[i++] = '-';
        }

        arr[i--] = '\0';

        j = 0;

        while (j < i) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            ++j;
            --i;
        }
        return arr;
    }
}

/** GET FROM task.h */