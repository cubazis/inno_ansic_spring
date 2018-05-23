#include <stdio.h>
#include "binarize.h"

int main() {
	unsigned long ul = 1608637542;
	signed long sl = -1608637542;
	binarize_u(ul);
	binarize_s(sl);
}