//
// Created by puzankova 30.05.18
//

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define MAX_QUEUE_SIZE 100

int insert(double value, int key);

double extract_min();

#endif //__QUEUE_H