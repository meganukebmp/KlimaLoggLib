SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)
PROG = parsefile

CC = gcc
CFLAGS = -Wall -std=c99 -Wall -pedantic -MD
LDFLAGS = 
INCLUDE = -Iinclude

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(PROG) $(DEP) $(PROG).exe

-include $(DEP)