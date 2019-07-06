#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string.c"

int is_rotation(char *str, char *rot)
{
    int l = strlen(str);
    int lr = strlen(rot);
    if (l != lr)
	return 0;

    char *double_str = (char *) malloc(2 * l + 1);

    memcpy(double_str, str, l);
    memcpy(double_str + l, str, l + 1);

    return is_substr(rot, double_str);
}

#ifdef TEST_string_is_rotation
void test_is_rotation(char *str, char *rot)
{
    printf("Check that <<%s>> is a rotation of <<%s>>.\n", str, rot);
    assert(is_rotation(str, rot));
}

void test_is_not_rotation(char *str, char *rot)
{
    printf("Check that <<%s>> is not a rotation of <<%s>>.\n", str, rot);
    assert(!is_rotation(str, rot));
}

int main()
{
    setbuf(stdout, NULL);

    test_is_rotation("waterbottle", "erbottlewat");
    test_is_rotation("", "");

    test_is_not_rotation("waterbottle", "erbottlewa");
    test_is_not_rotation("waterbottle", "erbottlewatt");
    test_is_not_rotation("waterbottle", "");
    test_is_not_rotation("", "dsadsadasd");
}
#endif
