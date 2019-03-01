#include "dll.h"

Node *getTail(List *list) {
    Node *p = list->head;
    for (int i = 1; i < list->size; i++) {
        p = p->next;
    }
    return p;
}

List *construct() {
    List *list = (List *) malloc(sizeof(List));
    list->size = 0;
    list->head = (Node *) malloc(sizeof(Node));
    list->head->value = NIL;
    return list;
}

void destroy(List *list) {
    free(list);
}

char *print(List *list) {
    char *res = (char *) malloc((list->size) * (sizeof(char)));
    char *iter = res;
    Node *p = list->head;
    for (int i = 0; i < list->size; i++) {
        *iter = p->value;
        printf("%c", p->value);
        p = p->next;
        iter++;
    }
    printf("\n");
    return res;
}

void pushback(List *list, char el) {
    if (list->size > 0) {
        Node *p = getTail(list);

        Node *node = (Node *) malloc(sizeof(Node));

        node->value = el;

        p->next = node;
        node->prev = p;
    } else {
        list->head->value = el;
    }
    list->size++;
}

void pushfront(List *list, char el) {
    if (list->size > 0) {
        Node *node = (Node *) malloc(sizeof(Node));

        node->value = el;

        list->head->prev = node;
        node->next = list->head;

        list->head = node;
    } else {
        list->head->value = el;
    }
    list->size++;
}

char popback(List* list){
    Node *p=getTail(list)->prev;
    free(p->next);
    list->size--;
}

char popfront(List* list){
    list->head=list->head->next;
    free(list->head->prev);
    list->size--;
}

int size(List* list){
    return list->size;
}