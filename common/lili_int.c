#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lili.h"

// int operations
ll_node *ll_search_int(ll_list * list, int value)
{
    return ll_search(list, &value, sizeof(int));
}

void ll_insert_int(ll_list * list, int *value)
{
    ll_insert(list, (void *) value, sizeof(int));
}

int ll_node_get_int(ll_node * node)
{
    assert(node->key_size == sizeof(int));
    return *(int *) node->key;
}

int *ll_get_int(ll_list * list, int index)
{
    return ll_get(list, index);
}

void ll_print_int(ll_list * list)
{
    ll_node *node = list->head;

    printf("Linked list: {");
    while (node) {
        printf("[%d]", *(int *) node->key);
        if (node->next)
            printf(" -> ");
        node = node->next;
    }
    printf("}\n");
}
