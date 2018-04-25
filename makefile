BINARY = mandelbox
OBJ := $(patsubst %.c,%.o,$(wildcard src/*.c))

CC = gcc
FLAGS = -Wall -O3

$(BINARY): $(OBJ)
	$(CC) $(FLAGS) -o $(BINARY) $(OBJ)

clean:
	rm $(BINARY) $(OBJ)

deploy:
	git add .
	git commit -m "update"
	git push https://github.com/alexhansen1234/raymarcher.git master
