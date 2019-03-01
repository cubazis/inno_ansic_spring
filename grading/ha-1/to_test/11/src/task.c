//
// Created by cubazis on 25.05.18.
//

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

char *detab(const char *input) {
    int length = 0;
    int tabs = 0;
    STRING_LEN(length, (input));
    for (int i = 0; i < length; ++i)
        if ((input)[i] == '\t')
            tabs += 1;
    char *c = ALLOCATE(length + 3 * tabs);
    int j = 0;
    for (int i = 0; i < length; ++i) {
        if ((input)[i] == '\t') {
            for (int k = 0; k < 4; ++k)
                c[j + k] = ' ';
            j += 3;
        } else
            c[j] = (input)[i];
        j += 1;
    }
    c[j] = '\0';

    return c;
}

char *entab(const char *input) {
    int length = 1;
    STRING_LEN(length, input);
    char *c = malloc(length * sizeof(char));
    int j = 0;
    for (int i = 0; i < length; ++i, ++j) {
        if (i + 3 < length && input[i] == ' ' && input[i + 1] == ' ' && input[i + 2] == ' ' && input[i + 3] == ' ') {
            c[j] = '\t';
            i += 3;
        } else
            c[j] = input[i];
    }
    c[j] = '\0';

    return c;
}

char *enter(int n, const char *input) {
    int length = 0;
    STRING_LEN(length, input);
    int strings = length / n + 1;
    char *c = malloc((length + strings) * sizeof(char));
    int j = 0;
    for (int i = 0; i < length; ++i, ++j) {
        if (i % n == 0 && i != 0)
            c[j++] = '\n';
        c[j] = input[i];
    }
    c[j] = '\0';

    return c;
}

int find_end_of_comment(int i, int length, const char *input) {
    if (input[i + 1] == '*') {
        for (; i < length; ++i)
            if (i + 2 < length && input[i] == '*' && input[i + 1] == '/')
                return i + 2;
    } else {
        for (; i < length; ++i)
            if (i + 1 < length && input[i] == '\n')
                return i + 1;
    }

    return length;
}

char *flush(const char *input) {
    int length = 0;
    STRING_LEN(length, input);
    char *c = malloc((length + 1) * sizeof(char));
    int j = 0;
    for (int i = 0; i < length; ++i, ++j) {
        if (i + 1 < length && input[i] == '/' && (input[i + 1] == '*' || input[i + 1] == '/'))
            i = find_end_of_comment(i, length, input);

        if (i < length)
            c[j] = input[i];
    }
    c[j] = '\0';

    return c;
}

int htoi(const char s[]) {
    int result = 0, size = 0, digit, power = 1, sub = 7;

    if (s[1] == 'x') {
        sub = 39;
    }

    STRING_LEN(size, s);

    for (int i = size - 1; i >= 2; i--) {
        digit = s[i] - '0';

        if (digit >= 17) {
            digit -= sub;
        }

        result += digit * power;
        power *= 16;
    }

    return result;
}

char *squeeze(const char s1[], const char s2[]) {
    int s1_size = 0, index = 0, found = 0;

    STRING_LEN(s1_size, s1);

    char *filtered = ALLOCATE(s1_size);

    for (int i = 0; s1[i] != '\0'; i++) {
        found = 0;
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            filtered[index] = s1[i];
            index++;
        }
    }

    char *result = ALLOCATE(index + 1);

    for (int i = 0; i < index; i++) {
        result[i] = filtered[i];
    }
    result[index] = '\0';

    return result;
}

int any(const char s1[], const char s2[]) {
    int result = -1;

    for (int i = 0; s1[i] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                result = i;
                break;
            }
        }

        if (result != -1)
            break;
    }

    return result;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return x & ~(~(~0 << n) << (p + 1 - n)) | (y & ~(~0 << n)) << (p + 1 - n);
}

int binsearch(int x, int v[], int n) {
    int low = 0, high = n - 1, mid = (low + high) / 2;

    while (low < high && x != v[mid]) {
        if (x > v[mid])
            low = mid + 1;
        else
            high = mid - 1;
        mid = (low + high) / 2;
    }
    if (x == v[mid])
        return mid;
    else
        return -1;
}

char *itoa(int n) {
    int k = n, count = 0;
    int sign_k = 1; // 1 is positive, -1 is negative
    if (k < 0) {
        count++; // minus
        sign_k = -1;
    }
    k /= 10;
    count++;    // last digit
    if (sign_k < 0) {
        k = -k;
    }
    while (k != 0) {
        count++;
        k /= 10;
    }

    char *s = ALLOCATE(count + 1);  // + 1 because null-terminator
    int i, sign = 1;
    i = 0;
    if (n < 0) {
        sign = -1;
    }
    s[i++] = (char) (abs(n % 10) + '0');
    n /= 10;
    if (sign < 0) {
        n = -n;
    }
    while (n > 0) {
        s[i++] = (char) (n % 10 + '0');
        n /= 10;
    }
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    for (int j = 0; j <= (i - 1) / 2; j++) {
        char copy = s[i - 1 - j];
        s[i - 1 - j] = s[j];
        s[j] = copy;
    }
    return s;
}

char *itob(int n, int b) {
    int k = n, count = 0;
    int sign_k = 1; // 1 is positive, -1 is negative
    if (k < 0) {
        count++; // minus
        sign_k = -1;
    }
    k /= b;
    count++;    // last digit
    if (sign_k < 0) {
        k = -k;
    }
    while (k != 0) {
        count++;
        k /= b;
    }

    char *s = ALLOCATE(count + 1);  // + 1 because null-terminator
    int i, sign = 1;
    i = 0;
    if (n < 0) {
        sign = -1;
    }
    s[i++] = (char) (abs(n % b) + '0');
    n /= b;
    if (sign < 0) {
        n = -n;
    }
    while (n > 0) {
        s[i++] = (char) (n % b + '0');
        n /= b;
    }
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    for (int j = 0; j <= (i - 1) / 2; j++) {
        char copy = s[i - 1 - j];
        s[i - 1 - j] = s[j];
        s[j] = copy;
    }
    for (int j = 0; j < i; j++) {
        if (s[j] > (char) ('0' + 9)) {
            s[j] = (char) ('A' + (int) (s[j]) - 10 - '0');
        }
    }
    return s;
}


char *escape(const char from[]) {
    int str_len = 0;
    int counter = 0;
    for (int i = 0; from[i] != '\0'; i++) {
        str_len++;
        if (from[i] == '\n' | from[i] == '\t') {
            counter++;
        }
    }
    char *out = ALLOCATE(str_len + counter);
    int dif = 0;
    for (int i = 0; i < str_len; i++) {
        switch (from[i]) {
            case '\n':
                out[i + dif] = '\\';
                out[i + dif + 1] = 'n';
                dif++;
                break;
            case '\t':
                out[i + dif] = '\\';
                out[i + dif + 1] = 't';
                dif++;
                break;
            default:
                out[i + dif] = from[i];
                break;
        }
    }
    return out;
}

char *expand(const char s1[]) {
    int counter = 2;
    int len = 0;
    if (s1[counter] != NULL) {
        for (; s1[counter] != '\0'; counter++) {
            len++;
            if ((s1[counter - 2] <= s1[counter]) & (s1[counter - 1] == '-') &
                ((s1[counter - 2] >= 'a' & s1[counter - 2] <= 'z') | (s1[counter - 2] >= '0' & s1[counter - 2] <= '9') |
                 (s1[counter - 2] >= 'A' & s1[counter - 2] <= 'Z')) &
                ((s1[counter] >= 'a' & s1[counter] <= 'z') | (s1[counter] >= '0' & s1[counter] <= '9') |
                 (s1[counter] >= 'A' & s1[counter] <= 'Z'))) {
                len--;
                len += s1[counter] - s1[counter - 2];
                counter++;
            }
        }
        int additional = 0;
        for (; s1[counter - 2] != '\0'; counter++) { additional++; }
        char *out = ALLOCATE(len + additional);

        counter = 2;
        int pos = 0;
        for (; s1[counter] != '\0'; counter++) {
            if ((s1[counter - 2] <= s1[counter]) & (s1[counter - 1] == '-') &
                ((s1[counter - 2] >= 'a' & s1[counter - 2] <= 'z') | (s1[counter - 2] >= '0' & s1[counter - 2] <= '9') |
                 (s1[counter - 2] >= 'A' & s1[counter - 2] <= 'Z')) &
                ((s1[counter] >= 'a' & s1[counter] <= 'z') | (s1[counter] >= '0' & s1[counter] <= '9') |
                 (s1[counter] >= 'A' & s1[counter] <= 'Z'))) {
                char now = s1[counter - 2];
                for (; now < s1[counter]; now++) {
                    out[pos] = now;
                    pos++;
                }
                counter += 1;
            } else {
                out[pos] = s1[counter - 2];
                pos++;
            }
        }
        int str_len = 0;
        STRING_LEN(str_len, s1);
        counter = str_len - 1;
        if ((s1[counter - 2] <= s1[counter]) & (s1[counter - 1] == '-') &
            ((s1[counter - 2] >= 'a' & s1[counter - 2] <= 'z') | (s1[counter - 2] >= '0' & s1[counter - 2] <= '9') |
             (s1[counter - 2] >= 'A' & s1[counter - 2] <= 'Z')) &
            ((s1[counter] >= 'a' & s1[counter] <= 'z') | (s1[counter] >= '0' & s1[counter] <= '9') |
             (s1[counter] >= 'A' & s1[counter] <= 'Z'))) {
            out[pos] = s1[counter];
            out[pos + 1] = '\0';
        } else {
            out[pos] = s1[counter - 1];
            pos++;
            out[pos] = s1[counter];
        }
        return out;
    } else { return s1; }
}

int strrindex(const char s[], const char t[]) {
    int i, j, k;
    int ans = -1;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
        if (k > 0 && t[k] == '\0') ans = i;
    }
    return ans;
}

double atofe(const char s[]) {
    double val, power;
    int i, sign;

    for (i = 0; IS_SPACE(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; IS_DIGIT(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; IS_DIGIT(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        int is_exp_negative = (s[i] == '-') ? 1 : 0;
        if (s[i] == '+' || s[i] == '-')
            i++;
        int n = 0;
        for (; IS_DIGIT(s[i]); i++)
            n = 10 * n + (s[i] - '0');
        for (int j = 0; j < n; j++) {
            val *= (is_exp_negative ? 0.1 : 10.0);
        }
    }
    return sign * val / power;
}

