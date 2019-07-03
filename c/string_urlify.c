#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define SPACE_ESCAPE "%20"

void urlify(char *input, int real_length){
    int length = strlen(input);

    while(real_length){
        real_length--;

        char curr = input[real_length];
        if(curr == ' '){
            length -= 3;
            memcpy(input + length, SPACE_ESCAPE, 3);
        }
        else {
            length--;
            input[length] = curr;
        }
    }
}

void test_urilify(char a[], char e[], int l){
    printf("Urlifying <<%s>> of length <<%d>> to ", a, l);
    urlify(a, l);
    assert(strcmp(a, e) == 0);
    printf("<<%s>>.\n", a);
}

int main(){
    char s1[] = "Mr John Smith    ";
    char e1[] = "Mr%20John%20Smith";
    test_urilify(s1, e1, 13);

    char s2[] = "";
    char e2[] = "";
    test_urilify(s2, e2, 0);

    char s3[] = "      ";
    char e3[] = "%20%20";
    test_urilify(s3, e3, 2);

    char s4[] = "abc";
    char e4[] = "abc";
    test_urilify(s4, e4, 3);
}
