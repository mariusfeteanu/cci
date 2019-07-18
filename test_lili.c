#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/lili.h"

#ifdef TEST_test_lili
void test_ll_eq()
{
    ll_node *l = ll_from_array((int []){4, 7, 5, 6}, 4);

    assert(ll_eq(l, l));

    ll_destroy(l);
}

void test_ll_search()
{
    ll_node *l = ll_from_array((int []){4, 7, 6, 5}, 4);

    printf("Searching for a value in a list of ints.\n");
    ll_print(l);

    ll_node *found = ll_search(l, 6);

    assert(found->value == 6);

    ll_destroy(l);
}

void test_ll_remove()
{
    ll_node *l = ll_from_array((int []){4, 7, 6, 5}, 4);

    printf("Remove a value from a list of ints.\n");
    ll_print(l);

    l = ll_remove(l);

    assert(ll_length(l) == 3);
    assert(l->value == 7);

    ll_destroy(l);
}

void test_ll_insert()
{
    ll_node *l = ll_from_array((int[]){ 7, 6, 5 }, 3);

    printf("Checking insertion into linked list of ints.\n");

    assert(ll_get(l, 0) == 7);
    assert(ll_get(l, 1) == 6);
    assert(ll_get(l, 2) == 5);
    assert(ll_length(l) == 3);
    ll_print(l);

    l = ll_insert(l, 4);
    ll_print(l);

    assert(ll_get(l, 0) == 4);
    assert(ll_get(l, 1) == 7);
    assert(ll_get(l, 2) == 6);
    assert(ll_get(l, 3) == 5);

    ll_destroy(l);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_eq();
    test_ll_search();
    test_ll_insert();
    test_ll_remove();
}
#endif
