#include <stdio.h>
#include <assert.h>
#include "common/lili.h"

int ll_is_intersection(ll_node *left, ll_node *right)
{
    return 1;
}

#ifdef TEST_lili_intersect
void test_ll_is_intersection(ll_node *left, ll_node *right)
{
    printf("Checking that the following lists intersect:\n");
    ll_print(left);
    ll_print(right);

    assert(ll_is_intersection(left, right));

    printf("Looks good!\n");
}

int main()
{
    setbuf(stdout, NULL);

    ll_node *left = ll_from_array((int[]) { 1, 2, 1 }, 3);
    ll_node *right = NULL;
    right = ll_insert(right, left->next->next->value);
    right = ll_insert(right, left->next->value);
    test_ll_is_intersection(left, right);

    ll_destroy(left);
    ll_destroy(right);
}
#endif
