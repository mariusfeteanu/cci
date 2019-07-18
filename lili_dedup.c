#include <stdio.h>
#include "common/lili.h"

void ll_dedup(ll_node *node)
{
    ll_node *dup_runner;

    while (node) {
        dup_runner = node->next;
        while (dup_runner) {
            if (node->value == dup_runner->value) {
                ll_node *skip = dup_runner->next;
                dup_runner->value = skip->value;
                dup_runner->next = skip->next;
                free(skip);
                // TODO: handle case where duplicates is last element in list
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
    printf("Checking duplicate removal\n");

    int vals[] = { 4, 2, 1, 4, 10, 13, 4, 1, 2, 8 };
    ll_node *l = ll_from_array(vals, 10);

    int dedup_vals[] = { 4, 2, 1, 10, 13, 8 };
    ll_node *d = ll_from_array(dedup_vals, 6);

    ll_print(l);
    printf("Expected list:\n");
    ll_print(d);

    ll_dedup(l);
    printf("Result:\n");
    ll_print(l);

    assert(ll_eq(l, d));
    ll_destroy(l);
    ll_destroy(d);

    printf("Worked!\n");
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_dedup();
}
#endif
