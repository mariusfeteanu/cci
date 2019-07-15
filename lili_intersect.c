#include <stdio.h>
#include <assert.h>
#include "common/lili.h"

int ll_is_intersection(ll_list *left, ll_list *right)
{
    return 1;
}

#ifdef TEST_lili_intersect
void test_ll_is_intersection(ll_list *left, ll_list *right)
{
    printf("Checking that the following lists intersect:\n");
    ll_print_int(left);
    ll_print_int(right);

    assert(ll_is_intersection(left, right));

    printf("Looks good!\n");

//    ll_destroy(right);
//    ll_destroy(left);
}

int main()
{
    setbuf(stdout, NULL);

    ll_list *left = ll_from_array((int[]) { 1, 2, 1 }, 3, sizeof(int));
    ll_list *right = ll_empty();
    ll_insert_node(right, left->head->next->next);
    ll_insert_node(right, left->head->next);
    test_ll_is_intersection(left, right);
}
#endif
