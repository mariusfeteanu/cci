#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lili.h"

ll_node *ll_search_double(ll_list list, double value)
{
    return ll_search(list, &value, sizeof(double));
}

void ll_insert_double(ll_list * list, double *value)
{
    ll_insert(list, (void *) value, sizeof(double));
}

double ll_node_get_double(ll_node node)
{
    assert(node.key_size == sizeof(double));
    return *(double *) node.key;
}

double *ll_get_double(ll_list list, int index)
{
    return ll_get(list, index);
}

void ll_print_double(ll_list list)
{
    ll_node *node = list.head;

    printf("Linked list: {");
    while (node) {
        printf("[%.2f]", *(double *) node->key);
        if (node->next)
            printf(" -> ");
        node = node->next;
    }
    printf("}\n");
}
