#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ll_node_s ll_node;
struct ll_node_s {
    ll_node *next;
    int value;
};

ll_node *ll_insert(ll_node * node, int value);

ll_node *ll_remove(ll_node * node);

int ll_eq(ll_node * left_node, ll_node * right_node);

int ll_length(ll_node * node);

void ll_destroy(ll_node * node);

ll_node *ll_search(ll_node * node, int value);

int ll_get(ll_node * node, int index);

void ll_print(ll_node * node);

ll_node *ll_from_array(int array[], int size);
