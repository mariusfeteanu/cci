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

# On test generate some reports with the output of each program
test: $(REPORTS)
report/%: bin/%
	@echo -e "\n\n######## $* ########"
	mkdir -p report && rm -f $@ && set -o pipefail && ./bin/$* | tee $@

# Build and add test flag to add the test function and main function
# to each compiled program. Also include helper code from the common dir
bin/%: %.c common
	mkdir -p bin
	$(CC) $(CFLAGS) \
	-DTEST_$* \
	$*.c \
	$(COMMON_OBJECTS) \
	-o bin/$*

# Helper functions and typedefs
# Mostly implementation of data structs
common: $(COMMON_OBJECTS)

clean:
	for f in $(PROGRAMS); do \
	rm -fr $$f $$f.dSYM $$f.c~; \
	done
	rm -f $(COMMON_OBJECTS)
	rm -rf ./report/
	rm -rf ./bin/

# Use GNU indent on all files.
# It's half broken and touches all the files but it works..
indent: $(wildcard *.c) \
        $(wildcard *.h) \
        $(wildcard common/*.c) \
        $(wildcard common/*.h)
	VERSION_CONTROL=none indent -kr -ci2 -nut $?

# Separate build for travis. Mostly because making bash on travis work sucks
%.travis: bin/%
	@echo -e "\n\n######## $* ########"
	./bin/$*
travis: $(patsubst %.c,%.travis,$(wildcard *.c))
