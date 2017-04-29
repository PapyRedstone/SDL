SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic -lm
LDFLAGS = -lSDL -lSDL_image

all: sdl.out

sdl.out : $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm *.o *.out *.gch
