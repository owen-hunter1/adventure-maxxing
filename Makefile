CC=clang

# Flags
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic -Iinclude
DEBUG_FLAGS=-g -O0

# Sanitizers
SANITIZERS=-fsanitize=address,undefined

# SDL
SDL_FLAGS=$(shell sdl2-config --cflags --libs)

# Source files
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

# Output
TARGET=bin/game

all: debug

debug: CFLAGS += $(DEBUG_FLAGS) $(SANITIZERS)
debug: $(TARGET)

release: CFLAGS += -O2
release: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(SDL_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: debug
	./$(TARGET)

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all debug release run clean