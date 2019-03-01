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

char *detab(const char input[]) {
	char *result = (char *) malloc(sizeof(char) * strlen(input));
	int index = 0;                                                  //index of current element in result array
	int len = strlen(input);
	for (int i = 0; i < len; i++) {
		if (input[i] == '\t') {
			for (int q = 0; q < 4; q++) {
				result[index] = ' ';
				index++;
			}
		} else {
			result[index] = input[i];
			index++;
		}
	}
	return result;
}

char *entab(const char input[]) {
	char *result = (char *) malloc(sizeof(input));
	int index = 0;
	int counter = 0;
	int len = 0;
	STRING_LEN(len, input);
	for (int i = 0; i < len; i++) {
		if (input[i] == ' ') {
			int q = i;
			i = i + q - 1;
			while (q < len && input[q] == ' ') {
				counter++;
				q++;
			}
			while (counter != 0) {
				if (counter >= 4) {
					result[index] = '\t';
					index++;
					counter = counter - 4;
				} else {
					result[index] = ' ';
					index++;
					counter--;
				}
			}
		} else {
			result[index] = input[i];
			index++;
		}
	}
	return result;
}

char *enter(int n, const char input[]) {
	char *result = (char *) malloc(sizeof(char) * (strlen(input) + strlen(input) / n));
	int index = 0;
	int counter = 1;
	int len = strlen(input);
	for (int i = 0; i < len; i++) {
		result[index] = input[i];
		index++;
		if (counter == n) {
			result[index] = '\n';
			index++;
			counter = 1;
		}
	}
	return result;
}

char *flush(const char *input) {
	char *result = (char *) malloc(sizeof(char) * (strlen(input)));
	int len = 0;
	STRING_LEN(len, input);
	int index = 0;
	for (int i = 0; i < len; i++) {
		if (i + 1 < len && input[i] == '/' && (input[i + 1] == '*' || input[i + 1] == '/')) {
			if (input[i + 1] == '*') {
				while (input[i] != '*' && input[i + 1] != '/') {
					i++;
				}
			} else {
				while (input[i] != '/' && input[i + 1] != '/') {
					i++;
				}
			}
			i++;
		}
		if (i < len) {
			result[index] = input[i];
		}
		index++;
	}
	return result;
}

/** GET FROM task.h */

int htoi(const char s[]) {
	int result = 0;

	int i = 0;
	if (s[i] == '0') {
		i++;
		if (s[i] == '\0') return 0;
		else if (s[i] == 'x' || s[i] == 'X') i++;
		else return -1; //because it is octal!
		if (s[i] == '\0') return -1;
	}

	while (s[i] != '\0') {

		result *= 16;
		if (s[i] <= '9' && s[i] >= '0')
			result += s[i] - '0';
		else if (s[i] <= 'f' && s[i] >= 'a')
			result += s[i] - 'a' + 10;
		else if (s[i] <= 'F' && s[i] >= 'A')
			result += s[i] - 'A' + 10;
		else
			return -1;
		i++;
	}

	return result;
}

char *squeeze(const char s1[], const char s2[]) {
	int size_s1 = 0;
	int i, j, k = 0;
	while (s1[size_s1] != '\0') size_s1++;
	char *res = ALLOCATE(size_s1);
	for (i = 0; i < size_s1; i++) {
		for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; j++);
		if (s2[j] == '\0') {
			res[k] = s1[i];
			k++;
		}
	}
	res[k] = '\0';
	return res;
}

int any(const char s1[], const char s2[]) {
	int pos = -1;
	int i, j;
	for (i = 0; s1[i] != '\0'; ++i) {
		for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; j++);
		if (s2[j] != '\0') {
			pos = i;
			return pos;
		}
	}
	return pos;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	unsigned pow_p = 1, pow_n = 1, i = p;
	while(i > 0){
		--i;
		pow_p *= 10;
	}
	i = n;
	while(i > 0){
		--i;
		pow_n *= 10;
	}

    y = y%pow_n; //last n bits of y

	unsigned res = x, temp_pow = 1;
    while(res > pow_p/10) res /= 10;
    while(res*10*temp_pow < x) temp_pow *= 10; //now in res are first p - 1 bits of x
    res *= temp_pow;
    unsigned bits = y * temp_pow / pow_n;
    res += bits; //now in res are first p - 1 bits of x and last n bits of y


	unsigned ost = x % (pow_p*pow_n/100);

	res += ost;


	return res;
}

/**
 * 3.1
 */
int binsearch(int x, int v[], int n) {
	int low = 0;
	int high = n - 1;
	int mid = (high + low) / 2;

	while ((low <= high) && (x != v[mid])) {
		if (v[mid] > x)
			high = mid - 1;
		else
			low = mid + 1;
		mid = (high + low) / 2;
	}

	if (x == v[mid])
		return mid;
	else
		return -1;
}

/**
 * 3.2
 */
char *escape(const char from[]) {
	int i = 0;
	int j = 0;
	int k = 0;
	int size = 0;
	STRING_LEN(size, from);
	char *out = malloc((2 * size) * sizeof(char));

	while (from[i]) {

		switch (from[i]) {
			case '\a':
				out[j++] = '\\';
				out[j] = 'a';
				break;
			case '\b':
				out[j++] = '\\';
				out[j] = 'b';
				break;
			case '\f':
				out[j++] = '\\';
				out[j] = 'f';
				break;
			case '\n':
				out[j++] = '\\';
				out[j] = 'n';
				break;
			case '\r':
				out[j++] = '\\';
				out[j] = 'r';
				break;
			case '\t':
				out[j++] = '\\';
				out[j] = 't';
				break;
			case '\v':
				out[j++] = '\\';
				out[j] = 'v';
				break;
			case '\"':
				out[j++] = '\\';
				out[j] = '\"';
				break;
			case '\'':
				out[j++] = '\\';
				out[j] = '\'';
				break;
			case '\\':
				out[j++] = '\\';
				out[j] = '\\';
				break;
			default:
				out[j] = from[i];
				break;
		}
		i++;
		j++;
	}
	out[j] = from[i];

	return out;
}

//Additional function
void reverse(char *s) {
	int k, i, size = 0;
	STRING_LEN(size, s);
	for (i = 0; i < size - 1; i++, size--) {
		k = s[i];
		s[i] = s[size];
		s[size] = (char) k;
	}
}

/**
 * 3.3
 */
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


/**
 * 3.4
 */
char *itoa(int n, const char s[]) {
    int i, sign, carry;

    sign = n;
    i = 0;

    char* res = (char *) malloc(sizeof(char) * (strlen(s)));
    do {
        carry = n % 10;
        res[i++] = ((sign < 0) ? -carry : carry) + '0';
    } while (n /= 10);
    if (sign < 0)
        res[i++] = '-';
    res[i] = '\0';
    reverse(res);
    return res;
}

/**
 * 3.5
 */

char *itob(int n, const char s[], int b) {
    int i, sign, carry;
    char bases[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (b < 2 || b > 36){
        fprintf(stderr, "Cannot support base %d\n", b);
        exit(EXIT_FAILURE);
    }
    char* res = (char *) malloc(sizeof(char) * (strlen(s)));
    sign = n;
    i = 0;
    do {
        carry = n % b;
        res[i++] = ((sign < 0) ? -carry : carry) + '0';
    } while (n /= b);
    if (sign < 0)
        res[i++] = '-';
    res[i] = '\0';
    reverse(res);
    return res;
}


int strrindex(const char s[], const char t[]) {
	int i, j, k;

	/* Check the strings lengths first */
	int slen = 0, tlen = 0;
	STRING_LEN(slen, s);
	STRING_LEN(tlen, t);
	/* If t is empty, return length */
	if (tlen <= 0) {
		return slen;
	}
	/*
	 * If substring's length is
	 * greater than main string,
	 * return -1
	 */
	if (slen < tlen) {
		return -1;
	}

	/* Iterate from end to beginning */
	for (i = slen - 1; i >= 0; i--) {
		/*
		 * If further string's length
		 * is less than substring,
		 * stop searching and return -1
		 */
		if (i + 1 < tlen) {
			return -1;
		}

		/*
		 * Pick current index of s
		 * and iterate over t
		 */
		k = i;
		for (j = tlen - 1; j >= 0; j--) {
			/*
			 * If all t's chars except first
			 * have been checked, check first char.
			 * If they are equal it means that
			 * substring has been found and
			 * because we started iterating from end,
			 * current s's index (k) is the index of
			 * last substring entry.
			 * Otherwise, break, because
			 * it is not the answer.
			 */
			if (j == 0) {
				if (t[j] == s[k]) {
					return k;
				} else break;
			}

			/*
			 * If current index is not first,
			 * but chars are equal, we can iterate
			 * next (to previous char) and continue checking.
			 * If they are not equal, just break.
			 */
			if (t[j] == s[k]) {
				k--;
			} else break;
		}
	}

	return -1;
}

double atofe(const char s[]) {
	int sign = 1;
	char afterdot = 0, afterexp = 0;
	char *left, *right, *exp;

	size_t len = strlen(s);

	left = malloc(sizeof(char) * len);
	right = malloc(sizeof(char) * len);
	exp = malloc(sizeof(char) * len);

	char *writer;
	writer = left;
	for (int i = 0; i < len; i++) {
		if (s[i] == '.' || s[i] == ',') {
			writer = right;
			continue;
		}
		if (s[i] == 'e' || s[i] == 'E') {
			writer = exp;
			continue;
		}

		if (s[i] >= '0' && s[i] <= '9' || s[i] == '-') {
			*writer = s[i];
			writer++;
		}
	}

	double l = atof(left);
	double r = atof(right);
	double e = strlen(right);

	double result = l + r * pow(10, -e);

	e = atof(exp);
	result *= pow(10, e);

	return result;
}