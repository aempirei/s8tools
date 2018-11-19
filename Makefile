CC = gcc
CCFLAGS = -Wall -W -w -lm
CFLAGS = -Wall -W -Wno-switch -Wno-implicit-fallthrough -std=gnu11 -Isrc/lib
FOLD = add mul or xor and min max
CMP = eq ne lt gt le ge
BANK = mean median mode rms
SOURCES = $(wildcard src/*.c)
TARGETS = $(SOURCES:src/%.c=bin/%)
LIBSRCS = $(wildcard src/lib/*.c)
LIBOBJS = $(LIBSRCS:%.c=%.o)
.PHONY: all clean

all: bin lib lib/libs8.a $(TARGETS) $(FOLD:%=bin/%) $(CMP:%=bin/%)

bin:
	mkdir bin

lib:
	mkdir lib

clean:
	rm -f $(TARGETS)
	rm -f $(FOLD:%=bin/%)
	rm -f $(CMP:%=bin/%)
	rm -f lib/libs8.a
	rmdir bin
	rmdir lib

lib/libs8.a: $(LIBOBJS)
	ar crfv $@ $^

src/lib/s8.o: $(wildcard src/lib/s8.[ch])

src/lib/s8-basic-function.o: $(wildcard src/lib/s8-basic-function.[ch])

.INTERMEDIATE: $(FOLD:%=src/fold.%.o) $(CMP:%=src/cmp.%.o) $(LIBOBJS)

src/fold.%.o: src/template/fold.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DFOLD=binary_$* -c -o $@ $<

src/cmp.%.o: src/template/cmp.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DCMP=cmp_$* -c -o $@ $<

bin/%: src/%.o lib/libs8.a
	$(CC) -o $@ $^ $(CCFLAGS)

$(FOLD:%=bin/%): bin/%: src/fold.%.o lib/libs8.a
	$(CC) -o $@ $^ $(CCFLAGS)

$(CMP:%=bin/%): bin/%: src/cmp.%.o lib/libs8.a
	$(CC) -o $@ $^ $(CCFLAGS)
