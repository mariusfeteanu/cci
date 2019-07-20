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
    printf("s1 (free: %d): ", s1->free_space);
    stack_print(s1);
    printf("s2 (free: %d): ", s2->free_space);
    stack_print(s2);
    printf("s3 (free: %d): ", s2->free_space);
    stack_print(s3);
    printf("st: ");
    print_storage(storage);
}

int stack_shared_push(stack *main_stack,
                       stack *shared_stack,
                       int shared_space,
                       int value){
    int total_free_space = main_stack->free_space + shared_stack->free_space - shared_space;
    assert(total_free_space>0);
    stack_push(main_stack, value);
    return total_free_space - 1; // account for the one we just allocated
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
    printf("shared space left: %d.\n",
           stack_shared_push(s2, s3, ST_SIZE-2, 3));
    printf("shared space left: %d.\n",
           stack_shared_push(s3, s2, ST_SIZE-2, 10));
    printf("shared space left: %d.\n",
           stack_shared_push(s3, s3, ST_SIZE-2, 9));
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
