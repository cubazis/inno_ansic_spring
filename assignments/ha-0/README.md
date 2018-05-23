# HA-0
___
### Home assignment #0

**Pay attention!**

This task is aimed at preparing you for the successful completion of laboratory work and homework.

For successful execution, first make sure that you have the *CLion* IDE installed, and the *C99* compiler.

**Task**

Write two functions that print into the output stream [two's complement code](https://en.wikipedia.org/wiki/Two%27s_complement) of arbitrary numbers. 

The first function named *binarize_u* should get arbitrary **unsigned** number as input and print to the output stream a binary representation of it.

Output Format has to be in the form of four bytes separated by one space symbol:
`01011111 11100001 11011100 01100110`

The second function named *binarize_s* should get arbitrary **signed** number as input and print to the output stream a binary representation of it.

Output Format has to be in the form of four bytes separated by one space symbol:
`10100000 00011110 00100011 10011010`

___

**1. Create a C project in CLion**

If you are new to Clion, please use [this](https://www.jetbrains.com/help/clion/clion-quick-start-guide.html). Windows users, please use [this](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html) and [this](https://engineroom.teamwork.com/using-cygwins-bash-terminal-in-a-jetbrains-ide-d22dd71b52b4)

By creating C project, be careful and check that you correctly choose *C executable* and *C99* compiler. Like this
![GitHub](https://github.com/cubazis/inno_ansic_spring/blob/master/imgs/clion0.jpg). 

Then please keep this certain structure of C project from the [template](https://github.com/cubazis/inno_ansic_spring/tree/master/assignments/ha-0/template).

```
ha-0
|-- CMakeLists.txt
|-- binarize.c
|-- binarize.h
|-- test_binarize.c    
```

**Code transcription**

*test_binarize.c* contains simple test suite for code correctness. For example:

```C
#include <stdio.h>
#include "binarize.h"

int main() {
    unsigned long ul = 1608637542;
    signed long sl = -1608637542;
    binarize_u(ul);
    binarize_s(sl);
}
```

*binarize_u* has to print
`01011111 11100001 11011100 01100110`

*binarize_s* has to print
`10100000 00011110 00100011 10011010`

*binarize.h* contains headers like this:

```C
#include <limits.h>
#include <stdio.h>

#ifndef TEMPLATE_BINARIZE_H
#define TEMPLATE_BINARIZE_H

#endif //TEMPLATE_BINARIZE_H

void binarize_u(unsigned long long x);

void binarize_s(signed long long y);
```

*binarize.c* contains implementation of functions like this:

```C
#include "binarize.h"

void binarize_u(unsigned long long x){
    // YOUR CODE HERE PLEASE
}

void binarize_s(signed long long y){
    // YOUR CODE HERE PLEASE
}
```

___

**2. Push it on github**
To do that create a repository of the project in you github.com account and by using this [certain example](https://github.com/cubazis/inno_ansic_spring/wiki/C-on-Git-(HowTo)) push it on there.

___

**3. Add me as collaborator**
![GitHub](https://github.com/cubazis/inno_ansic_spring/blob/master/imgs/git0.jpg)

___
**Deadline**
Try to finish it before the lab session 12:20, 24 May
