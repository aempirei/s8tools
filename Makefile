CC = gcc
CCFLAGS = -Wall -W -w -lm
CFLAGS = -Wall -W -pedantic -std=gnu11 -Isrc/lib
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGETS = $(SOURCES:src/%.c=bin/%)

.PHONY: all clean

all: bin $(TARGETS)

bin:
	mkdir bin

clean:
	rm -f $(TARGETS)
	rm -f $(OBJECTS)
	rm -f src/lib/s8.o
	rmdir bin

src/lib/s8.o: src/lib/s8.c src/lib/s8.h

bin/% : src/%.o src/lib/s8.o
	$(CC) -o $@ $^ $(CCFLAGS)
