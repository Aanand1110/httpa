CC = gcc
CFLAGS = -Wall -Wextra -I.

TARGET = client
SRC = $(shell find . -name '*.c')
OBJ = $(SRC:.c=.o)

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
