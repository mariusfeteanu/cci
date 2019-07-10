#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/lili.h"

// Removes a middle node from a single linked list
// We don't have one, so we pretend by not touching prev
//  on a doubly linked - this breaks it but it's okay for this example
// This only works for middle nodes
// (not heads or tails)
void lls_remove(ll_node * node)
{
    ll_node *next = node->next;

    node->key = next->key;
    node->key_size = next->key_size;
    node->next = next->next;
}

#ifdef TEST_lili_single_remove
void test_ll_destroy_node()
{
    int vals[] = { 4, 7, 6, 5 };
    ll_list *l = ll_from_array(vals, 4, sizeof(int));

    int expected_vals[] = { 4, 7, 5 };
    ll_list *e = ll_from_array(expected_vals, 3, sizeof(int));

    printf("Checking removing nodes from list:\n");
    ll_print_int(l);
    printf("Expecting:\n");
    ll_print_int(e);

    lls_remove(l->head->next->next);
    printf("Result:\n");
    ll_print_int(l);

    assert(ll_eq(l, e));
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_destroy_node();
}
#endif
