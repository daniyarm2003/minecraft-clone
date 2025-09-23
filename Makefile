BUILD_DIR ?= build
SRC_DIR ?= src

SRC_SUBDIRS := $(shell find $(SRC_DIR) -type d)

EXECUTABLE_NAME ?= game
EXECUTABLE_PATH := $(BUILD_DIR)/$(EXECUTABLE_NAME)

CPP_FILES := $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.cpp))
C_FILES := $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.c))

OBJ_FILES_CPP := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES))
OBJ_FILES_C := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_FILES))

CPP_FLAGS ?= -Iinclude -Wall -O2 -MMD -pg -std=c++17
C_FLAGS ?= -Iinclude -Wall -O2 -MMD -pg

LDFLAGS ?= -lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -pg

.PHONY: all clean

all: $(EXECUTABLE_PATH)

-include $(OBJ_FILES_CPP:.o=.d)
-include $(OBJ_FILES_C:.o=.d)

$(OBJ_FILES_CPP): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	g++ $(CPP_FLAGS) -c $< -o $@

$(OBJ_FILES_C): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	gcc $(C_FLAGS) -c $< -o $@

$(EXECUTABLE_PATH): $(OBJ_FILES_CPP) $(OBJ_FILES_C)
	g++ $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)