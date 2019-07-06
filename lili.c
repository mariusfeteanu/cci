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

// int operations
ll_node *ll_search_value_int(ll_list list, int value)
{
    return ll_search_value(list, &value, sizeof(int));
}

void ll_insert_int(ll_list * list, int *value)
{
    ll_insert(list, (void *) value, sizeof(int));
}

int ll_node_get_int(ll_node node)
{
    assert(node.key_size == sizeof(int));
    return *(int *) node.key;
}

void ll_print_int(ll_list list)
{
    ll_node *node = list.head;

    printf("Linked list: {");
    while (node) {
	printf("[%d]", *(int *) node->key);
	if (node->next)
	    printf(" -> ");
	node = node->next;
    }
    printf("}\n");
}

// double operations
ll_node *ll_search_value_double(ll_list list, double value)
{
    return ll_search_value(list, &value, sizeof(double));
}

void ll_insert_double(ll_list * list, double *value)
{
    ll_insert(list, (void *) value, sizeof(double));
}

int ll_node_get_double(ll_node node)
{
    assert(node.key_size == sizeof(double));
    return *(double *) node.key;
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

// string operations
//ll_node *ll_search_value_string(ll_list list, char *key){
//    return ll_search_value(list, &key, sizeof(int));
//}
//
//void ll_insert_int(ll_list *list, int *key){
//    ll_insert(list, (void *)key, sizeof(int));
//}
//
//int ll_node_get_int(ll_node node){
//    assert(node.key_size == sizeof(int));
//    return *(int *)node.key;
//}
//
//void ll_print_int(ll_list list){
//    ll_node *node = list.head;
//
//    printf("Linked list: {");
//    while(node){
//        printf("[%d]", *(int *)node->key);
//        if(node->next) printf(" -> ");
//        node = node->next;
//    }
//    printf("}\n");
//}

#ifdef TEST_lili
// untyped operations (tested with ints)
void test_ll_eq()
{
    int vals[] = { 4, 7, 6, 5 };
    ll_list l = ll_from_array(vals, 4, sizeof(int));

    assert(ll_eq(l, l));
}

void test_ll_remove_node()
{
    int vals[] = { 4, 7, 6, 5 };
    ll_list l = ll_from_array(vals, 4, sizeof(int));

    int expected_vals[] = { 4, 7, 5 };
    ll_list e = ll_from_array(expected_vals, 3, sizeof(int));

    printf("Checking removing nodes from list:\n");
    ll_print_int(l);
    printf("Expecting:\n");
    ll_print_int(e);

    ll_remove_node(&l, l.head->next->next);
    printf("Result:\n");
    ll_print_int(l);

    assert(ll_eq_values(l, e));
}

void test_ll_search_key()
{
    int vals[] = { 4, 7, 6, 5 };
    ll_list l = ll_from_array(vals, 4, sizeof(int));

    printf("Checking finding a key reference in a list.\n");
    ll_node *node = ll_search_key(l, vals + 1);

    assert(ll_node_get_int(*node) == 7);
}

// ***** int tests ******
void test_ll_int_from_array()
{
    int vals[] = { 4, 7, 6, 5 };
    ll_list l = ll_from_array(vals, 4, sizeof(int));

    printf("Checking linked list creation from array of ints.\n");
    ll_print_int(l);

    assert(ll_node_get_int(*l.head) == 4);
    assert(ll_node_get_int(*l.head->next) == 7);
    assert(ll_node_get_int(*l.head->next->next) == 6);
    assert(ll_node_get_int(*l.head->next->next->next) == 5);
}

void test_ll_search_int()
{
    int vals[] = { 4, 7, 6, 5 };
    ll_list l = ll_from_array(vals, 4, sizeof(int));

    printf("Searching for a value in a list of ints.\n");
    ll_print_int(l);

    ll_node *found = ll_search_value_int(l, 6);

    assert(ll_node_get_int(*found) == 6);
}

void test_ll_int_insert()
{
    int vals[] = { 7, 6, 5 };
    ll_list l = ll_from_array(vals, 3, sizeof(int));

    printf("Checking insertion into linked list of ints.\n");

    assert(ll_node_get_int(*l.head) == 7);
    assert(ll_node_get_int(*l.head->next) == 6);
    assert(ll_node_get_int(*l.head->next->next) == 5);
    assert(!(*(l.head->next->next)).next);
    ll_print_int(l);

    int n = 4.0;
    ll_insert_int(&l, &n);
    ll_print_int(l);

    assert(ll_node_get_int(*l.head) == 4);
    assert(ll_node_get_int(*l.head->next) == 7);
    assert(ll_node_get_int(*l.head->next->next) == 6);
    assert(ll_node_get_int(*l.head->next->next->next) == 5);
}

// ***** double tests *****
void test_ll_double_from_array()
{
    double vals[] = { 4.0, 7.0, 6.0, 5.0 };
    ll_list l = ll_from_array(vals, 4.0, sizeof(double));

    printf("Checking linked list creation from array of doubles.\n");
    ll_print_double(l);

    assert(ll_node_get_double(*l.head) == 4.0);
    assert(ll_node_get_double(*l.head->next) == 7.0);
    assert(ll_node_get_double(*l.head->next->next) == 6.0);
    assert(ll_node_get_double(*l.head->next->next->next) == 5.0);
}

void test_ll_search_double()
{
    double vals[] = { 4.0, 7.0, 6.0, 5.0 };
    ll_list l = ll_from_array(vals, 4, sizeof(double));

    printf("Searching for a value in a list of doubles.\n");
    ll_print_double(l);

    ll_node *found = ll_search_value_double(l, 6.0);

    assert(ll_node_get_double(*found) == 6.0);
}

void test_ll_double_insert()
{
    double vals[] = { 7.0, 6.0, 5.0 };
    ll_list l = ll_from_array(vals, 3, sizeof(double));

    printf("Checking insertion into linked list of doubles.\n");

    assert(ll_node_get_double(*l.head) == 7.0);
    assert(ll_node_get_double(*l.head->next) == 6.0);
    assert(ll_node_get_double(*l.head->next->next) == 5.0);
    assert(!(*(l.head->next->next)).next);
    ll_print_double(l);

    double n = 4.0;
    ll_insert_double(&l, &n);
    ll_print_double(l);

    assert(ll_node_get_double(*l.head) == 4.0);
    assert(ll_node_get_double(*l.head->next) == 7.0);
    assert(ll_node_get_double(*l.head->next->next) == 6.0);
    assert(ll_node_get_double(*l.head->next->next->next) == 5.0);
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_int_from_array();
    test_ll_search_int();
    test_ll_int_insert();

    test_ll_double_from_array();
    test_ll_search_double();
    test_ll_double_insert();

    test_ll_eq();
    test_ll_remove_node();
    test_ll_search_key();
}
#endif
