SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)
PROG = program.exe

CC = gcc
CFLAGS = -Wall -std=c99 -Wall -pedantic
LDFLAGS =
INCLUDE = -Iinclude

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $<  $(LDFLAGS)

.PHONY: clean
clean:
	rm $(OBJ) $(PROG)