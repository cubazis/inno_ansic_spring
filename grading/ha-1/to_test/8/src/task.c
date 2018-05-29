//
// Created by cubazis on 25.05.18.
//

#include "task.h"
#include <math.h>
#include <ctype.h>

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
        if (c[ j ] == 'c')
            b[j] = 'b';
        else
            b[j] = c[j];
        j++;
    }
    return b;
}

/** YOUR SOLUTIONS */
char *entab(const char input[]) {
    int i = 0;
    STRING_LEN(i, input);

    int *buf = malloc((i) * sizeof(int));
    int size = i;

    buf[0] = input[0] == ' ' ? 1 : 0;
    for (int j = 1; j < i; j++) {
        if (input[j] == ' ') {
            buf[j] = buf[j - 1] + 1;
            if (buf[j] == 4 && j >= 3) {
                buf[j] = 0;
                buf[j - 3] = -1;
                size -= 3;
            }
        }
    }
    char *res = ALLOCATE(size);
    if (i==0){
        res[0]='\0';
        return res;
    }
    int ind = -1;
    for (int j = 0; j < i;) {
        ind++;
        if (buf[j] == -1) {
            res[ind] = '\t';
            j += 4;
        } else {
            res[ind] = input[j];
            j++;
        }
    }
    res[ind+1]='\0';
    return res;

}

char *detab(const char input[]) {
    int size = 0;
    int i = 0;
    //1)Найти конечную длину строки
    STRING_LEN(i, input);
    for (int j = 0; j < i; j++) {
        if (input[j] != '\t') {
            size++;
        } else {
            size += 4;
        }
    }
    char *res = ALLOCATE(size);
    int ind = 0;
    //2)Заполнить строку
    for (int j = 0; j < i; j++) {

        if (input[j] != '\t') {
            res[ind] = input[j];
            ind++;
        } else {
            for (int l = ind; l <= ind + 3; l++) {
                res[l] = ' ';
            }
            ind += 4;
        }
    }
    return res;
}

char *enter(int n, const char input[]) {
    int i = 0, size = 0, counter = 0;

    STRING_LEN(i, input);

    for (int j = 0; j < i; j++) {
        if (counter > n) {
            size++;
            counter = 0;
        } else if (input[j] == '\n') {
            counter = 0;
        } else {
            counter++;
        }
        size++;
    }

    char *res = ALLOCATE(size);
    counter = 0;
    int arr_pointer = 0;
    for (int j = 0; j < i; j++) {
        if (counter > n) {
            res[arr_pointer] = '\n';
            arr_pointer++;
            res[arr_pointer] = input[j];
            counter = 0;
        } else if (input[j] == '\n') {
            res[arr_pointer] = '\n';
            counter = 0;
        } else {
            res[arr_pointer] = input[i];
        }
        arr_pointer++;
    }

    return res;
}

int htoi(const char s[]) {
    int j = 0, i = 0;
    STRING_LEN(i, s);

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        j = 2;
    }

    int res = 0, power = 0;
    for (i--; i >= j; i--) {
        int temp;
        if (s[i] - '0' >= 0 && s[i] - '9' <= 0)
            temp = s[i] - '0';
        else if (s[i] - 'a' >= 0 && s[i] - 'z' <= 0)
            temp = s[i] - 'a' + 10;
        else
            temp = s[i] - 'A' + 10;

        res += pow(16, power) * temp;
        power++;
    }
    return res;
}

int any(const char s1[], const char s2[]) {
    int i = 0;
    STRING_LEN(i, s1);

    int size_s1 = i, size_s2 = 0;

    i = 0;
    STRING_LEN(i, s2);
    size_s2 = i;

    for (i = 0; i < size_s1; i++) {
        for (int j = 0; j < size_s2; j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }

    return -1;
}

char *squeeze(const char s1[], const char s2[]) {
    int *s2_ = malloc((256) * sizeof(int));
    int i = 0;
    STRING_LEN(i, s2);
    for (int j = 0; j < i; j++) {
        s2_[s2[j]] = 1;
    }
    //int i3=0;
    //STRING_LEN(i3,"kekpek");
    int i1 = 0;
    STRING_LEN(i1, s1);
    int size = i1;
    for (int j = 0; j < i1; j++) {
        if (s2_[s1[j]] == 1) {
            size -= 1;
            if (size < 0) {
                size = 0;
            }
        }
    }
    char *res = ALLOCATE(size);
    int ind = 0;
    for (int j = 0; j < i1; j++) {
        if (s2_[s1[j]] != 1) {
            res[ind] = s1[j];
            ind++;
        }

    }
    return res;

}

char *itob(int n, int b) {
    int temp[32], size = 0;
    _Bool isNegative = n < 0;

    if (isNegative) {
        n *= -1;
    }

    while (n > 0) {
        temp[size] = n % b;

        n /= b;
        size++;
    }

    char *res = ALLOCATE(size + 1);
    res[size] = '\0';
    size--;

    if (b <= 10) {
        for (int i = 0; size >= 0; size--) {
            res[i] = temp[size] + '0';
            i++;
        }
    } else {
        for (int i = 0; size >= 0; size--) {
            if (temp[size] <= 9) {
                res[i] = temp[size] + '0';
            } else {
                res[i] = temp[size] + 'A' - 10;
            }
            i++;
        }
    }

    return res;
}

char *expand(const char s1[]) {
    int size = 0;
    int j = 0;
    STRING_LEN(j, s1);
    for (int i = 0; i < j; i++) {
        if (i > 1 && (s1[i] != '-') && (s1[i - 1] == '-')) {
            size += s1[i] - s1[i - 2] + 1;
        }
        if (i == 1 && s1[i - 1] == '-') {
            size += s1[i];
        }
    }
    char *res = ALLOCATE(size);
    int ind = 0;
    if (j > 0 && s1[0] == '-') {
        res[0] = '-';
        ind = 1;
    }
    for (int i = 1; i < j; i++) {
        //printf("%d",s1[i]);
        if (i > 1 && (s1[i - 1] == '-')) {
            for (int l = s1[i - 2]; l <= s1[i]; l++) {
                if (ind < 1 | (res[ind - 1] != l)) {
                    res[ind] = l;
                    ind++;
                }
            }
        }
    }

    res[ind] = '\0';
    return res;
}

int strrindex(const char s[], const char t[]) {
    int i = 0, sizeS, sizeT;
    STRING_LEN(i, s);

    sizeS = i;
    i = 0;

    STRING_LEN(i, t);
    sizeT = i;

    for (i = sizeS; i >= 0; i--) {
        if (s[i] == t[sizeT - 1] && sizeT - 2 <= i) {
            int temp = 1;
            _Bool match = 1;

            for (int j = sizeT - 2; j >= 0; j--) {
                match &= t[j] == s[i - temp];
                temp++;
            }

            if (match) {
                return i - temp + 1;
            }
        }
    }

    return -1;
}

char *flush(char arr[]) {

    int size = 0;

    STRING_LEN(size, arr);

    char *out = ALLOCATE(size);
    int ind = 0;

    for (int i = 0; arr[i] != '\0'; i++) {

        if (arr[i] == '/' && arr[i + 1] == '/') {
            while (arr[i] != '\n') i++;
            continue;
        }

        if (arr[i] == '/' && arr[i + 1] == '*') {
            i += 2;
            while (arr[i] != '*' || arr[i + 1] != '/') i++;
            i++;
            continue;
        }

        out[ind] = arr[i];
        ind++;
    }
    return out;
}

int binsearch(int x, int v[], int n) {

    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid;
        else low = mid + 1;
    }

    return (x == v[high]) ? high : -1;
}

char *escape(const char from[]) {
    int size = 0;

    STRING_LEN(size, from);

    char *out = ALLOCATE(2 * size);
    char c = 1;

    int ind = 0;

    for (int i = 0; c != '\0'; i++) {
        c = from[i];

        switch (c) {
            case '\n':
                out[ind++] = '\\';
                out[ind] = 'n';
                break;
            case '\t':
                out[ind++] = '\\';
                out[ind] = 't';
                break;
            default:
                out[ind] = c;
        }

        ind++;
    }

    out[ind] = '\0';

    return out;
}


unsigned setbits(unsigned x, int p, int n, unsigned y) {
    int temp[64];

    int j = 0;
    while (x > 0) {
        temp[j] = x % 2;
        j++;
        x /= 2;
    }

    char binX[j];
    int size = j;
    for (; j >= 0; j--) {
        binX[j] = temp[j] + '0';
    }

    for (int i = 0; i <= p - 1 || n > 0; i++) {
        binX[i] = y % 2 + '0';
        y /= 2;
        n--;
    }

    unsigned res = 0;
    for (int i = size - 1; i >= 0; i--) {
        res += pow(2, i) * (binX[i] - '0');
    }

    return res;
}

double atofe(const char s[]) {
    double val, power,exp;
    int i, sign,signexp;

    for (i = 0; isspace(s[i]); i++);

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0;isdigit(s[i]);i++){
        val=10.0*val + (s[i] - '0');
        power *=10.0;
    }
    if( s[i]=='e' || s[i]=='E')
        i++;
    signexp = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (exp = 0.0; isdigit(s[i]); i++)
        exp = 10.0 * exp + (s[i] - '0');

    return sign*val/power * pow(10,signexp*exp);
}

char* itoa(int n){

    int i = 1, sign = n;

    char* out = ALLOCATE(12);

    out[0] = '\0';

    do{
        if(sign >= 0)
            out[i] = n % 10 + '0';
        else out[i] = -1*(n % 10) + '0';
        i++;
    }while((n /= 10) != 0 );

    if(sign < 0) out[i] = '-';
    else i--;

    for(int j = 0; j <= i/2; j++){

        char c = out[i-j];
        out[i-j] = out[j];
        out[j] = c;

    }
    return out;
}
/** GET FROM task.h */