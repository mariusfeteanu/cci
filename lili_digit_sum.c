#include <stdio.h>
#include "common/lili.h"

ll_list *ll_digit_sum(ll_list *x, ll_list *y)
{
  ll_list *sum = ll_empty();
  int carry = 0;

  ll_node *xn = x->head, *yn = y->head;

  while(xn || yn){
    int current_sum = carry;
    if(xn){
      current_sum += ll_node_get_int(xn);
      xn = xn->next;
    }
    if(yn){
      current_sum += ll_node_get_int(yn);
      yn = yn->next;
    }

    ll_node *node = malloc(sizeof(ll_node));
    int *magic_int = malloc(sizeof(int));
    *magic_int = current_sum%10;

    node->prev = sum->tail;
    node->next = NULL;
    node->key = magic_int;
    node->key_size = sizeof(int);

    if (sum->tail)
        sum->tail->next = node;
    if (!sum->head)
      sum->head = node;
    sum->tail = node;

    carry = current_sum/10;
  }

  return sum;
}

#ifdef TEST_lili_digit_sum
void test_ll_digit_sum(ll_list *x, ll_list *y, ll_list *expected_sum)
{
  ll_list *sum = ll_digit_sum(x, y);
  printf("Checking if the sum of:\n");
  ll_print_int(x);
  printf("And:\n");
  ll_print_int(y);
  printf("Is:\n");
  ll_print_int(expected_sum);
  printf("Calculated result:\n");
  ll_print_int(sum);
  assert(ll_eq(sum, expected_sum));
  printf("Looks good");
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_digit_sum(
      ll_from_array((int []){7, 1, 6}, 3, sizeof(int)),
      ll_from_array((int []){5, 9, 2}, 3, sizeof(int)),
      ll_from_array((int []){2, 1, 9}, 3, sizeof(int))
    );
}
#endif
