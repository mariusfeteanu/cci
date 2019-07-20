#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "common/stack.h"

#define ST_SIZE 10

void print_storage(int *storage)
{
    printf("< ");
    for (int i = 0; i < ST_SIZE; i++) {
        printf("%d ", storage[i]);
    }
    printf(">\n");
}

void print_all(int *storage, stack * s1, stack * s2, stack * s3)
{
    printf("s1: ");
    stack_print(s1);
    printf("s2: ");
    stack_print(s2);
    printf("s3: ");
    stack_print(s3);
    printf("st: ");
    print_storage(storage);
}

#ifdef TEST_stack_three
int main()
{
    int storage[ST_SIZE] = { 0 };

    stack *s1 = stack_create(storage, 2, 1);
    // both tail stacks get all the remaining space
    stack *s2 = stack_create(storage + 2, 8, 1);
    stack *s3 = stack_create(storage + ST_SIZE - 1, 8, -1);

    print_all(storage, s1, s2, s3);

    stack_push(s1, 1);
    print_all(storage, s1, s2, s3);

    stack_push(s1, 2);
    stack_push(s2, 3);
    stack_push(s3, 10);
    stack_push(s3, 9);
    print_all(storage, s1, s2, s3);

    assert(storage[0] == 1);
    assert(storage[1] == 2);
    assert(storage[2] == 3);
    assert(storage[3] == 0);
    assert(storage[8] == 9);
    assert(storage[9] == 10);

    stack_destroy(s1);
    stack_destroy(s2);
    stack_destroy(s3);
}
#endif
