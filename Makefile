CC = gcc
CFLAGS = -Wall -Wextra -I./src

SRC = test.c src/doubly_linked_list.c
OBJ = $(SRC:.c=.o)

# Output binary
TARGET = test_program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all
