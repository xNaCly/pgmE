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
						-O3
						
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

# the previously built executable
run: main
	$(BUILD_DIR)/main.out

# compile the executable
main: pre
	gcc $(COMPILE)

# compiles executable with debugging info and runs it with the GNU-debugger (gdb)
debug: pre
	gcc -g3 $(COMPILE) 
	gdb $(BUILD_DIR)/main.out

# creates build dir, only if its not created yet
pre: 
	mkdir -p $(BUILD_DIR) 

# removes build and test files/dirs
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) 
	rm -f test.pgm
