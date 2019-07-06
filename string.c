#include <assert.h>
#include <stdio.h>

int is_substr(char *substr, char *str){
    int match_start = 0;
    int i = 0; // substring index
    int j = 0; // string index

    while(substr[i] && str[j]){
        if(substr[i] == str[j]){
            i++;
            j++;
        } else {
            match_start++;
            j = match_start;
            i = 0;
        }
    }

    // we have a match if and only if
    // we are out of substring to match
    return !substr[i];
}

#ifdef TEST_string
void test_is_substr(char *substr, char *str){
    printf("Check that <<%s>> is a substring of <<%s>>.\n", substr, str);
    assert(is_substr(substr, str));
}

void test_is_not_substr(char *substr, char *str){
    printf("Check that <<%s>> is not a substring of <<%s>>.\n", substr, str);
    assert(!is_substr(substr, str));
}

int main(){
    setbuf(stdout, NULL);

    test_is_substr("ho", "horse");
    test_is_substr("or", "horse");
    test_is_substr("se", "horse");
    test_is_substr("", "horse");
    test_is_substr("horse", "horse");
    test_is_substr("", "");

    test_is_not_substr("mo", "horse");
    test_is_not_substr("horses", "horse");
    test_is_not_substr("horse", "");
}
#endif
