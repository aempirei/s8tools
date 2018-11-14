CC = gcc
CCFLAGS = -Wall -W -w -lm
CFLAGS = -Wall -W -Wno-switch -Wno-implicit-fallthrough -std=gnu11 -Isrc/lib
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGETS = $(SOURCES:src/%.c=bin/%)
FOLD = add mul or xor and min max
FOLD_TARGETS = $(FOLD:%=bin/fold/%)
FOLD_OBJECTS = $(FOLD:%=src/fold.%.o)


.PHONY: all clean

all: bin bin/fold $(TARGETS) $(FOLD_TARGETS)

bin:
	mkdir bin

bin/fold:
	mkdir bin/fold

clean:
	rm -f $(TARGETS)
	rm -f $(FOLD_TARGETS)
	rm -f $(OBJECTS)
	rm -f src/lib/s8.o
	rm -f src/lib/s8-basic-function.o
	rmdir bin/fold
	rmdir bin

src/lib/s8.o: src/lib/s8.c src/lib/s8.h

src/lib/s8-basic-function.o: src/lib/s8-basic-function.c src/lib/s8-basic-function.h

bin/% : src/%.o src/lib/s8.o
	$(CC) -o $@ $^ $(CCFLAGS)

src/fold.%.o : src/template/fold.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ -DFOLD=binary_$*

bin/fold/% : src/fold.%.o src/lib/s8.o src/lib/s8-basic-function.o
	$(CC) -o $@ $^ $(CCFLAGS)
