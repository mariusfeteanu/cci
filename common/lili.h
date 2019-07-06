#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ll_node_s ll_node;
struct ll_node_s {
    ll_node *prev;
    ll_node *next;
    void *key;
    size_t key_size;
};

typedef struct ll_list_s {
    ll_node *head;
    ll_node *tail;
} ll_list;

ll_list ll_from_array(void *keys, unsigned int count, size_t key_size);

void ll_insert(ll_list * list, void *key, size_t key_size);

ll_node *ll_search_key(ll_list list, void *key);

ll_node *ll_search_value(ll_list list, void *key, size_t key_size);

void ll_remove_node(ll_list * list, ll_node * node);

int ll_eq(ll_list left, ll_list right);

int ll_eq_keys(ll_list left_list, ll_list right_list);

int ll_eq_values(ll_list left_list, ll_list right_list);

unsigned int ll_length(ll_list list);

void *ll_get(ll_list list, int index);

void ll_print(ll_list list);

// int operations
ll_node *ll_search_value_int(ll_list list, int value);

void ll_insert_int(ll_list * list, int *value);

int ll_node_get_int(ll_node node);

int *ll_get_int(ll_list list, int index);

void ll_print_int(ll_list list);

// double operations
ll_node *ll_search_value_double(ll_list list, double value);

void ll_insert_double(ll_list * list, double *value);

double ll_node_get_double(ll_node node);

double *ll_get_double(ll_list list, int index);

void ll_print_double(ll_list list);
