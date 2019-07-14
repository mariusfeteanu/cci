#include <stdio.h>
#include <assert.h>
#include "common/lili.h"

int ll_is_palindrome(ll_list * list)
{
    ll_node *node = list->head;
    ll_list *rev_list = ll_empty();
    int length = 0;

    while (node) {
        ll_create_head_node_int(rev_list, ll_node_get_int(node));
        length++;
        node = node->next;
    }

    node = list->head;
    ll_node *rev_node = rev_list->head;
    length = length / 2 + length % 2;
    while (length > 0) {
        if (ll_node_get_int(node) != ll_node_get_int(rev_node)) {
            ll_destroy_all(rev_list);
            return 0;
        }
        length--;
        node = node->next;
        rev_node = rev_node->next;
    }

    ll_destroy_all(rev_list);

    return 1;
}

#ifdef TEST_lili_palindrome
void test_ll_is_palindrome(ll_list * list)
{
    printf("Checking that list is plaindrome:\n");
    ll_print_int(list);

    assert(ll_is_palindrome(list));
    ll_destroy(list);
}

void test_ll_is_not_palindrome(ll_list * list)
{
    printf("Checking that list is not plaindrome:\n");
    ll_print_int(list);

    assert(!ll_is_palindrome(list));
    ll_destroy(list);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_is_palindrome(ll_from_array
                          ((int[]) { 1, 2, 1 }, 3, sizeof(int)));
    test_ll_is_palindrome(ll_empty());
    test_ll_is_palindrome(ll_from_array
                          ((int[]) { 1, 2, 2, 1 }, 4, sizeof(int)));
    test_ll_is_palindrome(ll_from_array((int[]) { 1 }, 1, sizeof(int)));

    test_ll_is_not_palindrome(ll_from_array
                              ((int[]) { 1, 2, 2 }, 3, sizeof(int)));
    test_ll_is_not_palindrome(ll_from_array
                              ((int[]) { 2, 1 }, 2, sizeof(int)));
}
#endif
