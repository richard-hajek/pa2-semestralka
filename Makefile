CC=g++
CARGS=-g -Wall -pedantic
SOURCES=$(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
LIBS=-lncurses

O=hajekric

all: compile doc

run: compile
	./hajekric examples/setup map The_Valley

doc:
	mkdir -p ./doc
	doxygen doxygen/doxygen.conf

compile:
	$(CC) $(CARGS) $(LIBS) $(SOURCES) -o $(O)

clean:
	rm -r doc
	rm -r $(O)
