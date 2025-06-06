

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall

# Source files and directories
src = (wildcard *.c)
SRCS = $(shell find . -name "*.c")
OBJS = $(patsubst ./%,build/%,$(SRCS:.c=.o))

# Target executable
TARGET = build/main

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	@echo "Linking object files..."
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile .c files into .o files
build/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	@echo "Cleaning up..."
	rm -rf build

# Run target
run: $(TARGET)
	@echo "Running the project..."
ifdef folder
	@./$(TARGET) $(folder)
else
	@./$(TARGET) file
endif