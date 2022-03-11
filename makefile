FLAGS := -fdiagnostics-color=always -Wall -Wpedantic -std=c99 # compiler flags

BUILD_DIR := ./build
SRC_DIR := ./src

FILES := $(shell find $(SRC_DIR) -name "*.c") # finds all source files in /src/*
COMPILE := $(FLAGS) $(FILES) -lm -o $(BUILD_DIR)/main.out # put everything together

run: main
	$(BUILD_DIR)/main.out

main: pre
	gcc $(COMPILE)

debug: pre
	gcc -g $(COMPILE)
	gdb $(BUILD_DIR)/main.out

pre: 
	mkdir -p $(BUILD_DIR) 

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) 
	rm -f test.pgm
