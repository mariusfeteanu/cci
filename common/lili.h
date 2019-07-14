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

// manipulation
ll_list *ll_empty();
// value based
void ll_create_head_node(ll_list * list, void *key, size_t key_size);
void ll_create_tail_node(ll_list * list, void *key, size_t key_size);
void ll_destroy_node(ll_list * list, ll_node * node);
void ll_destroy_node_and_value(ll_list * list, ll_node * node);
void ll_destroy(ll_list * list);
void ll_destroy_all(ll_list * list);
// node based
void ll_insert_node(ll_list * list, ll_node * node);
void ll_remove_node(ll_list * list, ll_node * node);
// equality tests
int ll_node_eq_value(ll_node * node, char *value, int size);
int ll_node_eq(ll_node * left, ll_node * right);
int ll_eq(ll_list * left_list, ll_list * right_list);
// search
ll_node *ll_search(ll_list * list, void *value, int size);
// inspect
unsigned int ll_length(ll_list * list);
void *ll_get(ll_list * list, int index);
// utility functions
void ll_print(ll_list * list);
ll_list *ll_from_array(void *keys, unsigned int count, size_t key_size);


// int helper function
ll_node *ll_search_int(ll_list * list, int value);
void ll_create_head_node_int(ll_list * list, int value);
void ll_create_tail_node_int(ll_list * list, int value);
int ll_node_get_int(ll_node * node);
int *ll_get_int(ll_list * list, int index);
void ll_print_int(ll_list * list);
