#include <stdio.h>
#include <assert.h>
#include <string.h>

int is_close(char *left, char *right)
{
    int any_change = 0;

    while (*left) {
	if (*right) {		// we still have chars in the right string
	    if (*left != *right) {
		// if there is any differences then either
		// 1. left must equal the rest of right
		// 2. right must equal the rest of left
		// 3. the rest of both must the same
		return (!strcmp(left, right + 1)
			|| !strcmp(left + 1, right)
			|| !strcmp(left + 1, right + 1));
	    }
	} else {		// we are out of right string
	    // if we have seen a change before then this would be the second
	    // we are no longer close
	    return !any_change;
	}
	left++;
	right++;
    }
    // if I saw any changes so far
    // then nothig should be left on the right
    if (any_change) {
	return !*right;
    }
    // if I did not see any changes then either
    // 1. precisely one char must be left
    // 2. zero characters must be left
    else {
	return (*right && !*(right + 1)) || !*right;
    }
}

#ifdef TEST_string_one_away
void test_is_close(char *left, char *right)
{
    printf("Checkin' that <<%s>> is close to <<%s>>.\n", left, right);
    assert(is_close(left, right));
}

void test_is_not_close(char *left, char *right)
{
    printf("Checkin' that <<%s>> is not close to <<%s>>.\n", left, right);
    assert(!is_close(left, right));
}

int main()
{
    setbuf(stdout, NULL);
    test_is_close("pale", "ple");
    test_is_close("pales", "pale");
    test_is_close("pale", "bale");

    test_is_close("ple", "pale");
    test_is_close("pale", "pales");
    test_is_close("bale", "pale");

    test_is_not_close("pale", "bake");
    test_is_not_close("bake", "pale");

    test_is_close("", "");
    test_is_close("", "a");
    test_is_not_close("dsadsa", "3jdsa0");
    test_is_close("apple", "aple");
}
#endif
