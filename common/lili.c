#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lili.h"

// manipulation
ll_list *ll_empty()
{
    return calloc(1, sizeof(ll_node));
}

void ll_create_head_node(ll_list * list, void *key, size_t key_size)
{
    ll_node *node = malloc(sizeof(ll_node));

    node->prev = NULL;
    node->next = list->head;
    node->key = key;
    node->key_size = key_size;

    if (list->head)
        list->head->prev = node;
    list->head = node;
    if (!list->tail)
      list->tail = node;
}

void ll_create_tail_node(ll_list * list, void *key, size_t key_size)
{
    ll_node *node = malloc(sizeof(ll_node));

    node->next = NULL;
    node->prev = list->tail;
    node->key = key;
    node->key_size = key_size;

    if (list->tail)
        list->tail->next = node;
    list->tail = node;
    if (!list->head)
      list->head = node;
}

void ll_destroy_node(ll_list * list, ll_node * node)
{
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    free(node);
}

void ll_insert_node(ll_list * list, ll_node *node)
{
    node->prev = NULL; // not necessary if node is clean, but still...
    node->next = list->head;

    if (list->head)
        list->head->prev = node;
    list->head = node;
}

void ll_remove_node(ll_list * list, ll_node * node)
{
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    node->next = NULL;
    node->prev = NULL;
}

// Equality tests
int ll_node_eq_value(ll_node * node, char *value, int size)
{
    char *node_value = (char *) node->key;

    if (!node)
        return 0;

    for (int i = 0; i < size; i++) {
        if (node_value[i] != value[i]) {
            return 0;
        }
    }
    return 1;
}

int ll_node_eq(ll_node * left, ll_node * right)
{
    if (left == right)
        return 1;
    if (left->key_size != right->key_size)
        return 0;
    if (left->key == right->key)
        return 1;

    // past the next check they are both not null
    // if one was null, then other would also be
    // and we would have returned on the first line
    if ((left && !right) || (!left && right))
        return 0;

    char *right_value = (char *) right->key;
    return ll_node_eq_value(left, right_value, right->key_size);
}

int ll_eq(ll_list * left_list, ll_list * right_list)
{
    ll_node *left = left_list->head;
    ll_node *right = right_list->head;

    while (left && right) {
        if (!ll_node_eq(left, right))
            return 0;
        left = left->next;
        right = right->next;
    }
    return !(left || right);
}

// search
ll_node *ll_search(ll_list * list, void *value, int size)
{
    ll_node *node = list->head;

    while (node) {
        if (ll_node_eq_value(node, (char *) value, size))
            return node;
        node = node->next;
    }
    return NULL;
}


// inspect
unsigned int ll_length(ll_list * list)
{
    int i = 0;
    ll_node *node = list->head;

    while (node) {
        i++;
        node = node->next;
    }
    return i;
}

void *ll_get(ll_list * list, int index)
{
    ll_node *node = list->head;
    while (node && index > 0) {
        index--;
        node = node->next;
    }

    if (node) {
        return node->key;
    }
    return NULL;
}

// Utility functions
void ll_print(ll_list * list)
{
    ll_node *node = list->head;

    printf("Linked list: {");
    while (node) {
        printf("[key@%p (%zu bytes)]", node->key, node->key_size);
        if (node->next)
            printf(" -> ");
        node = node->next;
    }
    printf("}\n");
}

ll_list *ll_from_array(void *keys, unsigned int count, size_t key_size)
{
    assert(count > 0);
    ll_node *node;
    ll_node *prev = NULL;
    ll_node *first = NULL;

    for (int i = 0; i < count; i++) {
        node = malloc(sizeof(ll_node));
        node->prev = prev;
        node->next = NULL;
        node->key = (void *) ((char *) keys + i * key_size);
        node->key_size = key_size;

        if (prev)
            prev->next = node;
        if (i == 0)
            first = node;
        prev = node;
    }

    ll_list *list = malloc(sizeof(ll_list));
    list->head = first;
    list->tail = prev;

    return list;
}
