#include <stdio.h>
#include <assert.h>
#include "common/lili.h"

int ll_is_palindrome(ll_node * head)
{
    ll_node *rev_node = NULL;
    ll_node *node = head;
    int length = 0;

    while (node) {
        rev_node = ll_insert(rev_node, node->value);
        length++;
        node = node->next;
    }

    node = head;
    length = length / 2 + length % 2;
    ll_node *rev_head = rev_node;
    while (length > 0) {
        if (node->value != rev_node->value) {
            ll_destroy(rev_head);
            return 0;
        }
        length--;
        node = node->next;
        rev_node = rev_node->next;
    }

    ll_destroy(rev_head);
    return 1;
}

#ifdef TEST_lili_palindrome
void test_ll_is_palindrome(ll_node * node)
{
    printf("Checking that list is plaindrome:\n");
    ll_print(node);

    assert(ll_is_palindrome(node));
    ll_destroy(node);
}

void test_ll_is_not_palindrome(ll_node * node)
{
    printf("Checking that list is not plaindrome:\n");
    ll_print(node);

    assert(!ll_is_palindrome(node));
    ll_destroy(node);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_is_palindrome(ll_from_array((int[]) { 1, 2, 1 }, 3));
    test_ll_is_palindrome(NULL);
    test_ll_is_palindrome(ll_from_array((int[]) { 1, 2, 2, 1 }, 4));
    test_ll_is_palindrome(ll_from_array((int[]) { 1 }, 1));

    test_ll_is_not_palindrome(ll_from_array((int[]) { 1, 2, 2 }, 3));
    test_ll_is_not_palindrome(ll_from_array((int[]) { 2, 1 }, 2));
}
#endif
