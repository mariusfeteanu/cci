#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

//typedef struct stack_s {
//    int free_space;
//    int *head;
//    int stride;
//    int *storage;
//} stack;

stack *stack_create(int *storage, int max_size, int stride)
{
    stack *empty = malloc(sizeof(stack));

    empty->free_space = max_size;
    empty->head = NULL;
    empty->stride = stride;
    empty->storage = storage;

    return empty;
}

void stack_destroy(stack * s)
{
    free(s);
}

int stack_pop(stack * s)
{
    int value = *s->head;
    if (s->head == s->storage) {
        s->head = NULL;
    } else {
        s->head -= s->stride;
    }
    s->free_space++;
    return value;
}

void stack_push(stack * s, int value)
{
    assert(s->free_space);

    if (s->head) {
        s->head += s->stride;
    } else {
        s->head = s->storage;
    }
    *(s->head) = value;
    s->free_space--;
}

int stack_peek(stack * s)
{
    return *s->head;
}

int stack_is_empty(stack * s)
{
    return !s->head;
}

void stack_print(stack * s)
{
    printf("[>> ");
    int *head = s->head;
    while (head) {
        printf("%d", *head);
        if (head != s->storage) {
            head -= s->stride;
        } else {
            head = NULL;
        }
        if (head)
            printf(" | ");
    }
    printf(" ]\n");
}
