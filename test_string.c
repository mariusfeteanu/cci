#include <assert.h>
#include <stdio.h>
#include "common/string.h"

#ifdef TEST_test_string
void test_is_substr(char *substr, char *str)
{
    printf("Check that <<%s>> is a substring of <<%s>>.\n", substr, str);
    assert(is_substr(substr, str));
}

void test_is_not_substr(char *substr, char *str)
{
    printf("Check that <<%s>> is not a substring of <<%s>>.\n", substr,
           str);
    assert(!is_substr(substr, str));
}

int main()
{
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
