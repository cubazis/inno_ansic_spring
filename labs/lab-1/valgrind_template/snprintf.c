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