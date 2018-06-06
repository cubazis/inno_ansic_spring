# Lab Session 06/06

## Security & Improper Pointers Use Cases
___

• Casting pointers
• Accessing hardware devices
• Aliasing and strict aliasing
• Use of the restrict keyword
• Threads
• Object-oriented techniques

___

### Casting Pointers

• Accessing a special purpose address
• Assigning an address to represent a port
• Determining a machine’s endianness

**Notice:** *The endianness of a machine generally refers to the order of bytes within a data type. Two common types of endian include little endian and big endian. Little endian means the low-order bytes are stored in the lowest address, while big endian means the high-order bytes are stored at the lowest address.*

```C
int num = 8;
int *pi;

pi = &num;
printf("Before: %p\n",pi);
int tmp = (int)pi;
pi = (int*)tmp;
printf("After: %p\n",pi);
```

#### Accessing a Special Purpose Address

In some low-level OS kernels the address of video RAM for a PC is 0xB8000

```C
#define VIDEO_BASE 0xB8000
int *video = (int *) VIDEO_BASE;
*video = 'A';
```

This is not typically done for video memory.

When you need to address memory at location zero, sometimes the compiler will treat it as a NULL pointer value. Access to location zero is often needed in low-level kernel programs. Here are a few techniques to address this situation:

• Set the pointer to zero (this does not always work)

• Assign a zero to an integer and then cast the integer to the pointer


• Use a union

• Use the *memset* function to assign a zero to the pointer

```C
memset((void*)&ptr, 0, sizeof(ptr));
```

On systems where addressing memory location zero is needed, the vendor will frequently have a workaround.


#### Accessing a Port

A port is both a hardware and a software concept. Servers use software ports to indicate they should receive certain messages sent to the machine. A hardware port is typically a physical input/output system component connected to an external device. By either reading or writing to a hardware port, information and commands can be processed by the program.

```C
#define PORT 0xB0000000
unsigned int volatile * const port = (unsigned int *) PORT;
```

**Notice:** *The machine uses the hexadecimal value address to designate a port.*

Compilers will sometimes temporarily use a cache, or register, to hold the value in a memory location for optimization purposes. If the external write modifies the memory location, then this change will not be reflected in the cached or register value.

Using the volatile keyword will prevent the runtime system from using a register to temporarily store the port value. Each port access requires the system to read or write to the port instead of reading a possibly stale value stored in a register. We don’t want to declare all variables as volatile, as this will prevent the compiler from performing certain types of optimizations.

```C
*port = 0x0BF4; // write to the port
value = *port; // read from the port
```


**Notice:** *It is not a good idea to access volatile memory with a nonvolatile variable. Using such a variable can result in undefined behavior.*


#### Accessing Memory using DMA

Direct Memory Access (DMA) is a low-level operation that assists in transferring data between main memory and some device. It is not part of the ANSI C specification but operating systems typically provide support for this operation. DMA operations are normally conducted in parallel with the CPU. This frees up the CPU for other processing and can result in better performance.

#### Determining the Endianness of a Machine

```C
int num = 0x12345678;
char* pc = (char*) &num;
for (int i = 0; i < 4; i++) {
printf("%p: %02x \n", pc, (unsigned char) *pc++);
}
```

#### Aliasing, Strict Aliasing, and the restrict Keyword

Two pointers are declared and are both assigned the same address

```C
int num = 5;
int* p1 = &num;
int* p2 = &num;
```    

*Strict aliasing* is another form of aliasing. Strict aliasing does not allow a pointer of one data type to alias a pointer of a different data type.

```C
float number = 3.25f;
unsigned int *ptrValue = (unsigned int *)&number;
unsigned int result = (*ptrValue & 0x80000000) == 0;
```

**Notice:** *Strict aliasing does not apply to pointers differing only by sign or qualifier. The following are all valid strict aliases:*

```C
int num;
const int *ptr1 = &num;
int *ptr2 = &num;
int volatile ptr3 = &num;
```

However, there are situations where the ability to use multiple representations of the same data can be useful. To avoid aliasing problems, several techniques are available:

• Use a union
• Disable strict aliasing
• Use a pointer to char

If your compiler has an option to disable strict aliasing, it can be turned off. The GCC compiler has the following compiler options:

• -fno-strict-aliasing to turn it off
• -fstrict-aliasing to turn it on
• -Wstrict-aliasing to warn of strict aliasing-related problems

**Notice** *Compilers do not always do a good job at reporting alias-related warnings. They can sometimes miss aliases and may sometimes report alias problems where they don’t exist. It is ultimately up to the programmer to identify alias conditions.*

Artyom Yurin: "Вопрос таков, зачем мы кастуем к char*?" Вот зочем.

A pointer to char is always assumed to potentially alias any object. Thus, it can be used safely in most situations. However, casting a pointer to one data type to a pointer to char and then casting the pointer to char to a second pointer data type will result in undefined behavior and should be avoided.


### Using a Union to Represent a Value in Multiple Ways

```C
typedef union _conversion {
    float fNum;
    unsigned int uiNum;
} Conversion;

int isPositive1(float number) {
    Conversion conversion = { .fNum =number};
    return (conversion.uiNum & 0x80000000) == 0;
}
```

Another way:

```C
typedef union _conversion2 {
    float *fNum;
    unsigned int *uiNum;
} Conversion2;

int isPositive2(float number) {
    Conversion2 conversion;
    conversion.fNum =&number;
    return (*conversion.uiNum & 0x80000000) == 0;
}
```

The following function does not use a union and violates the strict aliasing rule since the *ptrValue* pointer shares the same address as number:

```C
int isPositive3(float number) {
    unsigned int *ptrValue = (unsigned int *)&number;
    return (*ptrValue & 0x80000000) == 0;
}
```
The approach used by these functions assumes:

• The IEEE-754 floating point standard is used to represent a floating point number
• The floating number is laid out in a particular manner
• Integer and floating point pointers are aligned correctly

#### Strict Aliasing

```C

typedef struct _person {
    char* firstName;
    char* lastName;
    unsigned int age;
} Person;

typedef struct _employee {
    char* firstName;
    char* lastName;
    unsigned int age;
} Employee;

Person* person;

Employee* employee;
```

However, the pointers can reference the same object if the structure definitions differ only by their name, as illustrated below:

```C
typedef struct _person {
    char* firstName;
    char* lastName;
    unsigned int age;
} Person;

typedef Person Employee;

Person* person;
Employee* employee;
```


#### Using the restrict Keyword

C compilers assume pointers are aliased by default. Using the restrict keyword when declaring a pointer tells the compiler that the pointer is not aliased. This allows the compiler to generate more efficient code.

**Notice:** *New code development should use the restrict keyword with most pointer declarations. This will enable better code optimization. Modifying existing code may not be worth the effort.*


```C
void add(int size, double * restrict arr1, const     double * restrict arr2) {
    for (int i = 0; i < size; i++) {
    arr1[i] += arr2[i];
    }
}
```

Test

```C
double vector1[] = {1.1, 2.2, 3.3, 4.4};
double vector2[] = {1.1, 2.2, 3.3, 4.4};
add(4,vector1,vector2);
```
or

```C
double vector1[] = {1.1, 2.2, 3.3, 4.4};
double *vector3 = vector1;
add(4,vector1,vector3);
add(4,vector1,vector1);
```

Several standard C functions use the restrict keyword, including:

• void *memcpy(void * restrict s1, const void * restrict s2, size_t n);
• char *strcpy(char * restrict s1, const char * restrict s2);
• char *strncpy(char * restrict s1, const char * restrict s2, size_t n);
• int printf(const char * restrict format, ... );
• i nt sprintf(char * restrict s, const char * restrict format, ... );
• i nt snprintf(char * restrict s, size_t n, const char * restrict for
mat, ... );
• int scanf(const char * restrict format, ...);

The restrict keyword has two implications:
1. To the compiler it means it can perform certain code optimizations
2. To the programmer it means these pointers should not be aliased; otherwise, the results of the operation are undefined.


## Threads and Pointers

When threads share data, numerous problems can occur. One common problem is the corruption of data. One thread may write to an object but the thread may be suspended momentarily, leaving that object in an inconsistent state. Subsequently, a second thread may read that object before the first thread is able to resume. The second thread is now using an invalid or corrupted object.

The C11 standard implements threading, but it is not widely supported at this time. There are numerous libraries that support threads in C. We will use Portable Operating System Interface (POSIX) threads since they are readily available. Regardless of the library used, the techniques presented here should be applicable.

### Sharing Pointers Between Threads

When two or more threads share data, the data can become corrupted. To illustrate this problem, we will implement a multi-threaded function that computes the dot product of two vectors. The multiple threads will simultaneously access two vectors and a sum field. When the threads complete, the sum field will hold the dot product value.

```C
typedef struct {
    double *vectorA;
    double *vectorB;
    double sum;
    int length;
} VectorInfo;
```

The second data structure, Product , contains a pointer to a VectorInfo instance and the beginning index the dot Product vector will use. We will create a new instance of this structure for each thread with a different beginning index:

```C
typedef struct {
    VectorInfo *info;
    int beginningIndex;
} Product;
```

Since multiple threads may be accessing the sum field at the same time, it is necessary to protect this data using a mutex as declared below. A mutex allows only one thread to access a protected variable at a time. The following declares a mutex to protect the sum variable. It is declared at a global level to allow multiple threads to access it:

```C
pthread_mutex_t mutexSum;
```

The dotProduct function is shown below. When a thread is created, this function will be called. Since we are using POSIX, it is necessary to declare this function as returning void and being passed a pointer to void. This pointer passes information to the function. We will pass an instance of the Product structure. Within the function, variables are declared to hold the beginning and ending indexes. The for loop performs the actual multiplication and keeps a cumulative total in the total variable. The last part of the function locks the mutex, adds total to sum , and then unlocks the mutex. While the mutext is locked, no other threads can access the sum variable:

```C
void dotProduct(void *prod) {
    Product *product = (Product*)prod;
    VectorInfo *vectorInfo = Product->info;
    int beginningIndex = Product->beginningIndex;
    int endingIndex = beginningIndex + vectorInfo->length;
    double total = 0;
    for (int i = beginningIndex; i < endingIndex; i++) {
        total += (vectorInfo->vectorA[i] * vectorInfo->vectorB[i]);
    }
    pthread_mutex_lock(&mutexSum);
    vectorInfo->sum += total;
    pthread_mutex_unlock(&mutexSum);
    pthread_exit((void*) 0);
}
```
The code to create the threads is shown below. Two simple vectors are declared along with an instance of VectorInfo . Each vector holds 16 elements.
```C
#define NUM_THREADS 4
void threadExample() {
    VectorInfo vectorInfo;
    double vectorA[] = {1.0, 2.0, 3.0, 4.0, 5.0,
9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
    double vectorB[] = {1.0, 2.0, 3.0, 4.0, 5.0,
9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
6.0, 7.0, 8.0,
16.0};
6.0, 7.0, 8.0,
16.0};
    double sum;
    vectorInfo.vectorA = vectorA;
    vectorInfo.vectorB = vectorB;
    vectorInfo.length = 4;
```

A four-element array of threads is created next, along with code to initialize the mutex and an attribute field for the thread

```C
pthread_t threads[NUM_THREADS];
void *status;
pthread_attr_t attr;
pthread_mutex_init(&mutexSum, NULL);
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
int returnValue;
int threadNumber;
```
With each for loop iteration, a new instance of the Product structure is created. It is assigned the address of vectorInfo and a unique index based on threadNumber . The threads are then created:

```C
for (threadNumber = 0; threadNumber < NUM_THREADS; threadNumber++) {
    Product *product = (Product*) malloc(sizeof(Product));
    product->beginningIndex = threadNumber * 4;
    product->info = &vectorInfo;
    returnValue = pthread_create(&threads[threadNumber], &attr,
dotProduct, (void *) (void*) (product));
    if (returnValue) {
        printf("ERROR; Unable to create thread: %d\n", returnValue);
        exit(-1);
    }
}
```
After the for loop, the thread attribute and mutex variables are destroyed. The for loop ensures the program will wait until all four threads have completed. The dot product is then displayed.



```C
    pthread_attr_destroy(&attr);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &status);
    }
    pthread_mutex_destroy(&mutexSum);
    printf("Dot Product sum: %lf\n", vectorInfo.sum);
    pthread_exit(NULL);
}
```

The sum field is thus protected.