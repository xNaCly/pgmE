 # compiler flags
MANDATORY_FLAGS := -fdiagnostics-color=always  \
									 -Wall \
									 -Wpedantic \
									 -std=c11

									 	# use color in diagnostics
										# enables all construction warnings
									 	# enable all warnings demanded by ISO C
									  # follow ANSI C99 

MY_FLAGS := -Wextra \
						-Werror \
						-Wshadow \
						-Wundef \
						-fno-common 
						
						# set of warnings and errors not covered by -Wall
						# all warnings cause errors
						# warnings for shadowing variables
						# warnings for undefined macros
						# warnings for global variables

BUILD_DIR := ./build
PROD_DIR := ./dist
SRC_DIR := .
OUT_NAME := pgmE
FILES := $(shell find $(SRC_DIR) -name "*.c") # finds all source files 
COMPILE := $(MANDATORY_FLAGS) $(MY_FLAGS) $(FILES) -lm -o 

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

## self install
install: build/prod
	cp ./pgmE.1 ./pgmE.1_copy
	gzip ./pgmE.1_copy
	mv ./pgmE.1_copy.gz ./pgmE.1.gz
	sudo mkdir -p /usr/local/share/man/man1
	sudo mv pgmE.1.gz /usr/local/share/man/man1/pgmE.1.gz
	sudo mv $(PROD_DIR)/$(OUT_NAME) /usr/local/bin/pgmE

## uninstall 
uninstall:
	sudo rm /usr/local/man/man1/pgmE.1.gz
	sudo rm /usr/local/bin/pgmE

## Build, run the executable
run: build
	$(BUILD_DIR)/$(OUT_NAME)

## Production build, run the exectuable
run/prod: build/prod
	$(PROD_DIR)/$(OUT_NAME)

## Debug build, run the executable with gdb
run/debug: build/debug
	gdb -ex=r $(BUILD_DIR)/$(OUT_NAME).debug

## Debug build, run the executable with valgrind to check for memory leaks
run/test: build/debug
	valgrind --leak-check=yes $(BUILD_DIR)/$(OUT_NAME).debug

## Build the executable
build: create_dir
	gcc $(COMPILE) $(BUILD_DIR)/$(OUT_NAME)

## Production build with optimisation 
build/prod: create_dir/prod
	gcc -O3 $(COMPILE) $(PROD_DIR)/$(OUT_NAME)

## Windows production build with optimisation 
build/prod/windows: create_dir/prod
	x86_64-w64-mingw32-gcc -O3 --static $(COMPILE) $(PROD_DIR)/$(OUT_NAME).exe

## Debug build with debug infos
build/debug: create_dir
	gcc -g3 $(COMPILE) $(BUILD_DIR)/$(OUT_NAME).debug

create_dir: 
	mkdir -p $(BUILD_DIR) 

create_dir/prod: 
	mkdir -p $(PROD_DIR) 

## Clean the directory
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(PROD_DIR)
	rm -f test.pgm

.PHONY: install uninstall run run/prod run/prod run/test build build/prod build/prod/windows build/debug clean
