#include <stdio.h>
#include <assert.h>
#include "common/lili.h"

ll_node *ll_loop(ll_node * node)
{
    ll_node *fast = node, *slow = node;

    if (fast)
        fast = fast->next;
    if (fast)
        fast = fast->next;
    if (slow)
        slow = slow->next;

    while (slow != fast && slow && fast) {
        slow = slow->next;
        fast = fast->next;
        if (fast)
            fast = fast->next;
    }

    // A comment about why this works
    ll_node *head = node;
    while (slow != head) {
        slow = slow->next;
        head = head->next;
    }

    return slow;
}

#ifdef TEST_lili_loop
void test_ll_is_loop(ll_node * node, ll_node * loop)
{
    printf("Checking that some list has a loop.\n");

    assert(ll_loop(node) == loop);

    printf("Looks good!\n");
}

void free_loop(ll_node * node, ll_node * loop)
{
    while (node) {
        ll_node *next = node->next;
        if (node != loop) {
            free(node);
        } else {
            node->next = NULL;
        }
        node = next;
    }
    free(loop);
}

int main()
{
    setbuf(stdout, NULL);

    ll_node *l = ll_from_array((int[]) { 1, 2, 3, 4, 5 }, 5);
    l->next->next->next->next->next = l->next->next;
    test_ll_is_loop(l, l->next->next);

    free_loop(l, l->next->next);

    l = ll_from_array((int[]) { 1, 2, 3, 4, 5, 6 }, 6);
    l->next->next->next->next->next->next = l->next->next;
    test_ll_is_loop(l, l->next->next);

    free_loop(l, l->next->next);
}
#endif
