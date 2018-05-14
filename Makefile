CC=g++
FLAGS=-O3
LIB=-lm

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:src/%.cpp=build/%.o)

BIN=bin/executable

#----------------------------

executable: $(BIN)

$(BIN): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $(BIN) $(LIB)

build/%.o: src/%.cpp include/%.h include/concrete_graph.h
	$(CC) -c $(FLAGS) $< -o $@

build/main.o: src/main.cpp
	$(CC) -c $(FLAGS) $< -o $@


.PHONY: clean
clean:
	rm build/*.o $(BIN)
