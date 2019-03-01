#include <stdio.h>

/**
 * What will be the output
 */

#define p(x) *x
#define ref(x) &x
#define assign(x, val){       \
                (x) = (val);  \
                return ref(x);\
	}                     \

#define ptnt(x) int p(x)
#define aptnt auto ptnt(x);
#define body ptnt(function())

body{
	static int a;
	assign(a,6*7);
}

ptnt(main)() {
	aptnt
	ptnt((p(ptr))());
	ptr = ref(function);
	x = (p(ptr))();
	printf("%d",p(x));
}


