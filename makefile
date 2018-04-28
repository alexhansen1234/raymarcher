BINARY := mandelbox
SRC_DIR := ./src
BUILD_DIR := ./bin
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o, $(notdir $(SRC)))

CC := gcc
FLAGS := -O3 -Wall

$(BINARY): $(BUILD_DIR) $(OBJ)
	@echo Linking Target $(BINARY)
	@$(CC) $(FLAGS) -o $(BINARY) $(OBJ)

$(BUILD_DIR):
	@echo Creating Build directory $(BUILD_DIR)
	@mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $@
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@if [ -d bin ]; then\
		echo Removing $(BUILD_DIR);\
		rm -rf $(BUILD_DIR);\
	fi


cleaner:
	@make clean
	@echo Removing $(BINARY)
	@rm -f $(BINARY)

push:
	make cleaner
	git add .
	git commit -m "update"
	git push https://github.com/alexhansen1234/raymarcher.git master
