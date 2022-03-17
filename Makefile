 # compiler flags
MANDATORY_FLAGS := -fdiagnostics-color=always  \
									 -Wall \
									 -Wpedantic \
									 -std=c99

									 	# use color in diagnostics
										# enables all construction warnings
									 	# enable all warnings demanded by ISO C
									  # follow ANSI C99 

MY_FLAGS := -Wextra \
						-Werror \
						-Wshadow \
						-Wundef \
						-fno-common \
						
						# set of warnings and errors not covered by -Wall
						# all warnings cause errors
						# warnings for shadowing variables
						# warnings for undefined macros
						# warnings for global variables

BUILD_DIR := ./dist
SRC_DIR := .

# finds all source files in /src/*
FILES := $(shell find $(SRC_DIR) -name "*.c") 

COMPILE := $(MANDATORY_FLAGS) $(MY_FLAGS) $(FILES) -lm -o $(BUILD_DIR)/main.out 

# run the previously built executable
run: build
	$(BUILD_DIR)/main.out

run/debug: build/debug
	gdb $(BUILD_DIR)/main.out

run/testing: build/debug
	valgrind --leak-check=yes $(BUILD_DIR)/main.out

build:
	gcc -O3 $(COMPILE)

build/debug: create_dir
	gcc -g3 $(COMPILE)

create_dir: 
	mkdir -p $(BUILD_DIR) 

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) 
	rm -f test.pgm
