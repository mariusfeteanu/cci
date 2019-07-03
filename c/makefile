OBJECTS=
CFLAGS=-g -Wall -Werror -O1 -pedantic -std=c11
LDLIBS=
CC=cc

test: string_unique \
      string_permutation \
      string_urlify \
      string_palin_anagarm
	./string_unique
	./string_permutation
	./string_urlify
	./string_palin_anagarm

build: string_unique \
       string_permutation \
       string_urlify \
       string_palin_anagarm

string_unique: $(OBJECTS)
string_permutation: $(OBJECTS)
string_urlify: $(OBJECTS)
string_palin_anagarm: $(OBJECTS)

clean:
	rm -f \
	string_unique \
	string_permutation \
	string_urlify \
	string_palin_anagarm

