#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "common/stack.h"

#ifdef TEST_test_stack
void test_stack()
{
    int storage[1024] = { 0 };

    stack *s = stack_create(storage, 1024, 1);

    assert(stack_is_empty(s));
    stack_print(s);

    stack_push(s, 5);
    stack_print(s);
    stack_push(s, 6);
    stack_print(s);
    stack_push(s, 7);
    stack_print(s);

    assert(stack_peek(s) == 7);

    assert(stack_pop(s) == 7);
    stack_print(s);
    assert(stack_pop(s) == 6);
    stack_print(s);
    assert(stack_pop(s) == 5);
    stack_print(s);

    stack_destroy(s);
}

int main()
{
    setbuf(stdout, NULL);

    test_stack();
}
#endif
