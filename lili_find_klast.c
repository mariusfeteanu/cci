#include <stdio.h>
#include "common/lili.h"

ll_node *ll_find_klast(ll_list list, int k){
    // TODO: this leaks the memory for this list
    ll_list *reversed = ll_empty();

    ll_node *node = list.head;
    while (node){
        ll_insert(reversed, node->key, node->key_size);
        node = node->next;
    }

    node = reversed->head;
    while ( k > 0 && node){
        k--;
        node = node->next;
    }

    return node;
}

#ifdef TEST_lili_find_klast
void test_ll_find_klast()
{
    printf("Checking duplicate removal (by value, integers, buffered).\n");

    int vals[] = { 4, 2, 1, 4, 10, 13, 5, 6, 7 };
    ll_list l = ll_from_array(vals, 9, sizeof(int));

    int expected_last = 13;

    ll_print_int(l);

    int klast = ll_node_get_int(*ll_find_klast(l, 3));
    printf("Expected %d, found %d.\n", expected_last, klast);

    assert(expected_last == klast);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_find_klast();
}
#endif
