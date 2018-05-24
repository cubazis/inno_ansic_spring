#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
  char *str;
  asprintf(&str, "Hello, %s!\n", "Habr");
  printf("->\t%s", str);
  free(str);
}