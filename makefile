BINARY := mandelbox
SRC_DIR := ./src
OBJ := $(patsubst %.c,%.o,$(wildcard $(SRC_DIR)/*.c))
SRC := $(wildcard src/*.c)


CC := gcc
FLAGS := -O3 -Wall

$(BINARY): $(OBJ)
	@echo Linking $(BINARY)
	@$(CC) $(FLAGS) -o $(BINARY) $(OBJ)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $@
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@rm -f $(BINARY) $(OBJ)

push:
	make clean
	git add .
	git commit -m "update"
	git push https://github.com/alexhansen1234/raymarcher.git master
