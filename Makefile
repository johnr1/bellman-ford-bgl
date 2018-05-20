CC=g++
FLAGS=-O3 -std=c++0x -g
LIB=-lm -lleda

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:src/%.cpp=build/%.o)

BIN=bin/bellman_ford

LEDA_ROOT=/usr/local/LEDA
LEDA_INCL=$(LEDA_ROOT)/incl

#----------------------------

executable: $(BIN)

$(BIN): $(OBJECTS) include/io.h
	$(CC) -g $(OBJECTS) -o $(BIN) $(LIB) -L $(LEDA_ROOT)

build/%.o: src/%.cpp include/%.h
	$(CC) -c $(FLAGS) -I $(LEDA_INCL) $< -o $@

build/main.o: src/main.cpp
	$(CC) -c $(FLAGS) -I $(LEDA_INCL) $< -o $@


.PHONY: clean
clean:
	rm build/*.o $(BIN)
