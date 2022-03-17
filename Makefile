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
FILES := $(shell find $(SRC_DIR) -name "*.c") # finds all source files 
COMPILE := $(MANDATORY_FLAGS) $(MY_FLAGS) $(FILES) -lm -o $(BUILD_DIR)/main.out 

default: help

## This help screen
help:
			@printf "Available targets:\n\n"
			@awk '/^[a-zA-Z\-\_0-9%:\\]+/ { \
				helpMessage = match(lastLine, /^## (.*)/); \
				if (helpMessage) { \
					helpCommand = $$1; \
					helpMessage = substr(lastLine, RSTART + 3, RLENGTH); \
		gsub("\\\\", "", helpCommand); \
		gsub(":+$$", "", helpCommand); \
					printf "  \x1b[32;01m%-35s\x1b[0m %s\n", helpCommand, helpMessage; \
				} \
			} \
			{ lastLine = $$0 }' $(MAKEFILE_LIST) | sort -u
			@printf "\n"

## Production build, run the executable
run: build
	$(BUILD_DIR)/main.out

## Debug build, run the executable with gdb
run/debug: build/debug
	gdb $(BUILD_DIR)/main.out

## Debug build, run the executable with valgrind to check for memory leaks
run/test: build/debug
	valgrind --leak-check=yes $(BUILD_DIR)/main.out

## Production build with optimisation 
build:
	gcc -O3 $(COMPILE)

## Debug build with debug infos
build/debug: create_dir
	gcc -g3 $(COMPILE)

create_dir: 
	mkdir -p $(BUILD_DIR) 

## Clean the directory
clean:
	rm -rf $(BUILD_DIR) 
	rm -f test.pgm
