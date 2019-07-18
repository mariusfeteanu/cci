#include <stdio.h>
#include "common/lili.h"

ll_node *ll_find_klast(ll_node *node, int k)
{
    ll_node *runn = node;
    ll_node *curr = node;

    // run ahead k steps
    while (k > 0 && runn->next) {
        runn = runn->next;
        k--;
    }

    while (runn->next) {
        curr = curr->next;
        runn = runn->next;
    }

    return curr;
}

#ifdef TEST_lili_find_klast
void test_ll_find_klast()
{
    printf("Finding klast.\n");

    int vals[] = { 4, 2, 1, 4, 10, 13, 5, 6, 7 };
    ll_node *l = ll_from_array(vals, 9);

    int expected_last = 13;

    ll_print(l);

    int klast = ll_find_klast(l, 3)->value;
    printf("Expected %d, found %d.\n", expected_last, klast);

    assert(expected_last == klast);

    ll_destroy(l);
}

void test_ll_find_klast_single()
{
    printf("Finding klast.\n");

    int vals[] = { 4 };
    ll_node *l = ll_from_array(vals, 1);

    int expected_last = 4;

    ll_print(l);

    int klast = ll_find_klast(l, 1)->value;
    printf("Expected %d, found %d.\n", expected_last, klast);

    assert(expected_last == klast);

    ll_destroy(l);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_find_klast();
    test_ll_find_klast_single();
}
#endif
