CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c99 -Iheaders -g \
           $(shell pkg-config --cflags sdl2 2>/dev/null)
LDFLAGS := -lm # (keep for -L… if you need it)
LDLIBS  := $(shell pkg-config --libs sdl2 2>/dev/null) 

SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:.c=.o)

.PHONY: all clean

all: maze

maze: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

# Rebuild objects when the shared header changes
src/%.o: src/%.c headers/headers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) maze
