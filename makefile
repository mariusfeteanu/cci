CFLAGS=-g -Wall -Werror -Og -pedantic -std=c11
LDLIBS=
CC=cc

# The programs we will build (and test)
PROGRAMS=$(patsubst %.c,bin/%,$(wildcard *.c))
# The execution reports (program output and errors)
REPORTS=$(patsubst %.c,report/%,$(wildcard *.c))
# The compiled common code as object files (linked list fuctions etc.)
COMMON_OBJECTS=$(patsubst common/%.c,bin/common/%.o,$(wildcard common/*.c))
# Header for the common code
COMMON_HEADERS=$(wildcard common/*.h)
# Don't delete helper objects (in case we want to inspect them)
.PRECIOUS: $(COMMON_OBJECTS)

# Use default make rules to build
build: $(PROGRAMS)

# On test generate some reports with the output of each program
test: $(REPORTS)
report/%: bin/%
	@echo -e "\n\n######## $* ########"
	mkdir -p report && rm -f $@ && set -o pipefail && ./bin/$* | tee $@

# Build common objects in their own dir as object files
bin/common/%.o: common/%.c
	mkdir -p bin/common
	$(CC) -c $(CFLAGS) common/$*.c -o $@
# Build and add test flag to add the test function and main function
# to each compiled program. Also include helper code from the common dir
bin/%: %.c common $(COMMON_OBJECTS) $(COMMON_HEADERS)
	mkdir -p bin
	$(CC) $(CFLAGS) \
	-DTEST_$* \
	$*.c \
	$(COMMON_OBJECTS) \
	-o bin/$*

clean:
	rm -rf ./report/
	rm -rf ./bin/
	rm -rf ./indent/

# Use GNU indent on all files.
# Just to work around indent fiddling with timestamps...
%.indent: %
	@mkdir -p indent/common
	@VERSION_CONTROL=none indent \
			--k-and-r-style \
			--no-tabs $< \
			--output indent/$<~
	@if cmp --silent indent/$<~ $<; then \
		rm indent/$<~; \
	else \
		mv indent/$<~ $< && touch $< && echo "indenting $<"; \
	fi
	@rm -rf indent/common indent/

indent: $(patsubst %, %.indent, \
            $(wildcard *.c) \
            $(wildcard common/*.c) \
            $(wildcard common/*.h))

# Separate build for travis. Mostly because making bash on travis work sucks
%.travis: bin/%
	@echo -e "\n\n######## $* ########"
	./bin/$*
travis: $(patsubst %.c,%.travis,$(wildcard *.c))
