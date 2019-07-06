#include <stdio.h>
#include <assert.h>

int is_palin_anagram(char *input)
{
    int found[128] = { 0 };

    while (*input) {
	if (*input != ' ') {
	    found[(int) *input] += 1;
	}
	input++;
    }

    int found_even = 0;
    for (int i = 0; i < 128; i++) {
	if (found[i] % 2 == 1) {
	    if (found_even)
		return 0;
	    found_even = 1;
	}
    }

    return 1;
}

#ifdef TEST_string_palin_anagram
void test_is_palin_anagram(char *s)
{
    printf("Checking if <<%s>> is an anagram of a plaindrome.\n", s);
    assert(is_palin_anagram(s));
}

void test_is_not_palin_anagram(char *s)
{
    printf("Checking if <<%s>> is not an anagram of a plaindrome.\n", s);
    assert(!is_palin_anagram(s));
}

int main()
{
    setbuf(stdout, NULL);
    test_is_palin_anagram("tact coa");
    test_is_palin_anagram("");
    test_is_not_palin_anagram("aaab");
}
#endif
