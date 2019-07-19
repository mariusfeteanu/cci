#include <stdio.h>
#include <assert.h>
#include "common/lili.h"

ll_node *ll_intersection(ll_node * left, ll_node * right)
{
    // make sure the left lift is longer
    int left_length = ll_length(left);
    int right_length = ll_length(right);

    if (left_length < right_length) {
        ll_node *longer = right;
        right = left;
        left = longer;
        int long_length = right_length;
        right_length = left_length;
        left_length = long_length;
    }

    int diff = left_length - right_length;

    while (diff) {
        left = left->next;
        diff--;
    }

    ll_node *intersect = NULL;

    while (right_length) {
        if (left == right && !intersect) {
            intersect = left;
        }
        left = left->next;
        right = right->next;
        right_length--;
    }

    return intersect;
}

#ifdef TEST_lili_intersect
void test_ll_is_intersection(ll_node * left,
                             ll_node * right,
                             ll_node * intersect)
{
    printf("Checking that the following lists intersect:\n");
    ll_print(left);
    ll_print(right);

    assert(ll_intersection(left, right) == intersect);

    printf("Looks good!\n");

    ll_node *next;

    while(left != intersect){
        next = left->next;
        free(left);
        left = next;
    }
    while(right != intersect){
        next = right->next;
        free(right);
        right = next;
    }
    ll_destroy(intersect);
}

void test_ll_is_not_intersection(ll_node * left, ll_node * right)
{
    printf("Checking that the following lists do not intersect:\n");
    ll_print(left);
    ll_print(right);

    assert(ll_intersection(left, right) == NULL);

    printf("Looks good!\n");

    ll_destroy(left);
    ll_destroy(right);
}

int main()
{
    setbuf(stdout, NULL);

    ll_node *left = ll_from_array((int[]) { 1, 2, 1, 4 }, 4);
    ll_node *right = left->next->next;
    right = ll_insert(right, 8);
    test_ll_is_intersection(left, right, left->next->next);

    left = ll_from_array((int[]) { 1, 2, 1, 4 }, 4);
    right = left->next->next;
    right = ll_insert(right, 8);
    right = ll_insert(right, 9);
    right = ll_insert(right, 7);
    test_ll_is_intersection(left, right, left->next->next);

    left = ll_from_array((int[]) { 1, 2, 1, 4 }, 4);
    right = ll_from_array((int[]) { 8, 1, 4 }, 3);
    test_ll_is_not_intersection(left, right);
}
#endif
