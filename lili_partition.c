#include <stdio.h>
#include "common/lili.h"

void ll_partition(ll_list * list, int pv)
{
    ll_node *node = list->head;
    ll_list *p2 = ll_empty();

    while (node) {
        int nv = ll_node_get_int(node);
        ll_node *next = node->next;

        if (nv >= pv) {
            // cut from current list
           if(node->prev){
               node->prev->next = node->next;
           } else {
             list->head = node->next;
             p2->head = node;
             p2->tail = node;
           }
           if(node->next){
               node->next->prev = node->prev;
           } else {
             list->tail = node->prev;
           }
           // paste to other list
           node->prev = p2->tail;
           node->next = NULL;
           if(p2->tail){
             p2->tail->next = node;
           }

           // free(node);
            // paste to new list
            // This is simpler but slower
            // ll_insert(p2, node->key, node->key_size);
            // ll_remove(list, node);
        }
        node = next;
    }

    list->tail->next = p2->head;
    p2->head->prev = list->tail;
    list->tail = p2->tail;
}

#ifdef TEST_lili_partition
void test_ll_partition()
{
    int pv = 5;
    printf("Checking partition list by value = %d.\n", pv);

    int vals[] = { 3, 5, 8, 5, 10, 2, 1 };
    ll_list *l = ll_from_array(vals, 7, sizeof(int));
    int previous_length = ll_length(l);
    ll_print_int(l);

    ll_partition(l, pv);

    printf("After partition:\n");

    ll_print_int(l);

    ll_node *node = l->head;
    int found = 0;

    while (node) {
        int nv = ll_node_get_int(node);
        if (!found) {
            found = (nv >= pv);
        }

        if (found)
            assert(nv >= pv);
        if (!found)
            assert(nv < pv);

        node = node->next;
    }

    assert(previous_length == ll_length(l));
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_partition();
}
#endif
