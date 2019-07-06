#include <stdio.h>
#include "common/lili.h"

void ll_dedup_int_values_buffered(ll_list * list)
{
    unsigned int length = ll_length(*list);
    int *values = malloc(length * sizeof(int));
    int ii = 0;

    ll_node *node = list->head;
    while (node) {
	for (int jj = 0; jj < ii; jj++) {
	    // TODO: revisit this when I have a hash-map
	    if (values[jj] == ll_node_get_int(*node)) {
		ll_remove_node(list, node);
		break;
	    }
	}
	values[ii] = ll_node_get_int(*node);
	ii++;
	node = node->next;
    }
}

#ifdef TEST_lili_dedup
void test_ll_dedup()
{
    printf("Checking duplicate removal (by value, integers, buffered).\n");

    int vals[] = { 4, 2, 1, 4, 10, 13, 4, 1, 2 };
    ll_list l = ll_from_array(vals, 8, sizeof(int));

    int dedup_vals[] = { 4, 2, 1, 10, 13 };
    ll_list d = ll_from_array(dedup_vals, 5, sizeof(int));

    ll_print_int(l);
    printf("Expected list:\n");
    ll_print_int(d);

    ll_dedup_int_values_buffered(&l);
    printf("Result:\n");
    ll_print_int(l);

    assert(ll_eq_values(l, d));

    printf("Worked!\n");
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_dedup();
}
#endif
