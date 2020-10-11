CC=g++
CFLAGS = -Wall -g -std=c++17

SRC_DIR=src
TEST_DIR=test
OBJ_DIR=build

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJ_DIR)/Canvas.o $(OBJ_DIR)/tuple.o $(OBJ_DIR)/matrix.o 
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/test.out -I$(SRC_DIR) \
	$(OBJ_DIR)/Canvas.o $(OBJ_DIR)/tuple.o $(OBJ_DIR)/matrix.o \
	$(TEST_DIR)/tuple_test.cpp $(TEST_DIR)/canvas_test.cpp $(TEST_DIR)/matrix_test.cpp 
	$(OBJ_DIR)/test.out

clean:
	rm -r build/*

.PHONY: test clean

$(info $(shell mkdir -p $(OBJ_DIR)))