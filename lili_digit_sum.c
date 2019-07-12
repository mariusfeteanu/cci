#include <stdio.h>
#include "common/lili.h"

ll_list *ll_digit_sum(ll_list * x, ll_list * y)
{
    ll_list *sum = ll_empty();
    int carry = 0;

    ll_node *xn = x->head, *yn = y->head;

    while (xn || yn) {
        int current_sum = carry;
        if (xn) {
            current_sum += ll_node_get_int(xn);
            xn = xn->next;
        }
        if (yn) {
            current_sum += ll_node_get_int(yn);
            yn = yn->next;
        }

        // this cheats by inserting at the end
        // but you can easily do this on a sinle linked list
        ll_create_tail_node_int(sum, current_sum % 10);
        carry = current_sum / 10;
    }

    if (carry) {
        // ditto
        ll_create_tail_node_int(sum, carry);
    }

    return sum;
}

ll_list *ll_digit_rev_sum(ll_list * x, ll_list * y)
{
    ll_list *simple_sum = ll_empty();

    int xl = ll_length(x);
    int yl = ll_length(y);

    ll_list *ll, *sl;
    int excess;
    if (xl >= yl) {
        ll = x;
        sl = y;
        excess = xl - yl;
    } else {
        sl = x;
        ll = y;
        excess = yl - xl;
    }

    ll_node *lnode = ll->head;
    while (excess) {
        ll_create_head_node_int(simple_sum, ll_node_get_int(lnode));
        lnode = lnode->next;
        excess--;
    }

    ll_node *snode = sl->head;
    while (snode) {
        int s = ll_node_get_int(snode) + ll_node_get_int(lnode);
        ll_create_head_node_int(simple_sum, s);
        lnode = lnode->next;
        snode = snode->next;
    }

    // some space in case the lists are the same size but they sum longer
    ll_create_tail_node_int(simple_sum, 0);

    ll_node *node = simple_sum->head;
    ll_list *sum = ll_empty();
    int carry = 0;
    while (node) {
        int s = carry + ll_node_get_int(node);
        carry = s / 10;
        ll_create_head_node_int(sum, s % 10);
        node = node->next;
    }

    if (ll_node_get_int(sum->head) == 0) {
        ll_destroy_node(sum, sum->head);
    }

    return sum;
}

#ifdef TEST_lili_digit_sum
void test_ll_digit_sum(ll_list * x, ll_list * y, ll_list * expected_sum)
{
    ll_list *sum = ll_digit_sum(x, y);
    printf("Checking if the sum of:\n");
    ll_print_int(x);
    printf("And:\n");
    ll_print_int(y);
    printf("Is:\n");
    ll_print_int(expected_sum);
    printf("Calculated result:\n");
    ll_print_int(sum);
    assert(ll_eq(sum, expected_sum));
    printf("Looks good!\n");
}

void test_ll_digit_rev_sum(ll_list * x, ll_list * y,
                           ll_list * expected_sum)
{
    ll_list *sum = ll_digit_rev_sum(x, y);
    printf("Reverse: Checking if the sum of:\n");
    ll_print_int(x);
    printf("And:\n");
    ll_print_int(y);
    printf("Is:\n");
    ll_print_int(expected_sum);
    printf("Calculated result:\n");
    ll_print_int(sum);
    assert(ll_eq(sum, expected_sum));
    printf("Looks good!\n");
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_digit_sum(ll_from_array((int[]) { 7, 1, 6 }, 3, sizeof(int)),
                      ll_from_array((int[]) { 5, 9, 2, 1 }, 4,
                                    sizeof(int)),
                      ll_from_array((int[]) { 2, 1, 9, 1 }, 4, sizeof(int))
        );

    test_ll_digit_sum(ll_from_array((int[]) { 7, 1, 6 }, 3, sizeof(int)),
                      ll_from_array((int[]) { 5, 9, 6 }, 3, sizeof(int)),
                      ll_from_array((int[]) { 2, 1, 3, 1 }, 4, sizeof(int))
        );

    test_ll_digit_sum(ll_from_array((int[]) { 7, 1, 6 }, 3, sizeof(int)),
                      ll_from_array((int[]) { 5, 9, 2 }, 3, sizeof(int)),
                      ll_from_array((int[]) { 2, 1, 9 }, 3, sizeof(int))
        );

    test_ll_digit_sum(ll_from_array((int[]) { 4 }, 1, sizeof(int)),
                      ll_from_array((int[]) { 5 }, 1, sizeof(int)),
                      ll_from_array((int[]) { 9 }, 1, sizeof(int))
        );

    test_ll_digit_sum(ll_empty(),
                      ll_from_array((int[]) { 1 }, 1, sizeof(int)),
                      ll_from_array((int[]) { 1 }, 1, sizeof(int))
        );

    test_ll_digit_sum(ll_empty(), ll_empty(), ll_empty()
        );

    // reverse sum functions

    test_ll_digit_rev_sum(ll_from_array
                          ((int[]) { 6, 1, 7 }, 3, sizeof(int)),
                          ll_from_array((int[]) { 1, 2, 9, 5 }, 4,
                                        sizeof(int)),
                          ll_from_array((int[]) { 1, 9, 1, 2 }, 4,
                                        sizeof(int))
        );

    test_ll_digit_rev_sum(ll_from_array
                          ((int[]) { 6, 1, 7 }, 3, sizeof(int)),
                          ll_from_array((int[]) { 6, 9, 5 }, 3,
                                        sizeof(int)),
                          ll_from_array((int[]) { 1, 3, 1, 2 }, 4,
                                        sizeof(int))
        );

    test_ll_digit_rev_sum(ll_from_array
                          ((int[]) { 6, 1, 7 }, 3, sizeof(int)),
                          ll_from_array((int[]) { 2, 9, 5 }, 3,
                                        sizeof(int)),
                          ll_from_array((int[]) { 9, 1, 2 }, 3,
                                        sizeof(int))
        );

    test_ll_digit_rev_sum(ll_from_array((int[]) { 4 }, 1, sizeof(int)),
                          ll_from_array((int[]) { 5 }, 1, sizeof(int)),
                          ll_from_array((int[]) { 9 }, 1, sizeof(int))
        );

    test_ll_digit_rev_sum(ll_empty(),
                          ll_from_array((int[]) { 1 }, 1, sizeof(int)),
                          ll_from_array((int[]) { 1 }, 1, sizeof(int))
        );

    test_ll_digit_rev_sum(ll_empty(), ll_empty(), ll_empty()
        );
}
#endif
