SRC=*.c
#SRC+=world.c etc1.c etc2.c
#SRC=$(wildcard *.c)  # en commentaire, je ne suis pas un grand amateur
EXE=snakeElisa

CC=gcc
CFLAGS:=-Wall -Wextra -MMD -Og -g $(sdl2-config --cflags)
#CFLAGS:=-Wall -Wextra -MMD -O2 $(sdl2-config --cflags)  # pour la version release
LDFLAGS:=-lSDL2_image -lSDL2_ttf -lSDL2_gfx -lm -lSDL2 -lSDL2_mixer

OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))

all: $(OBJ) 
		$(CC) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.c
		@mkdir -p build
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		rm -rf build core *.o

-include $(DEP)
