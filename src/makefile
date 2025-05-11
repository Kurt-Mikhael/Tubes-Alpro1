# Compiler
CC = gcc

# Direktori
SRC_DIR = src/c
HDR_DIR = src/header

# Otomatis deteksi semua .c dalam src/c
SRC = $(wildcard $(SRC_DIR)/*.c)
OUTPUT = main

# Flag kompilasi
CFLAGS = -I$(HDR_DIR) -std=c99 -Wall

# Target utama
all: $(OUTPUT)

$(OUTPUT): $(SRC) main.c
	$(CC) $(CFLAGS) $(SRC) main.c -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
