#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/lili.h"

#ifdef TEST_test_lili
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

    assert(*ll_get_int(l, 0) == 4);
    assert(*ll_get_int(l, 1) == 7);
    assert(*ll_get_int(l, 2) == 6);
    assert(*ll_get_int(l, 3) == 5);
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

    assert(*ll_get_int(l, 0) == 7);
    assert(*ll_get_int(l, 1) == 6);
    assert(*ll_get_int(l, 2) == 5);
    assert(ll_length(l) == 3);
    ll_print_int(l);

    int n = 4.0;
    ll_insert_int(&l, &n);
    ll_print_int(l);

    assert(*ll_get_int(l, 0) == 4);
    assert(*ll_get_int(l, 1) == 7);
    assert(*ll_get_int(l, 2) == 6);
    assert(*ll_get_int(l, 3) == 5);
}

// ***** double tests *****
void test_ll_double_from_array()
{
    double vals[] = { 4.0, 7.0, 6.0, 5.0 };
    ll_list l = ll_from_array(vals, 4.0, sizeof(double));

    printf("Checking linked list creation from array of doubles.\n");
    ll_print_double(l);

    assert(*ll_get_double(l, 0) == 4.0);
    assert(*ll_get_double(l, 1) == 7.0);
    assert(*ll_get_double(l, 2) == 6.0);
    assert(*ll_get_double(l, 3) == 5.0);
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

    assert(*ll_get_double(l, 0) == 7.0);
    assert(*ll_get_double(l, 1) == 6.0);
    assert(*ll_get_double(l, 2) == 5.0);
    assert(ll_length(l) == 3);
    ll_print_double(l);

    double n = 4.0;
    ll_insert_double(&l, &n);
    ll_print_double(l);

    assert(*ll_get_double(l, 0) == 4.0);
    assert(*ll_get_double(l, 1) == 7.0);
    assert(*ll_get_double(l, 2) == 6.0);
    assert(*ll_get_double(l, 3) == 5.0);
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