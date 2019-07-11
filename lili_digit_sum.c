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

    int *magic_int = malloc(sizeof(int));
    *magic_int = current_sum%10;

    ll_create_tail_node_int(sum, magic_int);
    carry = current_sum/10;
  }

  if(carry){
    int *magic_int = malloc(sizeof(int));
    *magic_int = carry;
    ll_create_tail_node_int(sum, magic_int);
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
  printf("Looks good!\n");
}

int main()
{
    setbuf(stdout, NULL);

    test_ll_digit_sum(
      ll_from_array((int []){7, 1, 6}, 3, sizeof(int)),
      ll_from_array((int []){5, 9, 2, 1}, 4, sizeof(int)),
      ll_from_array((int []){2, 1, 9, 1}, 4, sizeof(int))
    );

    test_ll_digit_sum(
      ll_from_array((int []){7, 1, 6}, 3, sizeof(int)),
      ll_from_array((int []){5, 9, 6}, 3, sizeof(int)),
      ll_from_array((int []){2, 1, 3, 1}, 4, sizeof(int))
    );

    test_ll_digit_sum(
      ll_from_array((int []){7, 1, 6}, 3, sizeof(int)),
      ll_from_array((int []){5, 9, 2}, 3, sizeof(int)),
      ll_from_array((int []){2, 1, 9}, 3, sizeof(int))
    );

    test_ll_digit_sum(
      ll_from_array((int []){4}, 1, sizeof(int)),
      ll_from_array((int []){5}, 1, sizeof(int)),
      ll_from_array((int []){9}, 1, sizeof(int))
    );

    test_ll_digit_sum(
      ll_empty(),
      ll_from_array((int []){1}, 1, sizeof(int)),
      ll_from_array((int []){1}, 1, sizeof(int))
    );

    test_ll_digit_sum(
      ll_empty(),
      ll_empty(),
      ll_empty()
    );
}
#endif
