CC = gcc
CFLAGS = -Wall -Wextra -g

all:
	rm -r bin || mkdir bin
	$(CC) $(CFLAGS) test.c -o bin/test 
	$(CC) $(CFLAGS) example.c -o bin/example 
	i686-w64-mingw32-gcc -o bin/test.exe test.c
	i686-w64-mingw32-gcc -o bin/example.exe example.c

test:
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./bin/test

example:
	./bin/example

.PHONY: all test example