#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1024

void emit_compressed(char *output,
                     char prev,
                     int *j,
                     int *occurences){
    int digit_count = 1 + *occurences/10;

    assert((*j + digit_count + 1) < MAX_SIZE);

    output[*j] = prev;
    *j += 1;
    sprintf(&output[*j], "%d", *occurences);
    *j += digit_count;

    *occurences = 1;
}

void compress(char *input, char *output){
    char prev = *input;
    int occurences = 0;
     // use i to walk input because we need to detect
     // if the compression did anything
    int i = 0, j = 0;

    while(input[i]){
        if(input[i] == prev){
            occurences++; // the same char again
        } else {
            emit_compressed(output, prev, &j, &occurences);
        }
        prev = input[i];
        i++;
    }

    emit_compressed(output, prev, &j, &occurences);

    if(j >= i) strcpy(output, input);
}

#ifdef TEST_string_compression
void test_compress(char *input, char *expected_output){
    printf("Checking compression of <<%s>> to <<%s>>.\n", input, expected_output);

    char output[MAX_SIZE] = {0};
    compress(input, output);

    assert(!strcmp(output, expected_output));
}

int main(){
    setbuf(stdout, NULL);
    test_compress("aabcccccaaa", "a2b1c5a3");
    test_compress("abcd", "abcd");
    test_compress("", "");
    test_compress("aaaaaaaaaaaabb", "a12b2");
    test_compress("abbbb", "a1b4");
}
#endif
