#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lili.h"

// manipulation
void ll_insert(ll_list * list, void *key, size_t key_size)
{
    ll_node *node = malloc(sizeof(ll_node));

    node->prev = NULL;
    node->next = list->head;
    node->key = key;
    node->key_size = key_size;

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
}

// search
ll_node *ll_search_key(ll_list list, void *key)
{
    ll_node *node = list.head;

    while (node) {
	if (node->key == key)
	    return node;
	node = node->next;
    }

    return NULL;
}

ll_node *ll_search_value(ll_list list, void *key, size_t key_size)
{
    ll_node *node = list.head;
    char *search_for = (char *) key;

    while (node) {
	// if we have the same pointer we are done here
	if (node->key == key)
	    return node;

	char *current = (char *) node->key;

	int i;
	for (i = 0; i < key_size; i++) {
	    if (search_for[i] != current[i])
		break;
	}

	if (i == key_size)
	    return node;

	node = node->next;
    }

    return NULL;
}

// inspect
unsigned int ll_length(ll_list list)
{
    int i = 0;
    ll_node *node = list.head;

    while (node) {
	i++;
	node = node->next;
    }
    return i;
}

void *ll_get(ll_list list, int index)
{
    ll_node *node = list.head;
    while (node && index > 0) {
	index--;
	node = node->next;
    }

    if (node) {
	return node->key;
    }
    return NULL;
}

// Equality tests
int ll_eq(ll_list left, ll_list right)
{
    return left.head == right.head;
}

int ll_eq_keys(ll_list left_list, ll_list right_list)
{
    ll_node *left = left_list.head;
    ll_node *right = right_list.head;

    if (left == right)
	return 1;		// should this be in the loop?

    while (left && right) {
	if ((left->key_size != right->key_size)
	    || (left->key != right->key)) {
	    return 0;
	}
	left = left->next;
	right = right->next;
    }

    return !(left || right);
}

int ll_eq_values(ll_list left_list, ll_list right_list)
{
    ll_node *left = left_list.head;
    ll_node *right = right_list.head;

    if (left == right)
	return 1;		// should this be in the loop?

    while (left && right) {
	if (left->key != right->key) {
	    if ((left->key_size != right->key_size))
		return 0;
	    char *left_value = (char *) left->key;
	    char *right_value = (char *) right->key;
	    int i = 0;
	    for (i = 0; i < left->key_size; i++) {
		if (left_value[i] != right_value[i]) {
		    return 0;
		}
	    }
	}
	left = left->next;
	right = right->next;
    }
    return !(left || right);
}

// Utility functions
void ll_print(ll_list list)
{
    ll_node *node = list.head;

    printf("Linked list: {");
    while (node) {
	printf("[key@%p (%zu bytes)]", node->key, node->key_size);
	if (node->next)
	    printf(" -> ");
	node = node->next;
    }
    printf("}\n");
}

ll_list ll_from_array(void *keys, unsigned int count, size_t key_size)
{
    assert(count > 0);
    ll_node *node;
    ll_node *prev = NULL;

    ll_node *list_buffer;
    list_buffer = malloc(count * sizeof(ll_node));

    for (int i = 0; i < count; i++) {
	node = list_buffer + i;
	node->prev = prev;
	node->next = NULL;
	node->key = (void *) ((char *) keys + i * key_size);
	node->key_size = key_size;

	if (prev)
	    prev->next = node;
	prev = node;
    }

    ll_list list = {
	.head = list_buffer,
	.tail = prev
    };

    return list;
}
