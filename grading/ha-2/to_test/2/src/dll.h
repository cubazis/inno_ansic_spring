#include "stdlib.h"
#include "stdio.h"

#define NIL 'N'

typedef struct Node{
    struct Node *prev,*next;
    char value;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

List* construct();

void destroy(List* list);

char* print(List* list);

void pushback(List* list, char el);

void pushfront(List* list, char el);

char popback(List* list);

char popfront(List* list);

int size(List* list);


