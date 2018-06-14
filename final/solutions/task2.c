#include "stdio.h"

struct	circus{
	struct	circus	*prev;
	int	i;
	struct	circus	*next;
} AAA;

int are_equal(struct circus *s1, struct	circus *s2)
{
	return	(!(s1->prev == s2->next) || s1->next !=	s2->prev);
}

void main() {
	struct circus abc,def,ghi,jkl;
	abc.i=0;
	abc.prev=&jkl;
	abc.next=&def;
	def.i=1;
	def.prev=&abc;
	def.next=&ghi;
	ghi.i=2;
	ghi.prev=&def;
	ghi.next=&jkl;
	jkl.i=8;
	jkl.prev=&ghi;
	jkl.next=&abc;
	if (are_equal(&abc, &def))
	{
		printf("%d",	jkl.next->next->prev->next->i);
		printf("%1.1f", (float)jkl.next->next->prev->next->i
		//printf("%d.0", jkl.next->next->prev->next->i
		                       +
		                       abc.next->next->prev->next->i);
		printf("%u",def.next->next->prev->next->i
		            -
		            abc.next->next->prev->next->i);
		printf(".");
		printf("%d",abc.next->next->prev->next->i);
		printf("%u",ghi.next->next->prev->next->i);
		printf("%d",jkl.next->next->prev->next->i);
		printf("%d",def.next->next->prev->next->i);
	}
}