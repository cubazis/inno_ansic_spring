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

/** YOUR SOLUTIONS */

char* detab(const char input[])
{
	/** JUST TO CHECK */
	char* c = ALLOCATE(10);
	return c;
}

char* entab(const char input[])
{
	/** JUST TO CHECK */
	char* c = ALLOCATE(10);
	int size = 0;
	STRING_LEN(size, input);
	return c;
}

/** GET FROM task.h */