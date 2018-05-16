CC=g++
FLAGS=-O3 -Wall -Wextra
LIB=-lm -lleda -lX11

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:src/%.cpp=build/%.o)

BIN=bin/executable

LEDA_ROOT=${HOME}/Documents/lib/LEDA
LEDA_INCL=$(LEDA_ROOT)/incl

#----------------------------

executable: $(BIN)

$(BIN): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $(BIN) $(LIB) -L $(LEDA_ROOT)

build/%.o: src/%.cpp include/%.h include/concrete_graph.h
	$(CC) -c $(FLAGS) -I $(LEDA_INCL) $< -o $@

build/main.o: src/main.cpp
	$(CC) -c $(FLAGS) -I $(LEDA_INCL) $< -o $@


.PHONY: clean
clean:
	rm build/*.o $(BIN)
