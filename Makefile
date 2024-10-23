# Inspired from
# https://www.lucavall.in/blog/crafting-clean-maintainable-understandable-makefile-for-c-project
#
# Good modern C practices
# https://matt.sh/howto-c

#Project Settings
debug ?= 0
NAME := CLearning
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
LIB_DIR := lib
TESTS_DIR := tests
BIN_DIR := bin

# Generate paths for all object files
OBJS := $(patsubst %.c,%.o, $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/**/*.c))

# Compiler settings
CC := clang
LINTER := clang-tidy
FORMATTER := clang-format

# Compiler and Linker flags Settings:
# 	-std=gnu17: Use the GNU17 standard
# 	-Wall: Enable all warnings
# 	-Wextra: Enable extra warnings
# 	-Wpedantic: Enable pedantic warnings
# 	-lm: Link to libm
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -Wstrict-overflow -fno-strict-aliasing
LDFLAGS := -L/opt/homebrew/opt/llvm/lib -lm

ifeq ($(debug), 1)
	CFLAGS := $(CFLAGS) -g -O0
else
	CFLAGS := $(CFLAGS) -Oz
endif

# Targets

# Build executable
$(NAME): format lint dir $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $(patsubst %, build/%, $(OBJS))

# Build object files and third-party libraries
$(OBJS): dir
	@mkdir -p $(BUILD_DIR)/$(@D)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ -c $*.c

# Run CUnit tests
test: dir
	@$(CC) $(CFLAGS) -Werror -Wshadow -lcunit -o $(BIN_DIR)/$(NAME)_test $(TESTS_DIR)/*.c
	@$(BIN_DIR)/$(NAME)_test

# Run linter on source directories
lint:
	@$(LINTER) --config-file=.clang-tidy $(SRC_DIR)/* -- $(CFLAGS) # $(INCLUDE_DIR)/* $(TESTS_DIR)/* -- $(CFLAGS)

# Run formatter on source directories
format:
	@$(FORMATTER) -style=file -i $(SRC_DIR)/* # $(INCLUDE_DIR)/* $(TESTS_DIR)/*

# Setup build and bin directories
dir:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(TEST_DIR)

# Clean build and bin directories
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

run: $(NAME)
	./$(BIN_DIR)/$(NAME)

.PHONY: lint format check dir clean run

