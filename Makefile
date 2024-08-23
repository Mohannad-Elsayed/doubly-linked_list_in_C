CC = gcc
CFLAGS = -Wall -Wextra -g

all:
	rm -r bin; mkdir bin
	$(CC) $(CFLAGS) test.c -o bin/test 
	$(CC) $(CFLAGS) example.c -o bin/example 
	x86_64-w64-mingw32-gcc -o bin/test-64.exe test.c
	x86_64-w64-mingw32-gcc -o bin/example-64.exe example.c
	i686-w64-mingw32-gcc -o bin/test-32.exe test.c
	i686-w64-mingw32-gcc -o bin/example-32.exe example.c

test:
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./bin/test

example:
	./bin/example

.PHONY: all test example