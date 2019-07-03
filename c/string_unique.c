#include <stdio.h>
#include <assert.h>

int is_unique(char *input){
    // char is 8 bits
    // 255 possible values (we stop on NULL)
    // but we allocate it anyway to keep things readable
    char found[256] = {0};

    while(*input){
        if(found[(int)input[0]]){
            return 0;
        }
        else {
            found[(int)input[0]] = 1;
        }
        input++;
    }
  return 1;
}

void test_is_unique(){
    printf("Checking an unique string.\n");
    char a[] = "abc";
    assert(is_unique(a));
}

void test_is_not_unique(){
    printf("Checking a string with duplicates.\n");
    char a[] = "abca";
    assert(!is_unique(a));
}

void test_is_unique_empty(){
    printf("Checking an empty string.\n");
    char a[] = "";
    assert(is_unique(a));
}

int main(){
    test_is_unique();
    test_is_not_unique();
    test_is_unique_empty();
}
