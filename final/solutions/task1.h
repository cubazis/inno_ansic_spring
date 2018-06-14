#include	<stdio.h>
#define	PTR *
#define	CALL *call
#define	CHAR static char *
#define	MAGIC PTR&call
#define	I int*
#define	F float*
#define	OP(op1,	op2) ((op1) + (op2))
#define	CHARS(message)(printf(message, message))
#define	BODY char CALL(I i, F j)
BODY{
	CHAR s="%s%y%m%b%o%l%s";
	return OP(s,OP(*i,(int)(*j)));
}