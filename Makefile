CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

test: test.c
	$(CC) $(CFLAGS) -o test $^
	./test

example: example.c
	$(CC) $(CFLAGS) -o example $^
	./example

benchmark: benchmark.c
	$(CC) $(CFLAGS) -o benchmark $^
	./benchmark

clean:
	rm -f test example tempCodeRunnerFile.c 

.PHONY: all clean test example