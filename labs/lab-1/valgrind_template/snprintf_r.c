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