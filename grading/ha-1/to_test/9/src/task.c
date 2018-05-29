//
// Created by cubazis on 25.05.18.
//

#include <math.h>
#include "task.h"
#include <string.h>

#define TAB_SIZE 4

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
    char i = 0;
    int j = 0;
    STRING_LEN(i, input);
    char *to_return = ALLOCATE(i);
    j = i;
    int k2 = 0;
    for (int k1 = 0; k1 < i; ++k1) {
        if (input[k1] == '\t') {
            j += TAB_SIZE;
            to_return = realloc(to_return, j * sizeof(char));
            for (int c = 0; c < TAB_SIZE; ++c) {
                to_return[k2] = ' ';
                k2++;
            }
        } else {
            to_return[k2] = input[k1];
            k2++;
        }
    }
    to_return[k2] = '\0';

    return to_return;
}

char *entab(const char input[]) {
    char i = 0;
    STRING_LEN(i, input);
    char *to_return = ALLOCATE(i);

    int k2 = 0;

    int current_spaces = 0;

    for (int k1 = 0; k1 < i; ++k1) {
        if (input[k1] == ' ') {
            current_spaces++;
            if (current_spaces == TAB_SIZE) {
                current_spaces = 0;
                to_return[k2] = '\t';
                k2++;
            }
        } else {
            while (current_spaces > 0) {
                to_return[k2] = ' ';
                k2++;
                current_spaces--;
            }
            to_return[k2] = input[k1];
            k2++;
        }
    }
    while (current_spaces > 0) {
        to_return[k2] = ' ';
        k2++;
        current_spaces--;
    }

    to_return[k2] = '\0';
    return to_return;
}

char *flush(const char input[]) {
    char *output = ALLOCATE(strlen(input));
    int pointer = 0;
    int curDels = 0;
    int bound = 0;
    STRING_LEN(bound, input);
    for (int i = 0; i < bound; i++) {
        // String literals may contain comments
        if (input[i] == '"' || input[i] == '\'') {
            char dash = input[i];
            output[pointer] = input[i];
            pointer++;
            i++;
            while (input[i - 1] != '\\' && input[i] != dash) {
                output[pointer] = input[i];
                pointer++;
                i++;
            }
        }
        if (input[i] == '/') {
            // Remove // comments until next line
            if (input[i + 1] == '/') {
                curDels = 1;
                for (int j = i + 2; j < strlen(input); j++) {
                    curDels++;
                    if (input[j] == '\n') {
                        break;
                    }
                }
                i += curDels;
            }

                // Remove /* ... */
            else if (input[i + 1] == '*') {
                curDels = 0;
                for (int j = i; j < strlen(input) - 1; j++) {
                    curDels++;
                    if (input[j] == '*' && input[j + 1] == '/') {
                        break;
                    }
                }
                i += curDels;
            }
        } else {
            output[pointer] = input[i];
            pointer++;
        }
    }
    char *to = ALLOCATE(pointer);
    for (int j = 0; j < pointer; j++) {
        to[j] = output[j];
    }
    to[pointer] = '\0';
    return to;
}

char *enter(int n, const char input[]) {
    int length = 0;
    STRING_LEN(length, input);
    int count = 0;
    char *output = ALLOCATE(length + log2(length) + 1);
    if (length > n) {
        for (int i = 0; i < length; i++) {
            output[i + count] = input[i];
            if (i % n == n - 1 && i != 0 && i != length - 1) {
                output[i + count + 1] = '\n';
                count++;
            }
        }
    }
    int bound = length + count + 1;
    char *to = ALLOCATE(bound);
    for (int j = 0; j < bound - 1; j++) {
        to[j] = output[j];
    }
    to[bound - 1] = '\0';
    return to;
}

/** GET FROM task.h */

int htoi(const char s[]) {
    int l = 0;
    int res = 0;
    int start = 0;
    STRING_LEN(l, s);
    if (s[1] == 'x' || s[1] == 'X') {
        start = 2;
    }
    int power = 0;
    for (int i = l - 1; i >= start; i--) {
        char j = s[i];
        if (j >= 'a' && j <= 'f') {
            res += (j - 'a' + 10) * pow(16, power);
        } else if (j >= 'A' && j <= 'F') {
            res += (j - 'A' + 10) * pow(16, power);
        } else if (j >= '0' && j <= '9') {
            res += (j - '0') * pow(16, power);
        }
        power++;
    }
    return res;
}

char *squeeze(const char s1[], const char s2[]) {
    int l1 = 0, l2 = 0;
    STRING_LEN(l1, s1);
    STRING_LEN(l2, s2);
    char *res = ALLOCATE(l1);
    int flag;
    int res_i = 0;
    for (int i = 0; i < l1; i++) {
        flag = 0;
        for (int j = 0; j < l2; j++) {
            if (s1[i] == s2[j]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            res[res_i] = s1[i];
            res_i++;
        }
    }
    res[res_i] = '\0';
    return res;
}

int any(const char s1[], const char s2[]) {
    for (int i = 0; i < strlen(s1); i++) {
        for (int j = 0; j < strlen(s2); j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}

char *itob(int n, int b) {
    if (b < 2) {
        return "Base must be > 1";
    }
    int i, j, sign;
    char *output = ALLOCATE(1);
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        j = n % b;
        if (j < 10) {
            output[i++] = (char) (j + '0');
        } else {
            output[i++] = (char) (j + 'a' - 10);
        }
        output = realloc(output, sizeof(char) * (i + 1));
    } while ((n /= b) > 0);

    if (sign < 0)
        output[i++] = '-';
    output[i] = '\0';

    //reverse
    int k, l = 0;
    char c;
    STRING_LEN(l, output);
    for (k = 0, l--; k < l; k++, l--) {
        c = output[k];
        output[k] = output[l];
        output[l] = c;
    }
    return output;
}

int strrindex(const char source[], const char target[]) {

    int s_len = 0;
    int t_len = 0;
    STRING_LEN(s_len, source);
    STRING_LEN(t_len, target);
    int index = -1;
    for (int i = s_len - t_len + 1; i >= 0; i--) {
        if (source[i] == target[0]) {
            index = i;
            break;
        }
    }

    if (index > -1) {
        for (int i = index; i < t_len + index; i++) {
            char a = source[i];
            char b = target[i - index];
            if (a == b && i - index == t_len) return index;
            if (a != b) {
                char *to = (char *) malloc((index + 1) * sizeof(char));
                for (int j = 0; j < index; j++) {
                    to[j] = source[j];
                }
                to[index] = '\0';
                return strrindex(to, target);
            }
        }
        return index;
    }
    return index;
}

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0, high = n;
    while (low < high) {
        mid = (low + high) / 2;
        if (v[mid] < x) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    if ((high < n) && (v[high] == x)) {
        return high;
    } else {
        return -1;
    }
}

char *escape(const char from[]) {
    char i = 0;
    int j = 0;
    STRING_LEN(i, from);
    char *to_return = ALLOCATE(i);
    j = i;
    int k2, k1;
    k1 = k2 = 0;

    for (; k1 < i; ++k1) {
        switch (from[k1]) {
            case '\t':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = 't';
                break;
            case '\n':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = 'n';
                break;
            case '\v':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = 'v';
                break;
            case '\b':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = 'b';
                break;
            case '\r':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = 'r';
                break;
            case '\f':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = 'f';
                break;
            case '\a':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = 'a';
                break;
            case '\\':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = '\\';
                break;
            case '\?':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = '\?';
                break;
            case '\'':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = '\'';
                break;
            case '\"':
                j += 2;
                to_return = realloc(to_return, j * sizeof(char));
                to_return[k2++] = '\\';
                to_return[k2++] = '\"';
                break;
            default:
                to_return[k2++] = from[k1];
                break;
        }
    }
    to_return[k2] = '\0';
    return to_return;
}

char *expand(const char s1[]) {
    int l = 0;
    char *res = ALLOCATE(1);
    int insert = 0;
    STRING_LEN(l, s1);
    if (s1[0] == '-') {
        res[insert++] = '-';
    }
    for (int i = 1; i < l - 1; i++) {
        if (s1[i] == '-') {
            char start = s1[i - 1];
            char end = s1[i + 1];
            while (s1[i = i + 2] == '-' && i < l - 1) {
                end = s1[i + 1];
            }
            for (char j = start; j <= end; j++) {
                res[insert] = j;
                insert++;
                res = realloc(res, insert + 1 + sizeof(char));
            }
        }
    }
    if (s1[l - 1] == '-') {
        res[insert++] = '-';
    }
    res[insert] = '\0';
    return res;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned x1 = x;
    int to_move = p + 1 - n;

    if (to_move < 0) {
        printf("ALERT ALERT ALERT WRONG INPUT\n");
        return 0;
    }
    x1 = x1 & (~(~0 << to_move));
    x = x >> to_move;
    x = x & ((~0 << n));

    y = y & (~(~0 << n));
    x = x | y;

    x = x << to_move;
    x = x | x1;

    return x;
}

double atofe(const char s[]) {
    int i = 0;
    int l = 0;
    STRING_LEN(l, s);
    int flagPoint = 0;
    int flagE = 0;
    int E = 0;
    double res = 0;
    while (i < l) {
        if (s[i] == '.') {
            flagPoint = i;
        }
        if (s[i] == 'e' || s[i] == 'E') {
            flagE = i;
        }
        i++;
    }
    if (flagPoint && flagE) {
        int powerL = 0;
        int goLeftPoint = flagPoint - 1;
        while (goLeftPoint > 0) {
            res += (s[goLeftPoint--] - '0') * pow(10, powerL++);
        }
        int goRightPoint = flagPoint + 1;
        int powerR = -1;
        while (goRightPoint < flagE) {
            res += (s[goRightPoint++] - '0') * pow(10, powerR--);
        }
        if (s[0] == '-') {
            res *= -1;
        } else {
            res += (s[0] - '0') * pow(10, powerL);
        }
        int startE = flagE + 1;
        l--;
        powerL = 0;
        while (l > startE) {
            E += (s[l] - '0') * pow(10, powerL);
            l--;
        }
        if (s[startE] == '-') {
            E *= -1;
        } else {
            E += (s[startE] - '0') * pow(10, powerL);
        }
        res *= pow(10, E);
    } else if (flagPoint) {
        int powerL = 0;
        int goLeftPoint = flagPoint - 1;
        while (goLeftPoint > 0) {
            res += (s[goLeftPoint--] - '0') * pow(10, powerL++);
        }
        int goRightPoint = flagPoint + 1;
        int powerR = -1;
        while (goRightPoint < l) {
            res += (s[goRightPoint++] - '0') * pow(10, powerR--);
        }
        if (s[0] == '-') {
            res *= -1;
        } else {
            res += (s[0] - '0') * pow(10, powerL);
        }
    } else if (flagE) {
        int powerL = 0;
        int goLeftPoint = flagE - 1;
        while (goLeftPoint > 0) {
            res += (s[goLeftPoint--] - '0') * pow(10, powerL++);
        }
        if (s[0] == '-') {
            res *= -1;
        } else {
            res += (s[0] - '0') * pow(10, powerL);
        }
        int startE = flagE + 1;
        l--;
        powerL = 0;
        while (l > startE) {
            E += (s[l] - '0') * pow(10, powerL);
            l--;
        }
        if (s[startE] == '-') {
            E *= -1;
        } else {
            E += (s[startE] - '0') * pow(10, powerL);
        }
        res *= pow(10, E);
    } else {
        int powerL = 0;
        int goLeftPoint = l - 1;
        while (goLeftPoint > 0) {
            res += (s[goLeftPoint--] - '0') * pow(10, powerL++);
        }
        if (s[0] == '-') {
            res *= -1;
        } else {
            res += (s[0] - '0') * pow(10, powerL);
        }
    }
    return res;
}

char *itoa(int n) {
    char *res = ALLOCATE(1);
    int i, sign;
    sign = n;

    i = 0;
    do {
        res[i++] = (char) (abs(n % 10) + '0');
        res = realloc(res, (i + 1) * sizeof(char));
    } while (n /= 10);
    if (sign < 0)
        res[i++] = '-';

    res[i] = '\0';

    int j = 0;
    STRING_LEN(j, res);
    char c;

    for (i = 0, j--; i < j; i++, j--) {
        c = res[i];
        res[i] = res[j];
        res[j] = c;
    }
    return res;
}