CC = gcc
CCFLAGS = -Wall -W -w -lm
CFLAGS = -Wall -W -Wno-switch -Wno-implicit-fallthrough -std=gnu11 -Isrc/lib
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGETS = $(SOURCES:src/%.c=bin/%)
FOLD = add mul or xor and min max
BANK = mean median mode rms

.PHONY: all clean

all: bin $(TARGETS) $(FOLD:%=bin/%)

bin:
	mkdir bin

clean:
	rm -f $(TARGETS)
	rm -f $(FOLD:%=bin/%)
	rm -f src/lib/s8.o
	rm -f src/lib/s8-basic-function.o
	rmdir bin

src/lib/s8.o: $(wildcard src/lib/s8.[ch])

src/lib/s8-basic-function.o: $(wildcard src/lib/s8-basic-function.[ch])

src/fold.%.o: src/template/fold.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ -DFOLD=binary_$*

bin/% : src/%.o src/lib/s8.o
	$(CC) -o $@ $^ $(CCFLAGS)

$(FOLD:%=bin/%) : bin/% : src/fold.%.o src/lib/s8.o src/lib/s8-basic-function.o
	$(CC) -o $@ $^ $(CCFLAGS)
