OBJECTS=
CFLAGS=-g -Wall -Werror -Og -pedantic -std=c11
LDLIBS=
CC=cc

# All files that have a .c extension in the current dir
# But without the extension
PROGRAMS=$(patsubst %.c,bin/%,$(wildcard *.c))
REPORTS=$(patsubst %.c,report/%,$(wildcard *.c))
COMMON_OBJECTS=$(patsubst %.c,%.o,$(wildcard common/*.c))

# Use default make rules to build
build: $(PROGRAMS)

test: $(REPORTS)
report/%: bin/%
	@echo -e "\n\n######## $* ########"
	mkdir -p report && rm -f $@ && set -o pipefail && ./bin/$* | tee $@

bin/%: %.c common
	mkdir -p bin
	$(CC) $(CFLAGS) \
	-DTEST_$* \
	$*.c \
	$(COMMON_OBJECTS) \
	-o bin/$*

common: $(COMMON_OBJECTS)

clean:
	for f in $(PROGRAMS); do \
	rm -fr $$f $$f.dSYM $$f.c~; \
	done
	rm -f $(COMMON_OBJECTS)
	rm -rf ./report/
	rm -rf ./bin/


indent: $(wildcard *.c) \
        $(wildcard *.h) \
        $(wildcard common/*.c) \
        $(wildcard common/*.h)
	VERSION_CONTROL=none indent -kr -ci2 -nut $?


%.travis: bin/%
	@echo -e "\n\n######## $* ########"
	./bin/$*
travis: $(patsubst %.c,%.travis,$(wildcard *.c))
