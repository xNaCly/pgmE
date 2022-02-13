main:
	gcc -fdiagnostics-color=always -Wall -Wpedantic -std=c99 src/main.c src/libs/util/_util.c src/libs/pgm/_pgm.c src/libs/image/_image.c -lm -o build/main.out
	build/main.out
clean:
	rm -r build/
	rm *.pgm
pre:
	mkdir build/
