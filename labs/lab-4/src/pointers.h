//
// Created by cubazis on 05.06.18.
//

#include "stdio.h"

#ifndef TEMPLATE_IPD_H
#define TEMPLATE_IPD_H

typedef struct _employee {
	char name[10];
	int age;
} Employee;

typedef struct _item {
	int partNumber;
	int quantity;
	int binNumber;
} Item;

int valid(void *ptr);

int valid_etext(void *ptr);

void incr_bad(int *intptr);

void incr(int *intptr);

void replace(char buffer[], char replacement, size_t size);

int getSystemStatus();

#endif //TEMPLATE_IPD_H

