//
// Created by cubazis on 25.05.18.
//

#include "task.h"
#include <string.h>
#include <math.h>

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
	char i = 0, j = 0;
	STRING_LEN(i, c);
	char* b = ALLOCATE(i);

	for (;j < i;) {
		if(b[j] == 'c')
			b[j] = 'b';
		else
			b[j] = c[j];
		j++;
	}
	return b;
}

/** YOUR SOLUTIONS */

#define TABSTOP 4

char* detab(const char input[])
{
	int len, i, count,j ;
	len = i = count = j = 0;
	STRING_LEN(len, input);
	for (i = 0; i < len; ++i) { if (input[i] == '\t') ++count; }
	char *b = ALLOCATE(len + count*TABSTOP - 2);
	i = 0;
	do {
		if (input[i] == '\t') {
			for (int k = j; k < (j + TABSTOP); ++k) b[k] = ' ';
			j += TABSTOP;
		} else b[j++] = input[i];
		++i;
	} while (input[i]);
	b[j] = '\0';
	return b;
}

char* kernighan_detab(const char input[])
{
	int len, i, count, j;
	len = i = count = j = 0;
	STRING_LEN(len, input);
	for (i = 0; i < len; ++i) { if (input[i] == '\t') ++count; }
	char *b = ALLOCATE(len + count*TABSTOP - 2);
	i = 0;
	do {
		if (input[i] == '\t') {
			int k = j + (TABSTOP - j%TABSTOP);
			for(;j < k; ++j) b[j] = ' ';
		} else b[j++] = input[i];
		++i;
	} while (input[i]);
	b[j] = '\0';
	return b;
}

char* entab(const char input[])
{
	int i, len;
	i = len = 0;
	STRING_LEN(len, input);
	char* b = ALLOCATE(len);
	int j = 0;
	do {
		if (input[i] == ' ') {
			int count, tabs, spaces;
			count = spaces = 0;
			while (input[i] == ' ') {
				++count;
				++i;
			}
			tabs = count / TABSTOP;
			if (count%TABSTOP != 0) spaces = count - 4*tabs;
			while (tabs--   > 0) b[j++] = '\t';
			while (spaces-- > 0) b[j++] = ' ';
		} else b[j++] = input[i++];
	} while (input[i]);
	b[j] = '\0';
	return b;
}

char* enter(int n, const char input[])
{
	int len = 0, i = 0;
	STRING_LEN(len, input);
	char *b = ALLOCATE(len + len/n);
	int k = 0;
	do {
		if (i != 0 && i%n == 0) {
			b[k++] = '\n';
			b[k++] = input[i];
		} else
			b[k++] = input[i];
		++i;
	} while (input[i]);
	b[k] = '\0';
	return b;
}

char* flush(const char input[]) {
	int i, len, k;
	i = len = k = 0;
	STRING_LEN(len, input);
	char *b = ALLOCATE(len);
	do {
		if (input[i] == '/' && input[i+1] == '*') {
			while (input[i] != '*' || input[i+1] != '/') ++i;
			i += 2;
		}
		else if (input[i] == '/' && input[i+1] == '/')
			while (input[++i] != '\n');
		else b[k++] = input[i++];
	} while (input[i]);
	b[k] = '\0';
	return b;
}

short int get_digit(char s_digit) {
	char digit;
	digit = (s_digit >= 'A' && s_digit <= 'F') ? (char) (s_digit + 'a' - 'A') : s_digit; // to make symbol in either ['0' .. '9'] or
																						 // ['a' .. 'f']
    if (digit >= '0' && digit <= '9') {
        return (digit - '0');
    }
    if (digit >= 'a' && digit <= 'f') { // digit in ['a' .. 'f']
        return 10 + (digit - 'a');
    }
    else {
        return -1; // return error, digit is not in allowed alphabet
    }
}

int htoi(const char s[]) {
	s += 2; // to skip 0X
	const int base = 16;
	int i = 0;
	int res = get_digit(s[i]);

	++i;
	while (s[i] != '\0') {
	    short int d = get_digit(s[i]);
	    if (d == -1) {
	        return d;
	    }
	    else {
	        res = res * base + d;
	    }
	    ++i;
	}

	return res;
}

char* squeeze(const char s1[], const char s2[]) {
    int i = 0;
    char* res = malloc(strlen(s1));
    int k = 0;
    while (s1[i] != '\0') {
        char was = 0;
        int j = 0;
        while (s2[j] != '\0' && was == 0) {
            if (s1[i] == s2[j]) {
                was = 1;
            }
            ++j;
        }
        if (was == 0) {
            res[k] = s1[i];
            ++k;
        }
        ++i;
    }
    res[k] = '\0';

    return res;
}

int any(const char s1[], const char s2[]) {
    int i = 0;
    int res = -1;

    while (s1[i] != '\0' && res == -1) {
        int j = 0;
        while (s2[j] != '\0' && res == -1) {
            if (s1[i] == s2[j]) {
                res = i;
            }
            ++j;
        }
        ++i;
    }

    return res;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    for (int i = p + 1 - n; i <= p; ++i) {
        unsigned int bit = y & 1;
        y = y >> 1;
        x ^= (-bit ^ x) & (1U << i);
    }

    return x;
}

/* santa's little helper */
char* strindex(const char s[], const char t[])
{
	int i, j, k;
	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return &s[i];
	}
	return 0;
}

int strrindex(const char line[], const  char pattern[])
{
	char* ptr = line; char* found, result = -1;
	while (*line && (found = strindex(ptr++, pattern)))
		result = found - line;
	return result;
}

int binsearch(int x, int v[], int n){
	int low, high, mid;
	low = 0;
	high = n - 1;
	while(low < high){
		mid = (low + high + 1) / 2;
		if(x < v[mid])
			high = mid - 1;
		else
			low = mid;
	}
	return x == v[low] ? low : -1;
}

char* escape(const char from[]){
	int len = strlen(from);
	char* escaped = malloc(len * 2);
	int count = 0;
	for(int i = 0; from[i]; i++){
		switch(from[i]){
			case '\t':
				escaped[i + count] = '\\';
				escaped[i + count + 1] = 't';
				count++;
				break;
			case '\n':
				escaped[i + count] = '\\';
				escaped[i + count + 1] = 'n';
				count++;
				break;
			default:
				escaped[i + count] = from[i];
		}
	}
	escaped = realloc(escaped, len + count + 1);
	escaped[len + count] = 0;
	return escaped;
}

char* expand(const char s1[]){
	int len = strlen(s1);
	char* s = malloc(len * 12);
	int count = 0;
	for(int i = 0; s1[i]; i++){
		if(s1[i] == '-'){
			if(i == 0 || s1[i + 1] == 0){
				s[count++] = s1[i];
			}else{
				char start = s1[i - 1];
				char end = s1[i + 1];
				while(start <= end){
					s[count++] = start++;
				}
			}
		}
	}
	s[count++] = 0;
	return realloc(s, count);
}

char* itoa(int n){
	char* s = malloc(20);
	int i = 0;
	int sign = n >= 0;
	do{
		s[i++] = abs(n % 10) + '0';
	}while((n /= 10) != 0);
	if(!sign){
		s[i++] = '-';
	}
	int len = i;
	int j = len - 1;
	i = 0;
	char c;
	while(i < j){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
	s[len] = 0;
	return s;
}

char* itob(int n, int b){
	char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* s = malloc(100);
	int i = 0;
	int sign = n >= 0;
	do{
		s[i++] = alphabet[abs(n % b)];
	}while((n /= b) != 0);
	if(!sign){
		s[i++] = '-';
	}
	int len = i;
	int j = len - 1;
	i = 0;
	char c;
	while(i < j){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
	s[len] = 0;
	return s;
}

double atofe(const char s[]){
	int len = strlen(s), dot_pos = 0, e_pos = 0;
	while(s[dot_pos] != '.'){
		dot_pos++;
	}
	while(s[e_pos] != 'e' && s[e_pos] != 'E'){
		e_pos++;
	}
	char* int_part = malloc(dot_pos + 1);
	strncpy(int_part, s, dot_pos);
	int_part[dot_pos + 1] = 0;
	char* frac_part = malloc(e_pos - dot_pos);
	strncpy(frac_part, s + dot_pos + 1, e_pos - dot_pos - 1);
	frac_part[e_pos - dot_pos] = 0;
	char* exp_part = malloc(len - e_pos);
	strncpy(exp_part, s + e_pos + 1, len - e_pos - 1);
	exp_part[len - e_pos] = 0;
	int integer = atoi(int_part) * pow(10, e_pos - dot_pos - 1);
	if(integer >= 0)
		integer += atoi(frac_part);
	else
		integer -= atoi(frac_part);
	double result = integer;
	result *= pow(10, atoi(exp_part) - e_pos + dot_pos + 1);
	free(int_part);
	free(frac_part);
	free(exp_part);
	return result;
}

