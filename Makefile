CXX = g++
CPPFLAGS = -Isrc
CXXFLAGS = -Wall -pedantic -std=gnu++14 -O2 -Wno-unused-result
CC = gcc
CCFLAGS = -Wall -W -w
CFLAGS = -Wall -W -pedantic -std=gnu99
TARGETS = bin/norm bin/mean bin/hull bin/abs bin/auto
INSTALL_PATH = /usr/local
OBJECTS = src/*.o

.PHONY: all clean install

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
	rm -f $(OBJECTS)

install: $(TARGETS)
	install -m 755 bin/norm $(INSTALL_PATH)/bin
	install -m 755 bin/mean $(INSTALL_PATH)/bin
	install -m 755 bin/abs $(INSTALL_PATH)/bin
	install -m 755 bin/hull $(INSTALL_PATH)/bin
	install -m 755 bin/auto $(INSTALL_PATH)/bin

bin/norm: src/norm.o
	$(CC) -o $@ $< $(CCFLAGS) -lm

bin/mean: src/mean.o
	$(CC) -o $@ $< $(CCFLAGS)

bin/abs: src/abs.o
	$(CC) -o $@ $< $(CCFLAGS)

bin/hull: src/hull.o
	$(CC) -o $@ $< $(CCFLAGS)

bin/auto: src/auto.o
	$(CC) -o $@ $< $(CCFLAGS) -lm
