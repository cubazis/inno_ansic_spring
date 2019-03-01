#include "stdio.h"


/** Example №76
 *
 *  + structures
 *  + structures comparing
 *  + self-referenced structures
 *  + the % format fpecifiers
 *  + type casting
 */

struct aaa{
	struct aaa *prev;
	int i;
	struct aaa *next;
};

void main() {
	struct aaa abc,def,ghi,jkl;
	int x=100;
	abc.i=0;
	abc.prev = &jkl;
	abc.next = &def;
	def.i = 1;
	def.prev = &abc;
	def.next = &ghi;
	ghi.i = 2;
	ghi.prev = &def;
	ghi.next = &jkl;
	jkl.i=3;
	jkl.prev=&ghi;
	jkl.next=&abc;
	x=abc.next->next->prev->next->i;
	printf("%d",x);
}