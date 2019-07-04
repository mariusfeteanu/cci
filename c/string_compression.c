#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1024

void compress(char *input, char *output){
    char prev = *input;
    int occurences = 0;
     // use i to walk input because we need to detect
     // if the compression did anything
    int i = 0, j = 0;

    while(input[i]){
        assert(j+2<=MAX_SIZE); // because we need room to append the last count

        if(input[i] == prev){
            occurences++;
            // assert(occurences<10); // we don't handle more than five occurences yet
        } else {
            output[j] = prev;
            sprintf(output+j+1, "%d", occurences);
            j += (2 + occurences/10);
            occurences = 1;
        }

        prev = input[i];
        i++;
    }

    output[j] = prev;
    sprintf(output+j+1, "%d", occurences);
    j += 2;

    if(j >= i) strcpy(output, input);
}

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
