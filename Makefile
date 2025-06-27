#compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

#directories which i dont think I have any rn?
SRC_DIR := .
OBJ_DIR := obj
BIN_DIR := bin

#my excecuatble name 
TARGET := $(BIN_DIR)/test

#to get all cpp files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all := $(TARGET)

#then to link to executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@


#compile cpp to o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


#clean the things
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
	
