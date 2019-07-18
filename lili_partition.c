#include <stdio.h>
#include <assert.h>
#include "common/lili.h"

ll_node *ll_partition(ll_node *node, int pv)
{
    ll_node *second_part = NULL, *prev = NULL, *first_part = NULL;

    while (node) {
        int nv = node->value;
        ll_node *next = node->next;

        if (nv >= pv) {
            second_part = ll_insert(second_part, nv);
            if(prev) prev->next = ll_remove(node);
        } else {
            if(!first_part){
                first_part = node;
            }
            prev = node;
        }
        node = next;
    }

    if(first_part){
        prev->next = second_part;
    } else {
        first_part = second_part;
    }
    return first_part;
}

#ifdef TEST_lili_partition
void test_ll_partition()
{
    int pv = 5;
    printf("Checking partition list by value = %d.\n", pv);

    int vals[] = { 3, 5, 8, 5, 10, 2, 1 };
    ll_node *l = ll_from_array(vals, 7);
    int previous_length = ll_length(l);
    ll_print(l);

    l = ll_partition(l, pv);

    printf("After partition:\n");

    ll_print(l);

    ll_node *node = l;
    int found = 0;

    while (node) {
        int nv = node->value;
        if (!found) {
            found = (nv >= pv);
        }

        if (found)
            assert(nv >= pv);
        if (!found)
            assert(nv < pv);

        node = node->next;
    }

    assert(previous_length == ll_length(l));

    ll_destroy(l);
}

void test_ll_partition_0()
{
    int pv = 1;
    printf("Checking partition list by value = %d.\n", pv);

    int vals[] = { 3, 5, 8, 5, 10, 2, 1 };
    ll_node *l = ll_from_array(vals, 7);
    int previous_length = ll_length(l);
    ll_print(l);

    ll_node *pl = ll_partition(l, pv);

    printf("After partition:\n");

    ll_print(pl);

    ll_node *node = pl;
    int found = 0;

    while (node) {
        int nv = node->value;
        if (!found) {
            found = (nv >= pv);
        }

        if (found)
            assert(nv >= pv);

        node = node->next;
    }

    assert(previous_length == ll_length(pl));

    ll_destroy(l);
    ll_destroy(pl);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_partition();
    test_ll_partition_0();
}
#endif
