//
// Created by cubazis on 05.06.18.
//

#include "pointers.h"






int valid(void *ptr)
{
	return (ptr != NULL);
}








int valid_etext(void *ptr)
{
	extern char _etext;
	return (ptr != NULL) && ((char*) ptr > &_etext);
}







/** It ensures that its argument is not a null pointer.
 *  But the pointer could still be invalid,
 *  causing the function to corrupt memory or terminate abnormally.
 * @param intptr
 * */
void incr_bad(int *intptr) {
	if (intptr == NULL) {
		/* Handle error */
	}
	*intptr++;
}







/**
 * The resulting implementation is less likely to dereference
 * an invalid pointer or write to memory that is outside
 * the bounds of a valid object.
 * @param intptr
 */
void incr(int *intptr) {
	if (!valid(intptr)) {
		/* Handle error */
	}
	*intptr++;
}


void replace(char buffer[], char replacement, size_t size)
{
	size_t count = 0;
	while(*buffer != NULL && count++<size) {
		*buffer = replacement;
		buffer++;
	}
}

/** Functions */

int getSystemStatus() {
	int status = 0;
	return status;
}