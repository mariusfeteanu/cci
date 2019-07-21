#pragma once
typedef struct stack_s {
    int free_space;
    int *head;
    int stride;
    int *storage;
} stack;

stack *stack_create(int *storage, int max_size, int stride);
void stack_destroy(stack * s);
int stack_pop(stack * s);
void stack_push(stack * s, int value);
int stack_peek(stack * s);
int stack_is_empty(stack * s);
void stack_print(stack * s);
