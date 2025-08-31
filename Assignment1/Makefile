CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include

SRC_DIR = src
SEARCH_DIR = $(SRC_DIR)/search
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/state.cpp \
       $(SEARCH_DIR)/bfs.cpp

OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

TARGET = container_solver

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all run clean