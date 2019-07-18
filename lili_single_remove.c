#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/lili.h"

// This only works for middle nodes
// (not heads or tails)
void ll_remove_mid(ll_node * node)
{
    ll_node *next = node->next;

    node->value = next->value;
    node->next = next->next;
    free(next);
}

#ifdef TEST_lili_single_remove
void test_ll_remove_mid()
{
    int vals[] = { 4, 7, 6, 5 };
    ll_node *l = ll_from_array(vals, 4);

    int expected_vals[] = { 4, 7, 5 };
    ll_node *e = ll_from_array(expected_vals, 3);

    printf("Checking removing nodes from list:\n");
    ll_print(l);
    printf("Expecting:\n");
    ll_print(e);

    ll_remove_mid(l->next->next);
    printf("Result:\n");
    ll_print(l);

    assert(ll_eq(l, e));

    ll_destroy(l);
    ll_destroy(e);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_remove_mid();
}
#endif
