#include <stdio.h>
#include <assert.h>

void count_char(char *array, int *found){
    while(*array){
        found[(int)array[0]] += 1;
        array++;
    }
}

int is_permutation(char *input, char *perm){
    // char is 8 bits
    // 255 possible values (we stop on NULL)
    // but we allocate it anyway to keep things readable
    int found_input[256] = {0};
    int found_perm[256] = {0};

    count_char(input, found_input);
    count_char(perm, found_perm);

    for(int i = 1; i < 256; i++){ //i=0 skipped intentionally, see above
        if(found_input[i] != found_perm[i]){
            return 0;
        }
    }

  return 1;
}

void test_is_permutation(){
    char a[] = "abc", b[] = "cab";
    printf("Checking a valid permutation (%s) -> (%s).\n", a, b);
    assert(is_permutation(a, b));
}

void test_is_not_permutation(){
    char a[] = "abc", b[] = "cabd";
    printf("Checking an invalid permutation (%s) -> (%s).\n", a, b);
    assert(!is_permutation(a, b));
}

void test_is_not_permutation_samechars(){
    char a[] = "abc", b[] = "cabcab";
    printf("Checking an invalid permutation (%s) -> (%s).\n", a, b);
    assert(!is_permutation(a, b));
}

void test_is_not_permutation_one_empty(){
    char a[] = "abc", b[] = "";
    printf("Checking an invalid permutation (%s) -> (%s).\n", a, b);
    assert(!is_permutation(a, b));

    printf("Checking an invalid permutation (%s) -> (%s).\n", b, a);
    assert(!is_permutation(b, a));
}

void test_is_permutation_empty(){
    char a[] = "", b[] = "";
    printf("Checking an valid permutation (%s) -> (%s).\n", a, b);
    assert(is_permutation(a, b));
}

int main(){
     test_is_permutation();
     test_is_not_permutation();
     test_is_not_permutation_samechars();
     test_is_permutation_empty();
     test_is_not_permutation_one_empty();
}
