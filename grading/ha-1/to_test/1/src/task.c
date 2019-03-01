//
// Created by cubazis on 25.05.18.
//

#include "task.h"

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

char* detab(const char input[])
{
	int n = 0;
	while (input[n] != '\0') {
		n++;
	}

	char* output = malloc(n * 4 + 1);

	int i = 0;
	int j = 0;

	while (input[i] != '\0'){
		output[j] = input[i];

		if (input[i] == '\t') {
			for (int k = 0; k < 4; ++k) {
				output[j++] = ' ';
			}
			--j;
		}

		i++;
		j++;
	}

	output[j] = '\0';

	return output;
}

char* entab(const char input[])
{
	int n = 0;
	while (input[n] != '\0') {
		n++;
	}

	char* output = malloc(n * 4 + 1);

	int i = 0;
	int j = 0;
	int space_counter = 0;

	while (input[i] != '\0') {
		output[j] = input[i];

		if (input[i] == ' ') {
			space_counter++;
			if (space_counter == 4) {
				space_counter = 0;
				j -= 3;
				output[j] = '\t';
			}
		} else {
			space_counter = 0;
		}
		i++;
		j++;

	}

	output[j] = '\0';

	return output;
}

/** GET FROM task.h */

char* enter(int n, const char input[]){
	long long index = -1;
	int len = 0;
	int input_size = 0;
	int new_lines = 0;
	char current = ' '; //insert new line not after char, put it before
	//Find a number of new lines needed and size of the input
	for (input_size = 0; current != '\0'; input_size++){
		current = input[input_size];
		if (current == '\0'){
			continue;
		}
		if (current != ' '){
			len++;
		}
		if (current == '\n'){
			len = 0;
		}
		if (len == n + 1){
			new_lines++;
			len = 1;
		}
	}
	char* res = (char*) malloc(input_size + new_lines);
	index = 0;
	len = 0;
	//Fill res string
	for (int i = 0; i < input_size; i++) {
		current = input[i];
		//printf("char: %c idx: %d\n", current, index-1);
		if (current == '\0'){
			res[index++] = current;
			continue;
		}
		if (current != ' ') {
			len++;
		}
		if (current == '\n') {
			len = 0;
		}
		if (len == n + 1) { //Insert \n and then insert character from the input if len > n
			res[index++] = '\n';
			len = 1;
			//printf("new line! idx: %d\n", index);
		}
		res[index++] = current;
	}
	//printf("input size: %d\nnew lines: %d\nenter output: %s\n", input_size, new_lines, res);
	return (res);
}


char* squeeze(const char s1[], const char s2[]){
	char current = ' ';
	int s2_len = 0;
	int s1_len = 0;
	int res_len = 0;
	//find length of s1
	for (s2_len = 0; s2[s2_len] != '\0'; s2_len++);
	//find length of s2 and length of resulting string
	current = ' ';
	for (s1_len = 0;s1[s1_len] != '\0'; s1_len++){
		current = s1[s1_len];
		int cont = 0;
		for (int i=0;i<s2_len;i++){
			if (s2[i] == current){
				cont = 1;
				break;
			}
		}
		if (!cont){
			res_len++;
		}
	}
	//allocate space for resulting string
	char* res = (char*)malloc(res_len + 1);
	//fill result string
	current = ' ';
	int index = 0;
	for (int i=0;i <= s1_len; i++){
		current = s1[i];
		int cont = 0;
		for (int j=0;j<s2_len;j++){
			if (s2[j] == current){
				cont = 1;
				break;
			}
		}
		if (cont){
			continue;
		}
		res[index++] = current;
	}
	return (res);
}

int any(const char s1[], const char s2[]){
	int alp[257];
	//Fill alp with zeros
	for (int i=0;i<257;i++){
		alp[i] = 0;
	}
	//Fill alp with characters from s2
	for (int i=0;s2[i] != '\0';i++){
		alp[(int)(s2[i])] = 1;
	}
	//Find first index of first character from s2
	for (int i=0;s1[i] != '\0';i++){
		if (alp[(int)s1[i]]){
			return (i);
		}
	}
	return (-1);
}

unsigned setbits(unsigned x, int p, int n, unsigned y){
	p--;
	//printf("x: %u , y: %u\n", x, y);
	//isolate n rightmost bits from y and place it on (p-1)'th index
	unsigned val = ((y << (sizeof(unsigned)*8 - n)) >> p);
	//Set n bits starting from index (p-1) to 0 using mask
	unsigned mask = ~((0xffffffff << (sizeof(unsigned)*8 - n)) >> p);
	//printf("val : %u\n", val);
	//printf("mask : %u\n", mask);
	//Use mask first, and the apply val
	return ((x & mask) | val);
}

char* itoa(int n, const char s[]) {
    return itob(n, s, 10);
}

char* expand(const char s1[]) {
	char* output = malloc(1024);

	int starting_symbol = -1;
	int i = 0;
	int j = 0;

	while (s1[i] != '\0') {
		if (s1[i] == '-') {
			if (starting_symbol != -1 && s1[i + 1] != '\0' && s1[i + 1] != '-') {
				int ending_symbol = (int)(s1[i + 1]);

				j--;

				if (starting_symbol < ending_symbol) {
					for (char c = starting_symbol; c <= ending_symbol; ++c) {
						output[j++] = c;
					}
				} else {
					for (char c = starting_symbol; c >= ending_symbol; --c) {
						output[j++] = c;
					}
				}

				starting_symbol = ending_symbol;
				i++;
			} else {
				starting_symbol = -1;
				output[j++] = s1[i];
			}
		} else {
			starting_symbol = (int)(s1[i]);
			output[j++] = s1[i];
		}

		i++;
	}

	output[j] = '\0';

	return output;
}