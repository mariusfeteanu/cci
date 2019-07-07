#include <stdio.h>
#include "common/lili.h"

void ll_dedup(ll_list * list)
{
    ll_node *node, *dup_runner;

    node = list->head;
    while (node) {
        dup_runner = node->next;
        while (dup_runner) {
            if (ll_node_eq(node, dup_runner)) {
                ll_node *skip = dup_runner->next;
                ll_remove(list, dup_runner);
                dup_runner = skip;
            } else {
                dup_runner = dup_runner->next;
            }
        }
        node = node->next;
    }
}

#ifdef TEST_lili_dedup
void test_ll_dedup()
{
    printf("Checking duplicate removal (by value, integers, buffered).\n");

    int vals[] = { 4, 2, 1, 4, 10, 13, 4, 1, 2 };
    ll_list l = ll_from_array(vals, 9, sizeof(int));

    int dedup_vals[] = { 4, 2, 1, 10, 13 };
    ll_list d = ll_from_array(dedup_vals, 5, sizeof(int));

    ll_print_int(l);
    printf("Expected list:\n");
    ll_print_int(d);

    ll_dedup(&l);
    printf("Result:\n");
    ll_print_int(l);

    assert(ll_eq(l, d));

    printf("Worked!\n");
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_dedup();
}
#endif
