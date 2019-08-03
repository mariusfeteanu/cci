#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "common/stack.h"
#include "common/lili.h"

#define ST_SIZE 20

typedef struct stack_min_s {
    stack *stack;
    stack *min;
} stack_min;


stack_min *stack_min_create(int *storage, int max_size)
{
    stack_min *empty = malloc(sizeof(stack_min));
    empty->stack = stack_create(storage, max_size, 1);
    empty->min = stack_create(storage + max_size, max_size, -1);
    return empty;
}

void stack_min_destroy(stack_min * s)
{
    free(s->stack);
    free(s->min);
    free(s);
}

int stack_min_pop(stack_min * s)
{
    int value = stack_pop(s->stack);
    int current_min = stack_peek(s->min);
    if (current_min == value) {
        stack_pop(s->min);
    }
    return value;
}

void stack_min_push(stack_min * s, int value)
{
    stack_push(s->stack, value);

    if (!stack_is_empty(s->min)) {
        if (stack_peek(s->min) > value) {
            stack_push(s->min, value);
        }
    } else {
        stack_push(s->min, value);
    }
}

int stack_min_peek(stack_min * s)
{
    return stack_peek(s->stack);
}

int stack_min_is_empty(stack_min * s)
{
    return stack_is_empty(s->stack);
}

void stack_min_print(stack_min * s)
{
    stack_print(s->stack);
}

int stack_min_get(stack_min * s)
{
    return stack_peek(s->min);
}

#ifdef TEST_stack_min

void print_storage(int *storage)
{
    printf("< ");
    for (int i = 0; i < ST_SIZE; i++) {
        printf("%d ", storage[i]);
    }
    printf(">\n");
}

void test_stack_min()
{
    int storage[ST_SIZE] = { 0 };

    stack_min *s1 = stack_min_create(storage, ST_SIZE);

    stack_min_print(s1);
    assert(stack_min_is_empty(s1));

    stack_min_push(s1, 5);
    print_storage(storage);
    stack_min_push(s1, 7);
    print_storage(storage);
    stack_min_push(s1, 4);
    print_storage(storage);
    assert(stack_min_get(s1) == 4);
    stack_min_push(s1, 2);
    print_storage(storage);
    stack_min_push(s1, 9);
    print_storage(storage);

    assert(stack_min_get(s1) == 2);

    stack_min_pop(s1);
    stack_min_pop(s1);
    assert(stack_min_get(s1) == 4);
    assert(stack_min_peek(s1) == 4);

    stack_min_destroy(s1);
}

int main()
{
    test_stack_min();
}
#endif
