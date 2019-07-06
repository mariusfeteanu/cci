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

ll_list ll_from_array(void *keys, unsigned int count, size_t key_size){
    assert(count > 0);
    ll_node *node;
    ll_node *prev = NULL;

    ll_node *list_buffer;
    list_buffer = malloc(count * sizeof(ll_node));

    for(int i = 0; i < count; i++){
        node = list_buffer + i;
        node->prev = prev;
        node->next = NULL;
        node->key = (void *)((char *)keys + i*key_size);
        node->key_size = key_size;

        if(prev) prev->next = node;
        prev = node;
    }

    ll_list list = {
        .head = list_buffer,
        .tail = prev
    };

    return list;
}

void ll_insert(ll_list *list, void *key, size_t key_size){
    ll_node *node = malloc(sizeof(ll_node));

    node->prev = NULL;
    node->next = list->head;
    node->key = key;
    node->key_size = key_size;

    list->head->prev = node;
    list->head = node;
}

void ll_insert_int(ll_list *list, int *key){
    ll_insert(list, (void *)key, sizeof(int));
}

int ll_node_get_int(ll_node node){
    assert(node.key_size == sizeof(int));
    return *(int *)node.key;
}

ll_node *ll_search(ll_list list, void *key, size_t key_size){
    ll_node *node = list.head;
    char *search_for = (char *)key;

    while(node->next){
        char *current = (char *)node->key;

        int i;
        for(i=0; i<key_size; i++){
            if(search_for[i] != current[i]) break;
        }

        if(i == key_size) return node;

        node = node->next;
    }

    return NULL;
}

ll_node *ll_search_int(ll_list list, int key){
    return ll_search(list, &key, sizeof(int));
}

#ifdef TEST_lili
void test_lili_int_from_array(){
    int vals[] = {4, 7, 6, 5};
    ll_list l = ll_from_array(vals, 4, sizeof(int));

    printf("Checking linked list creation from array of ints.\n");

    assert(ll_node_get_int(*l.head) == 4);
    assert(ll_node_get_int(*l.head->next) == 7);
    assert(ll_node_get_int(*l.head->next->next) == 6);
    assert(ll_node_get_int(*l.head->next->next->next) == 5);
}

void test_lili_search_int(){
    int vals[] = {4, 7, 6, 5};
    ll_list l = ll_from_array(vals, 4, sizeof(int));

    printf("Searching for a value in a list of ints.\n");

    ll_node *found = ll_search_int(l, 6);

    assert(ll_node_get_int(*found) == 6);
}

void test_lili_int_insert(){
    int vals[] = {7, 6, 5};
    ll_list l = ll_from_array(vals, 3, sizeof(int));

    printf("Checking insertion into linked list of ints.\n");

    assert(ll_node_get_int(*l.head) == 7);
    assert(ll_node_get_int(*l.head->next) == 6);
    assert(ll_node_get_int(*l.head->next->next) == 5);
    assert(!(*(l.head->next->next)).next);

    int n = 4;
    ll_insert_int(&l, &n);

    assert(ll_node_get_int(*l.head) == 4);
    assert(ll_node_get_int(*l.head->next) == 7);
    assert(ll_node_get_int(*l.head->next->next) == 6);
    assert(ll_node_get_int(*l.head->next->next->next) == 5);
}

int main(){
    setbuf(stdout, NULL);

    test_lili_int_from_array();
    test_lili_search_int();
    test_lili_int_insert();
}
#endif
