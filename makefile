BINARY = mandelbox
OBJ := $(patsubst %.c,%.o,$(wildcard src/*.c))

CC = gcc
FLAGS = -Wall -O3

$(BINARY): $(OBJ)
	$(CC) $(FLAGS) -o $(BINARY) $(OBJ)

clean:
	rm $(BINARY) $(OBJ)
