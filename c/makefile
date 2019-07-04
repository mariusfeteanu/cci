OBJECTS=
CFLAGS=-g -Wall -Werror -O1 -pedantic -std=c11
LDLIBS=
CC=cc

# All files that have a .c extension in the current dir
# But without the extension
PROGRAMS=$(shell ls *.c | cut -d "." -f 1)

# Use default make rules to build
*.report: $(PROGRAMS)
	for t in $?; do \
	echo "### Testing [$$t] ###" \
	rm -f $$t.report && \
	./$$t >$$t.report && \
	cat $$t.report; \
	done

# Use default make rules to build
build: $(PROGRAMS)

clean:
	for f in $(PROGRAMS); do \
	rm -fr $$f $$f.report $$f.dSYM; \
	done
