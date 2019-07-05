OBJECTS=
CFLAGS=-g -Wall -Werror -O0 -pedantic -std=c11
LDLIBS=
CC=cc

# All files that have a .c extension in the current dir
# But without the extension
PROGRAMS=$(patsubst %.c,%,$(wildcard *.c))
REPORTS=$(patsubst %.c,%.report,$(wildcard *.c))

test: $(REPORTS) 

%.report: %
	rm -f $@ && set -o pipefail && ./$* | tee $@

# Use default make rules to build
build: $(PROGRAMS)

clean:
	for f in $(PROGRAMS); do \
	rm -fr $$f $$f.report $$f.dSYM; \
	done

%.travis: %
	./$*

travis: $(patsubst %.c,%.travis,$(wildcard *.c))
