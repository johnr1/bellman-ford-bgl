CC=g++
FLAGS=-O3 -std=c++0x
LIB=-lm

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:src/%.cpp=build/%.o)

BIN=bin/bellman_ford

#----------------------------

executable: $(BIN)

$(BIN): $(OBJECTS) include/io.h
	$(CC) $(OBJECTS) -o $(BIN) $(LIB)

build/%.o: src/%.cpp include/%.h
	$(CC) -c $(FLAGS) $< -o $@

build/main.o: src/main.cpp
	$(CC) -c $(FLAGS) $< -o $@


.PHONY: clean
clean:
	rm build/*.o $(BIN)
