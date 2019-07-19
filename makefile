CFLAGS=-g -Wall -Werror -O0 -pedantic -std=c11
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
	@echo -e "\n\n###TEST### $*###TEST###"
	mkdir -p report && rm -f $@ && set -o pipefail && ./bin/$* | tee $@

# Build common objects in their own dir as object files
bin/common/%.o: common/%.c
	mkdir -p bin/common
	$(CC) -c $(CFLAGS) common/$*.c -o $@
# Build and add test flag to add the test function and main function
# to each compiled program. Also include helper code from the common dir
bin/%: %.c common $(COMMON_OBJECTS) $(COMMON_HEADERS)
	@echo -e "\n\n###BUILD### $* ###BUILD###"
	mkdir -p bin
	$(CC) $(CFLAGS) \
	-DTEST_$* \
	$*.c \
	$(COMMON_OBJECTS) \
	-o bin/$*

# TODO: this does not calculate coverage for common objects
coverage: clean $(patsubst %,cov/%.gcov,$(wildcard *.c))
	rm -rf ./bin/
	@if grep "\#\#\#\#" cov/*.c.gcov ; then \
		echo "Found not covered code, see above"; \
		exit 1; \
	else \
		echo "All code covered"; \
	fi
cov/%.c.gcov: CFLAGS += -fprofile-arcs -ftest-coverage
cov/%.c.gcov: bin/%
	@echo -e "\n\n###COVER### $*###COVER###"
	mkdir -p cov
	./bin/$*
	gcov $*.gcda
	mv $*.gcda $*.gcno $*.c.gcov ./cov/

leakcheck: $(patsubst %.c,leakcheck/%,$(wildcard *.c))
leakcheck/%: bin/%
	mkdir -p leakcheck
	valgrind --leak-check=yes --error-exitcode=1 ./bin/$*
	touch leakcheck/$*

clean:
	rm -rf ./report/ ./bin/ ./indent/ *.gcno *.gcda *.c.gcov ./cov/ ./leakcheck/

# Use GNU indent on all files.
# Just to work around indent fiddling with timestamps...
%.indent: %
	@mkdir -p indent/common
	@VERSION_CONTROL=none indent \
			--k-and-r-style \
			--pointer-align-right \
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
