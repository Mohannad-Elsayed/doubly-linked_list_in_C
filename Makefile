CC = gcc
CFLAGS = -Wall -Wextra -g

test: test.c
	$(CC) $(CFLAGS) -o test $^
	./test
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./test

example: example.c
	$(CC) $(CFLAGS) -o example $^
	./example

benchmark: benchmark.c
	$(CC) $(CFLAGS) -o benchmark $^
	./benchmark

clean:
	rm -f test example tempCodeRunnerFile.c 

.PHONY: all clean test example