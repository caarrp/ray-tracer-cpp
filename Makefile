#compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 

DEBUG ?= false

ifeq ($(DEBUG), true)
    CXXFLAGS := -std=c++17 -Wall -Wextra -g -O0 -DDEBUG
endif

#directories which i dont think I have any rn?
SRC_DIR := .
OBJ_DIR := obj
BIN_DIR := bin

#my excecuatble name 
TARGET := $(BIN_DIR)/test

#to get all cpp files
SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(patsubst %.cc,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))
all := $(TARGET)

#then to link to executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@


#compile cpp to o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#writing ppm to test file
run: bin/test
	./bin/test > test.ppm
	display test.ppm


#clean the things
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
	
