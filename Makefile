CXX = g++
CPPFLAGS = -Isrc
CXXFLAGS = -Wall -pedantic -std=gnu++14 -O2 -Wno-unused-result
CC = gcc
CCFLAGS = -Wall -W -w -lm
CFLAGS = -Wall -W -pedantic -std=gnu99
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGETS = $(SOURCES:src/%.c=bin/%)
INSTALL_PATH = /usr/local

.PHONY: all clean install

all: bin $(TARGETS)

bin:
	@mkdir bin

say:
	@echo "SOURCES = $(SOURCES)"
	@echo "OBJECTS = $(OBJECTS)"
	@echo "TARGETS = $(TARGETS)"

clean:
	rm -f $(TARGETS)
	rm -f $(OBJECTS)
	rmdir bin

install: $(TARGETS)
	install -m 755 bin/norm $(INSTALL_PATH)/bin
	install -m 755 bin/mean $(INSTALL_PATH)/bin
	install -m 755 bin/abs $(INSTALL_PATH)/bin
	install -m 755 bin/hull $(INSTALL_PATH)/bin
	install -m 755 bin/auto $(INSTALL_PATH)/bin
	install -m 755 bin/half $(INSTALL_PATH)/bin

bin/% : src/%.o
	$(CC) -o $@ $< $(CCFLAGS)
