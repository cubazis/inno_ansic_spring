#include <math.h>
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
    char i = 0, j = 0;
    STRING_LEN(i, c);
    char *b = ALLOCATE(i);

    for (; j < i;) {
        if (c[j] == 'c')
            b[j] = 'b';
        else
            b[j] = c[j];
        j++;
    }
    return b;
}

char *detab(const char input[]) {
    int size = 0;
    STRING_LEN(size, input);
    int tabs = 0;
    for (int i = 0; i < size; i++)
        if (input[i] == '\t') tabs++;
    int size_with_tabs = size + 3 * tabs + 1;

    char *detabbed = (char *) ALLOCATE(size_with_tabs);
    for (int i = 0, k = 0; i < size; i++, k++) {
        if (input[i] == '\t') {
            detabbed[k] = ' ';
            detabbed[k + 1] = ' ';
            detabbed[k + 2] = ' ';
            detabbed[k + 3] = ' ';
            k += 3;
        } else detabbed[k] = input[i];
    }
    detabbed[size_with_tabs - 1] = '\0';

    return detabbed;
}

char *entab(const char input[]) {
    // 	I'm too lazy to write efficient code, sry
    int number_eligible_spaces = 0;
    int input_size = 0;
    STRING_LEN(input_size, input);
    for (int i = 0; i < (input_size - 3) && input_size >= 4; i++) {
        if (input[i] == ' ' && input[i + 1] == ' ' && input[i + 2] == ' ' && input[i + 3] == ' ') {
            number_eligible_spaces++;
            i += 4;
        }
    }

    int final_size = input_size - (number_eligible_spaces * 3) + 1;
    char *result = ALLOCATE(final_size);

    for (int i = 0, k = 0; i < input_size; i++, k++) {
        if (i < (input_size - 3) && input[i] == ' ' && input[i + 1] == ' ' && input[i + 2] == ' ' &&
            input[i + 3] == ' ') {
            result[k] = '\t';
            i += 3;
        } else result[k] = input[i];
    }

    result[final_size - 1] = '\0';
    return result;
}

char *enter(int n, const char input[]) {
    int input_size = 0;
    STRING_LEN(input_size, input);
    int enters = 0, new_size = 0;
    char *result;

    if ((n == 0) || (input_size / n) == 0) {
        result = ALLOCATE(input_size + 1);
        for (int i = 0; i < input_size; i++)
            result[i] = input[i];
        result[input_size] = '\0';
        return result;
    }

    enters = input_size / n;
    new_size = input_size + enters + 1;

    result = ALLOCATE(new_size);

    for (int i = 0, k = 0; k < new_size; i++, k++) {
        if ((n == 1 && (k % 2) == 1) || (k != 0 && ((k - ((i - 1) / n)) % n) == 0 && n != 1)) {
            result[k] = '\n';
            i--;
            continue;
        }
        result[k] = input[i];
    }

    result[new_size - 1] = '\0';
    return result;
}

char *flush(const char input[]) {
    int input_size = 0;
    STRING_LEN(input_size, input);
    char *result = ALLOCATE(input_size + 1);

    int in_comment = 0;
    for (int i = 0, k = 0; i < input_size; i++, k++) {
        if (input[i] == '/' && (i + 1 < input_size) && in_comment == 0) {
            if (input[i + 1] == '/') {
                in_comment = 1;
                k--;
            } else if (input[i + 1] == '*') {
                in_comment = 2;
                k--;
            } else {
                result[k] = input[i];
            }
        } else if ((input[i] == '\n' && in_comment == 1)) {
            in_comment = 0;
            result[k] = input[i];
        } else if (input[i] == '/' && i > 0 && in_comment == 2 && input[i - 1] == '*') {
            in_comment = 0;
            k--;
        } else if (in_comment == 0) {
            result[k] = input[i];
        } else k--;

        if (i + 1 == input_size) result[k + 1] = '\0';
    }

    return result;
}

int htoi(const char s[]) {
    int result = 0;
    int input_size = 0;
    STRING_LEN(input_size, s);
    int i = 1, k = 0;

    for (i; i <= input_size && s[input_size - i] != 'x' && s[input_size - i] != 'X'; i++) {
        char current = s[input_size - i];
        if (current >= 'a' && current <= 'f')
            result += (10 + s[input_size - i] - 'a') * pow(16, i - 1);
        else if (current >= 'A' && current <= 'F')
            result += (10 + s[input_size - i] - 'A') * pow(16, i - 1);
        else result += (s[input_size - i] - '0') * pow(16, i - 1);
    }

    return result;
}

char *squeeze(const char s1[], const char s2[]) {
    char cur;
    char *res = (char *) s1, *new_res;
    int s1_length = 0, s2_length = 0, k;
    STRING_LEN(s1_length, s1);
    STRING_LEN(s2_length, s2);

    for (int i = 0; i < s2_length; i++) {
        cur = res[i];
        k = 0;
        new_res = "";

        for (int j = 0; j < s1_length; j++) {
            if (res[i] != cur) {
                new_res[k] = res[i];
                k++;
            }
        }
        s2_length = k;

        STRING_COPY(new_res, res, k);
    }

    return res;
}

int any(const char s1[], const char s2[]) {
    int s1_size = 0, s2_size = 0;
    STRING_LEN(s1_size, s1);
    STRING_LEN(s2_size, s2);

    for (int i = 0; i < s1_size; i++) {
        for (int j = 0; j < s2_size; j++) {
            if (s1[i] == s2[j]) return i;
        }
    }

    return -1;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned xnulled = ((x >> (p + 1 - n)) & (~0 << n)) << (p + 1 - n);
    unsigned xrightpart = x & ~(~0 << (p + 1 - n));
    unsigned ynulled = (y & ~(~0 << n)) << (p + 1 - n);

    unsigned result = xnulled | ynulled | xrightpart;
    return result;
}

int binsearch(int x, int v[], int n) {
    int low = 0, high = n - 1, mid = 0;

    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid - 1;
        else
            low = mid;
    }

    return (x == v[mid]) ? mid : -1;
}

char *escape(char *from) {
    char cur;
    int from_length = 0, k = 0;
    STRING_LEN(from_length, from);
    char *to = ALLOCATE(from_length * 2);

    for (int i = 0; i < from_length; i++, k++) {
        cur = from[i];
        switch (cur) {
            case '\n':
                to[k] = '\\';
                to[++k] = 'n';
                break;
            case '\t':
                to[k] = '\\';
                to[++k] = 't';
                break;
            default:
                to[k] = cur;
                break;
        }
    }

    to[k] = '\0';

    return to;
}

char *expand(char *s) {
    char left = s[0], cur;
    char *res = "";
    int s_length = 0;
    STRING_LEN(s_length, s);

    for (int i = 0; i < s_length; i++) {
        cur = s[i];
        if (cur != '-') {
            if (left == '-') {
                left = cur;
            } else
                for (char c = left; c <= cur; c++) {
                    res += c;
                }
                left = '-';
        }
    }

    return res;
}

char *itoa(int n, const char s[]);

char *itob(int n, const char s[], int b);

int strrindex(char* s, char* t) {
    char *res;
    int s_length = 0, t_length = 0, equal;
    STRING_LEN(s_length, s);
    STRING_LEN(t_length, t);

    for (int i = s_length - t_length; i >= 0; i--) {
        equal = 1;
        for (int j = 0; j < t_length; j++) {
            if (s[i + j] != t[j]) {
                equal = 0;
                break;
            }
        }
        if (equal == 1)
            return i;
    }

    return -1;
}

double atofe(const char s[]);