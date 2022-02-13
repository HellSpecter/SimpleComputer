# папка куда упадут .o файлы все
BUILD_DIR = ./build

# папка где лежат все .cpp файлы (они могут быть во вложенных папках тоже)
SRC_DIR   = ./src

# компилятор
COMPILER = g++

# флаги компилятора
CFLAGS   = -I src

# название бинарника на выходе
BINARY_NAME = main

# === DO NOT EDIT UNDER THIS LINE ===
.RECIPEPREFIX=>
CPP_FILES = $(shell cd $(SRC_DIR) && find * -name "*.cpp")
OBJ_FILES = $(CPP_FILES:%.cpp=$(BUILD_DIR)/%.o)
OBJ_DIRS  = $(sort $(dir $(OBJ_FILES)))

all: $(BINARY_NAME)

$(OBJ_FILES): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
> $(COMPILER) $(CFLAGS) -c $< -o $@

$(BINARY_NAME): $(OBJ_DIRS) $(OBJ_FILES)
> $(COMPILER) $(CFLAGS) $(OBJ_FILES) -o $(BINARY_NAME)

$(OBJ_DIRS):
> mkdir -p $@

clean:
> rm -rf $(BUILD_DIR)
> rm -f  $(BINARY_NAME)

.PHONY: all clean