OBJECTS=
CFLAGS=-g -Wall -O1 -pedantic -std=c11
LDLIBS=
CC=cc

test: string_unique string_permutation string_urlify
	./string_unique
	./string_permutation
	./string_urlify

build: string_unique string_permutation string_urlify

string_unique: $(OBJECTS)
string_permutation: $(OBJECTS)
string_urlify: $(OBJECTS)


clean:
	rm -f string_unique string_permutation string_urlify

