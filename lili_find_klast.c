#include <stdio.h>
#include "common/lili.h"

ll_node *ll_find_klast(ll_list * list, int k)
{
    ll_node *runn = list->head;
    ll_node *curr = list->head;

    // run ahead k steps
    while (k > 0 && runn) {
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
    printf("Checking duplicate removal (by value, integers, buffered).\n");

    int vals[] = { 4, 2, 1, 4, 10, 13, 5, 6, 7 };
    ll_list *l = ll_from_array(vals, 9, sizeof(int));

    int expected_last = 13;

    ll_print_int(l);

    int klast = ll_node_get_int(ll_find_klast(l, 3));
    printf("Expected %d, found %d.\n", expected_last, klast);

    assert(expected_last == klast);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_find_klast();
}
#endif
