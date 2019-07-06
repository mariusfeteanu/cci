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
	@echo -e "\n\n######## $* ########"
	rm -f $@ && set -o pipefail && ./$* | tee $@

%: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -DTEST_$* $*.c -o $*

# Use default make rules to build
build: $(PROGRAMS)

clean:
	for f in $(PROGRAMS); do \
	rm -fr $$f $$f.report $$f.dSYM $$f.c~; \
	done


indent:
	VERSION_CONTROL=none indent -kr *.c


%.travis: %
	@echo -e "\n\n######## $* ########"
	./$*
travis: $(patsubst %.c,%.travis,$(wildcard *.c))
