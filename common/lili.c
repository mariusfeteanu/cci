#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lili.h"

ll_node *ll_insert(ll_node *node, int value){
    ll_node *new_node = malloc(sizeof(ll_node));
    new_node->next = node;
    new_node->value = value;
    return new_node;
}

ll_node *ll_remove(ll_node *node){
    ll_node *next = node->next;
    free(node);
    return next;
}

int  ll_eq(ll_node *left, ll_node *right){
    while(left && right){
        if(left->value != right->value){
            return 0;
        }
        left = left->next;
        right = right->next;
    }
    return !left && !right;
}

int ll_length(ll_node *node){
    int size = 0;
    while(node){
        size++;
        node = node->next;
    }
    return size;
}

void ll_destroy(ll_node *node){
    ll_node *next;
    while(node){
        next = node->next;
        free(node);
        node = next;
    }
}

ll_node *ll_search(ll_node *node, int value){
    while(node){
        if(node->value == value){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

int ll_get(ll_node *node, int index){
    while(node && index){
        index--;
        node = node->next;
    }
    return node->value;
}

void ll_print(ll_node *node){
    printf("{");
    while(node){
        printf("%d", node->value);
        node = node->next;
        if(node) printf(" -> ");
    }
    printf("}\n");
}

ll_node *ll_from_array(int array[], int size){
    ll_node *node = NULL;
    while(size){
        node = ll_insert(node, array[size-1]);
        size--;
    }
    return node;
}
