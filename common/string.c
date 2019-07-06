#include <assert.h>
#include <stdio.h>

int is_substr(char *substr, char *str)
{
    int match_start = 0;
    int i = 0;			// substring index
    int j = 0;			// string index

    while (substr[i] && str[j]) {
	if (substr[i] == str[j]) {
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
