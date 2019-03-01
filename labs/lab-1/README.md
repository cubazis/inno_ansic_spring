# Lab Session 24/05
___


## Cmake First Step

Create a new C project in CLion.

You see basic project structure

```shell=
.
|— cmake-build-debug
|— CMakeLists.txt
|- main.c
External Libraries
```
This is not what I would like. I want to introduce you to such a useful thing as the library Check. I truly believe in what you know about unit testing and assembly process. 

You can use these link to familiarize Cmake. 
[CMake-Based Project](http://preshing.com/20170511/how-to-build-a-cmake-based-project/)

[Cmake Docs](https://cmake.org/cmake/help/v3.0/manual/cmake-language.7.html#bracket-comment)

We need such structure
```shell=
.
|— cmake-build-debug
|— CMakeLists.txt
|— CMakeModules
    |- FindCheck.cmake
|- tests
    |- CMakeLists.txt
    |- test_random.c
|- src
    |- random.c
    |- random.h
External Libraries    
```

**CMakeLists.txt**
```Cmake
cmake_minimum_required ( VERSION 2.6 )
```
Укажите здесь имя вашего проекта.
Учитываете установку переменных 
```Cmake
<project_name>_BINARY_DIR и  <project_name>_SOURCE_DIR
```
в значение имени каталога с проектом.
```Cmake
project ( project_name )

set ( SRC_DIR ${PROJECT_SOURCE_DIR}/src )
```
Укажите вместо my-project имя своего приложения
- имя исполняемого файла
```Cmake
set ( APP_NAME my-project )
```
Управление типом сборки через задание значения
предопределенной переменной CMAKE_BUILD_TYPE
Возможные значения:
```Cmake
DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL
set( CMAKE_BUILD_TYPE RELEASE )
```
Снять комментарий для добавления пути на 
заголовочные файлы, которые следует добавить 
для компиляции проекта
```Cmake
#include_directories ( /path/to/headers_1 )
#include_directories ( /path/to/headers_2 )
...
#include_directories ( /path/to/headers_N )
```
Снять комментарий для добавления пути на 
библиотеки, которые следует добавить 
для линковки проекта

```Cmake
#link_directories ( /path/to/lib_1 )
#link_directories ( /path/to/lib_2 )
...
#link_directories ( /path/to/lib_N )

list(APPEND SRC ${SRC_DIR}/main.cpp )
```

снять комментарий для добавления других *.cpp файлов

```
list(APPEND SRC ${SRC_DIR}/file_1.cpp )
list(APPEND SRC ${SRC_DIR}/file_2.cpp )
...
list(APPEND SRC ${SRC_DIR}/file_N.cpp )

add_executable ( ${APP_NAME} ${SRC} )
```


Снять комментарий для добавления имени библиотеки
требуемой для линковки проекта

```
#target_link_libraries( ${APP_NAME} name_1 )
#target_link_libraries( ${APP_NAME} name_2 )
...
#target_link_libraries( ${APP_NAME} name_N )

```

```Cmake
cmake_minimum_required
```
выставляет требование по минимальной версии CMake, требуемой для обработки даного файла конфигурации.

```Cmake 
project(<project_name>)
```
задает имя проекта. Необходимо учитывать, что дополнительной функцией данной команды является установка переменных <project_name>_BINARY_DIR и <project_name>_SOURCE_DIR в значение имени каталога проекта.

```Cmake
set
```
задает значение переменной для дальнейшего использования. Здесь создаем переменную SRC_DIR по значению подставленному из предопределенной переменной PROJECT_SOURCE_DIR и подстроки "/src". Чтобы получить значение переменной, её идентификатор надо поместить в фигурные скобки и предварить знаком доллара - ${...}.

```Cmake
include_directories
```
добавить указанный в скобках каталог к списку каталогов поиска заголовочных файлов. В одной команде можно указать несколько каталогов заголовочных файлов, разделив их пробелом.

```Cmake
link_directories
```
добавить указанный в скобках каталог к списку каталогов поиска библиотек для линковки. В одной команде можно указать несколько каталогов библиотек, разделив их пробелом.

```Cmake
list
```
с первым аргументом APPEND выполняет добавление к списку, указанному вторым аргументом, элемента заданного третьим аргументом. В нашем случае, к списку под именем SRC добавлено имя файла main.cpp с путем, указанным значением переменной SRC_DIR.

```Cmake
add_executable
```
для сборки исполняемого файла представленного первым аргументом добавляет компиляционные листы, которые будут образованы по списку файлов источников, заданных вторым аргументом - значением списка SRC.

```Cmake
target_link_libraries
```
задает библиотеки для линковки. Исполняемый файл указывается первым аргументом. Например, если в Linux требуется указать для линковки приложения my-project библиотеки с именем файла libm.so, то следует написать target_link_libraries(my-project m), что соответствует общим правилам задания имени библиотек в опциях для линковки. В одной команде можно указать несколько библиотек, разделив их пробелом.

Представленный вариант файла CMakeList.txt можно взять как шаблон для своих проектов. Чтобы собрать такой проект, надо в каталоге с файлом CMakeLists.txt выполнить команду "cmake ." (не забудьте про точку, обозначающую синоним для имени текущего каталога - в нем будет осуществлён поиск файла CMakeLists.txt). По этой команде будет создан Makefile, который потом следует обработать утилитой make. Для этого надо просто выполнить команду "make".

```shell=
cd build
cmake ..
make
```

```Cmake
cmake_minimum_required(VERSION 3.8)
project(cmake_first_step)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Wshadow")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

enable_testing()
add_subdirectory(tests)
```
FindCheck.cmake
```Cmake
# - Try to find the CHECK libraries
#  Once done this will define
#
#  CHECK_FOUND - system has check
#  CHECK_INCLUDE_DIRS - the check include directory
#  CHECK_LIBRARIES - check library
# 
#  Copyright (c) 2007 Daniel Gollub <dgollub@suse.de>
#  Copyright (c) 2007 Bjoern Ricks  <b.ricks@fh-osnabrueck.de>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.

INCLUDE( FindPkgConfig )

# Take care about check.pc settings
PKG_SEARCH_MODULE( CHECK check )

# Look for CHECK include dir and libraries
IF( NOT CHECK_FOUND )

        FIND_PATH( CHECK_INCLUDE_DIRS check.h )

        FIND_LIBRARY( CHECK_LIBRARIES NAMES check )

        IF ( CHECK_INCLUDE_DIRS AND CHECK_LIBRARIES )
                SET( CHECK_FOUND 1 )
                IF ( NOT Check_FIND_QUIETLY )
                        MESSAGE ( STATUS "Found CHECK: ${CHECK_LIBRARIES}" )
                ENDIF ( NOT Check_FIND_QUIETLY )
        ELSE ( CHECK_INCLUDE_DIRS AND CHECK_LIBRARIES )
                IF ( Check_FIND_REQUIRED )
                        MESSAGE( FATAL_ERROR "Could NOT find CHECK" )
                ELSE ( Check_FIND_REQUIRED )
                        IF ( NOT Check_FIND_QUIETLY )
                                MESSAGE( STATUS "Could NOT find CHECK" )       
                        ENDIF ( NOT Check_FIND_QUIETLY )
                ENDIF ( Check_FIND_REQUIRED )
        ENDIF ( CHECK_INCLUDE_DIRS AND CHECK_LIBRARIES )
ENDIF( NOT CHECK_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( CHECK_INCLUDE_DIRS CHECK_LIBRARIES )
```
CMakeLists.txt
```Cmake
enable_testing()

find_package(Check REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

include_directories(. ../src)

add_executable(test_random test_random.c ../src/random.c)

target_link_libraries(test_random ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(test_random ${CMAKE_CURRENT_BINARY_DIR}/test_binarize)
```
**test-random.c**
```//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "random.h"
#include "math.h"

#define MAX_L 1000000

const double tolerance = 1e-3;
const double tolerance_strict = 1e-9;

#define ck_assert_double_eq_tol(val, ref, tol) \
	ck_assert(fabs(((val))-((ref))) < tol);

#define ck_assert_double_eq(val, ref) \
	ck_assert_double_eq_tol(val, ref, tolerance_strict);

START_TEST (test_bin)
{
	double samples[MAX_L];
	double sum = 0;
	for (int i = 0; i < MAX_L; ++i) {
		samples[i] = uniform_distribution();
		//printf("%lf\n", samples[i]);
		sum += samples[i];
	}
	double res = 0;
	printf("%lf\n", res = sum/MAX_L);
	ck_assert_double_eq_tol(res, .499, tolerance);
	ck_assert_double_eq(res, .499);
}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("random");
	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test_bin);
	suite_add_tcase(suite, tcase);
	return suite;
}

int main (int argc, char *argv[]) {
	int number_failed;
	Suite *suite = str_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return number_failed;
}
```


**random.h**

```C
#ifndef RANDOM_RANDOM_H
#define RANDOM_RANDOM_H

#include <limits.h>
#include <stdio.h>

double uniform_distribution(void);

#endif //RANDOM_RANDOM_H
```

**random.c**
```C
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
```


[Cmake with Check](https://isti.bitbucket.io/2012/06/01/cmake-check.html)

## C Foundations


* Тип char по умолчанию знаковый или нет? А int?
* Законно ли неявное приведение (signed char *) к (char *)? А то же для int?
* Сколько бит в unsigned char?
* Какое максимальное число гарантированно можно поместить в int? А минимальное?
* Тип long определённо больше, чем char, не так ли?

Тип unsigned char является абстракцией машинного байта. Важность этого типа проявляется в том, что С может адресовать память только с точностью до байта. На большинстве архитектур размер байта равен 8 бит, но бывают и исключения. Например, процессоры с 36-битной архитектурой как правило имеют 9-битный байт, а в некоторых DSP от Texas Instruments байты состоят из 16 или 32 бит. Древние архитектуры могут иметь короткие байты из 4, 5 или 7 бит.

Стандарт С вынужден отказаться от допотопных архитектур и требует, чтобы байты были как минимум 8-битные. Конкретное значение (CHAR_BIT2)) для данной платформы записано в заголовочном файле limits.h.

**Symbols**
```C
printf("%d\n", 4/7);
printf("%f\n", 4/7.0);

printf("%d\n", '\0');
printf("%d\n", '\a');
printf("%d\n", '\b');
printf("%d\n", '\f');
printf("%d\n", '\n');
printf("%d\n", '\r');
printf("%d\n", '\t');
printf("%d\n", '\v');
printf("%d\n", '\\');
printf("%d\n", '\?');
printf("%d\n", '\'');
printf("%d\n", '\"');
printf("%d\n", '\077');
printf("%d\n", '\xAF');
```

**Types**

[wiki](https://en.wikipedia.org/wiki/C_data_types)

```C
#include <stdio.h>
#include <limits.h>
#include <float.h>

void printIntegerTypes(void);
void printFloatingPointTypes(void);
void printCalculatedIntegerTypes(void);


int main() {
    printCalculatedIntegerTypes();
    printIntegerTypes();
    printFloatingPointTypes();
    return 0;
}

void printIntegerTypes(void){
    printf("The number of bits in a byte %d\n", CHAR_BIT);
    printf("The maximum number of bytes in a multi-byte character %d\n", MB_LEN_MAX);
    printf("\n");
    printf("The minimum value of CHAR = %d\n", CHAR_MIN);
    printf("The maximum value of CHAR = %d\n", CHAR_MAX);
    printf("\n");
    printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
    printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
    printf("\n");
    printf("The minimum value of UNSIGNED CHAR = %d\n", 0);
    printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);
    printf("\n");
    printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
    printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);
    printf("\n");
    printf("The minimum value of UNSIGNED SHORT INT = %d\n", 0);
    printf("The maximum value of UNSIGNED SHORT INT = %u\n", USHRT_MAX);
    printf("\n");
    printf("The minimum value of INT = %d\n", INT_MIN);
    printf("The maximum value of INT = %d\n", INT_MAX);
    printf("\n");
    printf("The minimum value of UNSIGNED INT = %d\n", 0);
    printf("The maximum value of UNSIGNED INT = %u\n", UINT_MAX);
    printf("\n");
    printf("The minimum value of LONG = %ld\n", LONG_MIN);
    printf("The maximum value of LONG = %ld\n", LONG_MAX);
    printf("\n");
    printf("The minimum value of UNSIGNED LONG = %d\n", 0);
    printf("The maximum value of UNSIGNED LONG = %lu\n", ULONG_MAX);
    printf("\n");
    printf("The minimum value of LONG LONG = %lld\n", LLONG_MIN);
    printf("The maximum value of LONG LONG = %lld\n", LLONG_MAX);
    printf("\n");
    printf("The minimum value of UNSIGNED LONG LONG = %d\n", 0);
    printf("The maximum value of UNSIGNED LONG LONG = %llu\n", ULLONG_MAX);
    printf("\n");
}

void printFloatingPointTypes(void){
    printf("FLT_RADIX    = %d\n", FLT_RADIX);
    printf("DECIMAL_DIG  = %d\n", DECIMAL_DIG);
    ...
    printf("FLT_MAX_10_EXP  = %d\n",  FLT_MAX_10_EXP);
    printf("FLT_ROUNDS      = %d\n",  FLT_ROUNDS);
    printf("FLT_EVAL_METHOD = %d\n",  FLT_EVAL_METHOD);
    //printf("FLT_HAS_SUBNORM = %d\n",  FLT_HAS_SUBNORM); // C11
}

void printCalculatedIntegerTypes(void){
    printf("Signed char min = %d\n", -(char)((unsigned char) ~0 >> 1)-1);
    printf("Signed char max = %d\n", (char)((unsigned char) ~0 >> 1));
    printf("\n");
    printf("Signed short min = %d\n", -(short)((unsigned short) ~0 >> 1)-1);
    printf("Signed short max = %d\n", (short)((unsigned short) ~0 >> 1));
    printf("\n");
    printf("Signed int min = %d\n", -(int)((unsigned int) ~0 >> 1)-1);
    printf("Signed int min = %d\n", (int)((unsigned int) ~0 >> 1));
    printf("\n");
    printf("Signed long min = %ld\n", -(long)((unsigned long) ~0 >> 1)-1);
    printf("Signed long min = %ld\n", (long)((unsigned long) ~0 >> 1));
    printf("\n");

    printf("Unsigned char min = %d\n",(unsigned char) 0);
    printf("Unsigned char max = %d\n", (unsigned char) ~0);
    printf("\n");
    printf("Unsigned short min = %d\n",(unsigned short) 0);
    printf("Unsigned short max = %d\n", (unsigned short) ~0);
    printf("\n");
    printf("Unsigned int min = %u\n",(unsigned int) 0);
    printf("Unsigned int max = %u\n", (unsigned int) ~0);
    printf("\n");
    printf("Unsigned long min = %lu\n",(unsigned long) 0);
    printf("Unsigned long max = %lu\n", (unsigned long) ~0);
    printf("\n");
}

```

[Ответы](https://habr.com/post/156593/)

#### Can I use only one bit?

```C
typedef struct foo
{
    unsigned x:1;
} foo;
```

But compiler will try to optimize it.

```C
#define FLAG_FOO 0
#define FLAG_BAR 1

// in case platform does not support uint8_t
typedef unsigned char uint8_t;

uint8_t flags;

void flag_foo_set()
{
    flags |= (1 << FLAG_FOO);
}

void flag_foo_clr()
{
    flags &= ~(1 << FLAG_FOO);
}

uint8_t flag_foo_get()
{
    return flags & (1 << FLAG_FOO);
}

```

WTF?

[**Extra stuff**](https://www.badprog.com/c-type-what-are-uint8-t-uint16-t-uint32-t-and-uint64-t)

## Binarizator

**cmake_template**

```
.
|— cmake-build-debug
|— CMakeLists.txt
|— CMakeModules
    |- FindCheck.cmake
|- tests
    |- CMakeLists.txt
    |- test_binarize.c
|- src
    |- binarize.c
    |- binarize.h
External Libraries    
```
**CMakeLists.txt**

```Cmake
cmake_minimum_required(VERSION 3.8)
project(cmake_template)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Wshadow")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

enable_testing()
add_subdirectory(tests)
```


**tests/CMakeLists.txt**

```Cmake
enable_testing()

find_package(Check REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

include_directories(. ../src)

add_executable(test_binarize test_binarize.c ../src/binarize.c)

target_link_libraries(test_binarize ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(test_binarize ${CMAKE_CURRENT_BINARY_DIR}/test_binarize)
```



**tests/test_binarize.c**

```C
#include <check.h>
#include "binarize.h"
#include "math.h"


START_TEST (test_bin)
{
	printf("unsigned UINT_MAX: ");
	binarize_u(UINT_MAX);

	unsigned long x = 1608637542;
	signed long y = -1608637542;

	printf("unsigned long x: %lu\n", x);
	printf("signed long x: %ld\n", y);

	binarize_u(x);
	binarize_s(y);
}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("binarize");
	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test_bin);
	suite_add_tcase(suite, tcase);
	return suite;
}

int main (int argc, char *argv[]) {
	int number_failed;
	Suite *suite = str_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return number_failed;
}
```

**binarize.h**
```C
#ifndef BINARIZE_BINARIZE_H
#define BINARIZE_BINARIZE_H

#include <limits.h>
#include <stdio.h>


void binarize_u(unsigned long long x);

void binarize_s(signed long long y);

#endif //BINARIZE_BINARIZE_H
```

**binarize.c**

```C
#include "binarize.h"

void printBitSet(char b[])
{
	int i = 0, j = 0;
	while (b[i] != '\0'){
		if (j == 8 && (b[i+1] != '\0')){
			printf(" ");
			//printf("");
			j = 0;
		}
		printf("%c",b[i]);
		++j;
		++i;
	}
	printf("\n");
}



void bit_sum(char *b, char *o)
{
	int i = 0;
	while (b[i] != '\0'){
		++i;
	}
	--i;
	short int mask = 0;
	for (i; i >= 0 ; --i) {
		if(b[i] == '1' && o[i] == '1'){
			if(mask == 0){
				b[i] = '0';
				mask = 1;
			} else {
				b[i] = '1';
			}
		} else if ((b[i] == '1' && o[i] == '0') || (b[i] == '0' && o[i] == '1')){
			if(mask == 0){
				b[i] = '1';
			} else {
				b[i] = '0';
				mask = 1;
			}
		} else if (b[i] == '0' && o[i] == '0'){
			if(mask == 0){
				b[i] = '0';
			} else {
				b[i] = '1';
				mask = 0;
			}
		}
	}
}

void one_complement(char *b)
{
	int i = 0;
	while (b[i] != '\0'){
		if(b[i] == '1'){
			b[i] = '0';
		} else {
			b[i] = '1';
		}
		++i;
	}
}

void two_complement(char *b)
{
	/** YOUR CODE HERE */
}

void binarize_u(unsigned long long x)
{
	unsigned long long mask = 1;
	int size;
/*    if(x <= 255){
        size = 1 * 8 - 1;
    }
    else */
        if(x <= USHRT_MAX){
		size = sizeof(unsigned short int) * 8 - 1;
	} else if(x <= UINT_MAX){
		size = sizeof(unsigned int) * 8 - 1;
	} else{
		size = sizeof(unsigned long long) * 8 - 1;
	}
	mask <<= size;
	char c[size];
	int j = 0, i;
	while (j <= size){
		c[j] = '0';
		++j;
	}
	for(j = 0, i = size; j <= size; ++j, --i)
	{
		c[j] = (char) ((x & mask) ? '1' : '0');
		x <<= 1;
	}
	c[j] = '\0';
	printBitSet(c);
}

void binarize_s(signed long long y)
{
	/** YOUR CODE HERE */
	printf("STUB\n");
}
```

## Valgrind

[Valgrind](https://en.wikipedia.org/wiki/Valgrind) is a programming tool for memory debugging, memory leak detection, and profiling. Valgrind was originally designed to be a free memory debugging tool for Linux on x86, but has since evolved to become a generic framework for creating dynamic analysis tools such as checkers and profilers.


[Valgrind](https://ru.wikipedia.org/wiki/Valgrind) — инструментальное программное обеспечение, предназначенное для отладки использования памяти, обнаружения утечек памяти, а также профилирования. Название valgrind взято из германо-скандинавской мифологии, где является названием главного входа в Вальгаллу

valgrind_template
```shell=
.
|- asprintf.c
|- snprintf.c
|- snprintf_r.c
|- strcpy.c
|- strcpy_r.c
```
asprintf.c
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
  char *str;
  asprintf(&str, "Hello, %s!\n", "Habr");
  printf("->\t%s", str);
  free(str);
}
```
snprintf.c
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
/* Т.к. snprintf() не учитывает символ конца строки, прибавляем его размер к результату */
  size_t needed_mem = snprintf(NULL, 0, "Hello, %s!\n", "Habr") + sizeof('\0'); 
  char *str = malloc(needed_mem);
  snprintf(str, needed_mem, "Hello, %s!\n", "Habr");
  printf("->\t%s", str);
  free(str);
}
```
snprintf_r.c
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define strsize(args...) snprintf(NULL, 0, args) + sizeof('\0')

void main() {
  char *str = malloc(strsize("Hello, %s\n", "Habr!"));
  sprintf(str, "Hello, %s\n", "Habr!");
  printf("->\t%s", str);
  free(str);
}
```
strcpy.c
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELLO_STRING "Hello, Habr!\n"

void main() {
  char *str = malloc(sizeof(char) * strlen(HELLO_STRING));
  strcpy(str, HELLO_STRING);
  printf("->\t%s", str);
  free(str);
}
```
strcpy_r.c
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELLO_STRING "Hello, Habr!\n"

void main() {
  char *str = malloc(sizeof(char) * (strlen(HELLO_STRING) + 1));
  strcpy(str, HELLO_STRING);
  printf("->\t%s", str);
  free(str);
}
```

[Немного о строках в Си, или несколько вариантов оптимизировать неоптимизируемое](https://habr.com/post/272269/)