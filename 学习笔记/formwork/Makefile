CC := g++
CUR_DIR := $(shell pwd)
FLAGS := -std=c++11 -w
INC_DIR := $(CUR_DIR)/be/include
SRC_DIR := $(CUR_DIR)/be/src
BUILD_DIR := $(CUR_DIR)/build
BIN_DIR := $(CUR_DIR)/build/bin
INCLUDE := -I$(INC_DIR)
src = $(wildcard $(SRC_DIR)/*.cpp)
obj = $(patsubst &(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(src))

$(BIN_DIR)/main: $(obj)
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $(obj) -lpthread -g -o $@
	@echo 'Build done!'

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -g -o  $@ $<

clean:
	@rm -rf $(BIN_DIR)/main
