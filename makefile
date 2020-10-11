CC=g++
CFLAGS = -Wall -g -std=c++17

SRC_DIR=src
OBJ_DIR=build

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

tuple_test: $(OBJ_DIR)/tuple.o $(OBJ_DIR)/tuple_test.o
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/tuple_test $(OBJ_DIR)/tuple.o $(OBJ_DIR)/tuple_test.o

test: tuple_test
	$(OBJ_DIR)/tuple_test

clean:
	rm -r build/*

.PHONY: test clean

$(info $(shell mkdir -p $(OBJ_DIR)))