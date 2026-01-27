CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c99 -Iheaders -g \
           $(shell pkg-config --cflags sdl2 2>/dev/null)
LDFLAGS := -lm # (keep for -L… if you need it)
LDLIBS  := $(shell pkg-config --libs sdl2 2>/dev/null) 

SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:.c=.o)

MINGW := x86_64-w64-mingw32-gcc
MINGW_FLAGS := -Wall -Wextra -pedantic -std=c99 -Iheaders -g \
	       -I/usr/x86_64-w64-mingw32/include/ \
	       -Wl,-subsystem,windows -lmingw32 
MINGW_LDLIBS := -L/usr/x86_64-w64-mingw32/lib/ -lSDL2main -lSDL2


MINGW_OBJ := $(SRC:.c=.obj)

.PHONY: all clean

all: maze

maze: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

maze.exe: $(MINGW_OBJ)
	$(MINGW) $(MINGW_FLAGS) -o $@ $^ $(MINGW_LDLIBS)
# Rebuild objects when the shared header changes
src/%.o: src/%.c headers/headers.h
	$(CC) $(CFLAGS) -c $< -o $@

src/%.obj: src/%.c headers/headers.h
	$(MINGW) $(MINGW_FLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJ) maze
