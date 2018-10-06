CXX = g++
CPPFLAGS = -Isrc
CXXFLAGS = -Wall -pedantic -std=gnu++14 -O2 -Wno-unused-result
CC = gcc
CCFLAGS = -Wall -W -w -lm
CFLAGS = -Wall -W -pedantic -std=gnu99
TARGETS = bin/norm bin/mean bin/hull bin/abs bin/auto bin/plot bin/dx bin/half
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
	install -m 755 bin/half $(INSTALL_PATH)/bin

bin/% : src/%.o
	$(CC) -o $@ $< $(CCFLAGS)
