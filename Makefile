CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin
TESTS_DIR = tests

TARGET = $(BIN_DIR)/myhttpd

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	find $(TESTS_DIR) ! -name "*.c" ! -name "*.h" ! -name "$(TESTS_DIR)" -delete 2>/dev/null || true

test: $(TESTS_DIR)/test_headers
	./$(TESTS_DIR)/test_headers

$(TESTS_DIR)/test_headers: $(TESTS_DIR)/headers.c $(SRC_DIR)/http.c $(INCLUDE_DIR)/http.h | $(TESTS_DIR)
	$(CC) $(CFLAGS) -o $@ $(TESTS_DIR)/headers.c $(SRC_DIR)/http.c

$(TESTS_DIR):
	mkdir -p $(TESTS_DIR)