# Lab Session 05/06

## Humor 

Python: What if everything was a dict?
Java: What if everything was an object?
JavaScript: What if everything was a dict *and* an object?
C: What if everything was a pointer?
APL: What if everything was an array?
Tcl: What if everything was a string?
Prolog: What if everything was a term?
Lisp: What if everything was a pair?
Scheme: What if everything was a function?
Haskell: What if everything was a monad?
Assembly: What if everything was a register?
Coq: What if everything was a type/proposition?
COBOL: WHAT IF EVERYTHING WAS UPPERCASE?
C#: What if everything was like Java, but different?
Ruby: What if everything was monkey patched?
Pascal: BEGIN What if everything was structured? END
C++: What if we added everything to the language?
C++11: What if we forgot to stop adding stuff?
Rust: What if garbage collection didn't exist?
Go: What if we tried designing C a second time?
Perl: What if shell, sed, and awk were one language?
Perl6: What if we took the joke too far?
PHP: What if we wanted to make SQL injection easier?
VB: What if we wanted to allow anyone to program?
VB .NET: What if we wanted them to stop again?
Forth: What if everything was a stack?
ColorForth: What if the stack was green?
PostScript: What if everything was printed at 600dpi?
XSLT: What if everything was an XML element?
Make: What if everything was a dependency?
m4: What if everything was incomprehensibly quoted?
Scala: What if Haskell ran on the JVM?
Clojure: What if Lisp ran on the JVM?
Lua: What if game developers got tired of C++?
Mathematica: What if Steven Wolfram invented everything?
Malbolge: What if there is no god?

## Security & Improper Pointers Use Cases
___

* The responsibility of securing an application largely falls on the developer.

* Writing secure applications in C can be difficult because of several inherent aspects of the language.

* Unpredictable behavior of pointers
    * Memory
    * Process

*Stay up to date* with [CERT](https://www.sei.cmu.edu/about/divisions/cert/index.cfm)

___

### Techniques

* Address Space Layout Randomization (ASLR)

*ASLR* process arranges an application’s data region randomly in memory.

[*return-to-libc* attack](https://ru.wikipedia.org/wiki/%D0%90%D1%82%D0%B0%D0%BA%D0%B0_%D0%B2%D0%BE%D0%B7%D0%B2%D1%80%D0%B0%D1%82%D0%B0_%D0%B2_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA%D1%83)

* Data Execution Prevention (DEP)

DEP technique prevents the execution of code if it is in a nonexecutable region of memory.

#### Narrow places

• Declaration and initialization of pointers
• Improper pointer usage
• Deallocation problems

___

### Declaration and initialization

Improper Pointer Declaration
```C
int* ptr1, ptr2;
```


Proper Pointer Declaration
```C
int *ptr1, *ptr2;
```

**Notice:** *It is an even better practice to declare each variable on its own line.*


Another good practice involves using type definitions instead of macro definitions.

```C
#define PINT int*
PINT ptr1, ptr2;
```
A better approach:

```C
typedef int* PINT;
PINT ptr1, ptr2;
```

#### Wild pointer

```C
int *pi;
...
printf("%d\n",*pi);
```

#### Uninitialized Pointers

Handling
```C
int *pi = NULL;
...
if(pi == NULL) {
    // pi should not be dereferenced
} else {
    // pi can be used
}
```

Assertion

```C
assert(pi != NULL);
```

Using Static Analysis Tools

___


### Pointer Usage

• Not checking the index values used when accessing an array’s elements

• Not being careful when performing pointer arithmetic with array pointers

• Using functions such as gets to read in a string from standard input

• Using functions such as *[strcpy](https://ru.wikipedia.org/wiki/Strcpy)* and *[strcat](https://ru.wikipedia.org/wiki/Strcpy)* improperly

```C
char *strcpy (char *dst, const char *src);

char * strcat( char * destptr, const char * srcptr );
```

![GitHub](![GitHub](https://github.com/cubazis/inno_ansic_spring/blob/dev/imgs/classic.jpg))

#### NULL Test

```C
float *vector = malloc(20 * sizeof(float));
if(vector == NULL) {
    // malloc failed to allocate memory
} else {
    // Process vector
}
```

#### Dereference Operator

A common approach for declaring and initializing a pointer
```C
int num;
int *pi = &num;
```

Another seemingly equivalent declaration

```C
int num;
int *pi;
*pi = &num;
```
The pointer, pi , has not been initialized yet. We have made a simple mistake of misusing the dereference operator.

```C
int num;
int *pi;
pi = &num;
```

#### Dangling Pointers
A dangling pointer occurs when a pointer is freed but still references that memory.
```C
int *pi = (int*) malloc(sizeof(int));
*pi = 5;
printf("*pi: %d\n", *pi);
free(pi);
```
![GitHub](![GitHub](https://github.com/cubazis/inno_ansic_spring/blob/dev/imgs/dangling.jpg))

#### Outside the Bounds

```C

char firstName[8] = "_______";
char middleName[8] = "_______";
char lastName[8] = "_______";

middleName[-11] = 'X';
middleName[0] = 'X';
middleName[18] = 'X';

printf("%p %s\n", firstName,firstName);
printf("%p %s\n", middleName,middleName);
printf("%p %s\n", lastName,lastName);
```
![GitHub](![GitHub](https://github.com/cubazis/inno_ansic_spring/blob/dev/imgs/obounds.jpg))

#### Calculating the Array Size

*replace* function implementation
```C
void replace(char buffer[], char replacement, size_t size)
{
	size_t count = 0;
	while(*buffer != NULL && count++<size) {
		*buffer = replacement;
		buffer++;
	}
}
```

Tcase

```C
char name[8];
strcpy(name,"Alexander");
replace(name,'+',sizeof(name));
printf("%s\n", name);
```

#### Sizeof op misusing

```C
int buffer[20];
int *pbuffer = buffer;
for(int i=0; i<sizeof(buffer); i++) {
    *(pbuffer++) = 0;
}
```

#### Bounded Pointers
```C
#define SIZE 32
char name[SIZE];
char *p = name;
if(name != NULL) {
    if(p >= name && p < name+SIZE) {
        // Valid pointer - continue
    } else {
        // Invalid pointer - error condition
    }
}
```

* Using Static Analysis Tools

* pointer validation function

* [Bounded Model Checking](http://www.cprover.org/cbmc/)

___

#### Pointer Validation Function DEMO
___



#### String Security

```C
char firstName [8];
int result;
result = strcpy_s(firstName,sizeof(firstName),"Alexander");
```

#### Format String Attack
```C
int main(int argc, char** argv) {
    printf(argv[1]);
    ...
}
```

```bash
./a.out
> > > "User Supplied Input"
```

Functions such as printf , fprintf , snprintf , and syslog all have a format string as an argument.

The simplest defense against this type of attack is to never use a user-supplied format string with these functions.

#### Pointer Arithmetic and Structures

Structures

```C
typedef struct _employee {
	char name[10];
	int age;
} Employee;

typedef struct _item {
	int partNumber;
	int quantity;
	int binNumber;
} Item;
```

Tcases

```C
START_TEST(test_structers_2)
{
	// Not guaranteed to work
	Item part = {12345, 35, 107};
	int *pi = &part.partNumber;
	printf("Part number: %d\n",*pi);
	pi++;
	printf("Quantity: %d\n",*pi);
	pi++;
	printf("Bin number: %d\n",*pi);
}
END_TEST

START_TEST(test_structers_2_better)
{
	Item part = {12345, 35, 107};
	int *pi = &part.partNumber;
	printf("Part number: %d\n",*pi);
	pi = &part.quantity;
	printf("Quantity: %d\n",*pi);
	pi = &part.binNumber;
	printf("Bin number: %d\n",*pi);
}
END_TEST

START_TEST(test_structers_2_much_more_better)
{
	Item part = {12345, 35, 107};
	printf("Part number: %d\n",part.partNumber);
	printf("Quantity: %d\n",part.quantity);
	printf("Bin number: %d\n",part.binNumber);
}
END_TEST
```

#### Functions

The Function
```C
int getSystemStatus() {
    int status;
    ...
    return status;
}
```

Test Cases

```C
if(getSystemStatus() == 0) {
    printf("Status is 0\n");
} else {
    printf("Status is not 0\n");
}
```

and

```C
if(getSystemStatus == 0) {
    printf("Status is 0\n");
} else {
    printf("Status is not 0\n");
}
```

Same problem with different signatures

```C
int (*fptrCompute)(int,int);
int add(int n1, int n2, int n3) {
    return n1+n2+n3;
}
fptrCompute = add;
fptrCompute(2,5);
```

### Memory Deallocation4

#### Double Free
```C
int *pi = (int*) malloc(sizeof(int));
*pi = 5;
free(pi);

int sum = 0;
for (int i = 0; i < 14; ++i) {
    sum += i;
}
free(pi);
```

#### Clearing Sensitive Data
```C
char name[32];
int userID;
char *securityQuestion;

for (int i = 0; i < 32; ++i) {
    name[i] = (char)i;
}
userID = 42;
securityQuestion = name;

memset(name,0,sizeof(name));
userID = 0;
memset(securityQuestion,0,strlen(securityQuestion));
```

or

```C
char *name = (char*)malloc(32* sizeof(char));
for (int i = 0; i < 32; ++i) {
    name[i] = (char)i;
}
memset(name,0,sizeof(name));
free(name);
```

#### Static Analysis Tools

*-Wall*
