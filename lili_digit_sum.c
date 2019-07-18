#include <stdio.h>
#include "common/lili.h"

ll_node *ll_digit_sum(ll_node * x, ll_node * y)
{
    ll_node *sum = NULL;
    int carry = 0;

    while (x || y) {
        int current_sum = carry;
        if (x) {
            current_sum += x->value;
            x = x->next;
        }
        if (y) {
            current_sum += y->value;
            y = y->next;
        }
        sum = ll_insert(sum, current_sum % 10);
        carry = current_sum / 10;
    }

    if (carry) {
        sum = ll_insert(sum, carry);
    }

    ll_node *rev_sum = NULL;
    ll_node *sum_head = sum;

    while(sum){
        rev_sum = ll_insert(rev_sum, sum->value);
        sum = sum->next;
    }
    ll_destroy(sum_head);
    return rev_sum;
}

//ll_node *ll_digit_rev_sum(ll_node * x, ll_node * y)
//{
//    ll_node *simple_sum = NULL;
//
//    int xl = ll_length(x);
//    int yl = ll_length(y);
//
//    ll_node *ll, *sl;
//    int excess;
//    if (xl >= yl) {
//        ll = x;
//        sl = y;
//        excess = xl - yl;
//    } else {
//        sl = x;
//        ll = y;
//        excess = yl - xl;
//    }
//
//    ll_node *lnode = ll->head;
//    while (excess) {
//        ll_create_head_node_int(simple_sum, ll_node_get_int(lnode));
//        lnode = lnode->next;
//        excess--;
//    }
//
//    ll_node *snode = sl->head;
//    while (snode) {
//        int s = ll_node_get_int(snode) + ll_node_get_int(lnode);
//        ll_create_head_node_int(simple_sum, s);
//        lnode = lnode->next;
//        snode = snode->next;
//    }
//
//    // some space in case the lists are the same size but they sum longer
//    ll_create_tail_node_int(simple_sum, 0);
//
//    ll_node *node = simple_sum->head;
//    ll_node *sum = NULL;
//    int carry = 0;
//    while (node) {
//        int s = carry + ll_node_get_int(node);
//        carry = s / 10;
//        ll_create_head_node_int(sum, s % 10);
//        node = node->next;
//    }
//
//    if (ll_node_get_int(sum->head) == 0) {
//        ll_destroy_node_and_value(sum, sum->head);
//    }
//
//    ll_destroy_all(simple_sum);
//    return sum;
//}

#ifdef TEST_lili_digit_sum
void test_ll_digit_sum(ll_node * x, ll_node * y, ll_node * expected_sum)
{
    ll_node *sum = ll_digit_sum(x, y);
    printf("Checking if the sum of:\n");
    ll_print(x);
    printf("And:\n");
    ll_print(y);
    printf("Is:\n");
    ll_print(expected_sum);
    printf("Calculated result:\n");
    ll_print(sum);
    assert(ll_eq(sum, expected_sum));
    printf("Looks good!\n");

    ll_destroy(sum);
    // freeing these as I know they don't get re-used
    ll_destroy(x);
    ll_destroy(y);
    ll_destroy(expected_sum);
}

//void test_ll_digit_rev_sum(ll_node * x, ll_node * y,
//                           ll_node * expected_sum)
//{
//    ll_node *sum = ll_digit_rev_sum(x, y);
//    printf("Reverse: Checking if the sum of:\n");
//    ll_print(x);
//    printf("And:\n");
//    ll_print(y);
//    printf("Is:\n");
//    ll_print(expected_sum);
//    printf("Calculated result:\n");
//    ll_print(sum);
//    assert(ll_eq(sum, expected_sum));
//    printf("Looks good!\n");
//
//    ll_destroy_all(sum);
//    // freeing these as ␜I know they don't get re-used
//    ll_destroy(x);
//    ll_destroy(y);
//    ll_destroy(expected_sum);
//}

int main()
{
    setbuf(stdout, NULL);

    test_ll_digit_sum(ll_from_array((int[]) { 7, 1, 6 }, 3),
                      ll_from_array((int[]) { 5, 9, 2, 1 }, 4),
                      ll_from_array((int[]) { 2, 1, 9, 1 }, 4)
        );

    test_ll_digit_sum(ll_from_array((int[]) { 7, 1, 6 }, 3),
                      ll_from_array((int[]) { 5, 9, 6 }, 3),
                      ll_from_array((int[]) { 2, 1, 3, 1 }, 4)
        );

    test_ll_digit_sum(ll_from_array((int[]) { 7, 1, 6 }, 3),
                      ll_from_array((int[]) { 5, 9, 2 }, 3),
                      ll_from_array((int[]) { 2, 1, 9 }, 3)
        );

    test_ll_digit_sum(ll_from_array((int[]) { 4 }, 1),
                      ll_from_array((int[]) { 5 }, 1),
                      ll_from_array((int[]) { 9 }, 1)
        );

    test_ll_digit_sum(NULL,
                      ll_from_array((int[]) { 1 }, 1),
                      ll_from_array((int[]) { 1 }, 1)
        );

    test_ll_digit_sum(NULL, NULL, NULL
        );

    // reverse sum functions

//    test_ll_digit_rev_sum(ll_from_array
//                          ((int[]) { 6, 1, 7 }, 3),
//                          ll_from_array((int[]) { 1, 2, 9, 5 }, 4,
//                                        sizeof(int)),
//                          ll_from_array((int[]) { 1, 9, 1, 2 }, 4,
//                                        sizeof(int))
//        );
//
//    test_ll_digit_rev_sum(ll_from_array
//                          ((int[]) { 6, 1, 7 }, 3),
//                          ll_from_array((int[]) { 6, 9, 5 }, 3,
//                                        sizeof(int)),
//                          ll_from_array((int[]) { 1, 3, 1, 2 }, 4,
//                                        sizeof(int))
//        );
//
//    test_ll_digit_rev_sum(ll_from_array
//                          ((int[]) { 6, 1, 7 }, 3),
//                          ll_from_array((int[]) { 2, 9, 5 }, 3,
//                                        sizeof(int)),
//                          ll_from_array((int[]) { 9, 1, 2 }, 3,
//                                        sizeof(int))
//        );
//
//    test_ll_digit_rev_sum(ll_from_array((int[]) { 4 }, 1),
//                          ll_from_array((int[]) { 5 }, 1),
//                          ll_from_array((int[]) { 9 }, 1)
//        );
//
//    test_ll_digit_rev_sum(NULL,
//                          ll_from_array((int[]) { 1 }, 1),
//                          ll_from_array((int[]) { 1 }, 1)
//        );
//
//    test_ll_digit_rev_sum(NULL, NULL, NULL
//        );
}
#endif
