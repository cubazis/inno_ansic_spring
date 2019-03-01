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