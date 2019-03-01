//
// Created by cubazis on 24.05.18.
//

#include "random.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>

double uniform_distribution(void)
{
	double limit = pow(2.0, DBL_MANT_DIG);
	double denom = RAND_MAX + 1.0;
	double denom_to_k = 1.0;
	double numer = 0.0;

	for ( ; denom_to_k < limit; denom_to_k *= denom )
		numer += rand() * denom_to_k;


	double result = numer / denom_to_k;
	if (result == 1.0)
		result -= DBL_EPSILON/2;
	assert(result != 1.0);
	return result;
}