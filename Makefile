CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

OBJ = main.c \
	linkedlist.o \
	AVL.o \
	stack.o \
	hash_table.o \
	IO.o


SRC = main.c \
	linkedlist.c \
	AVL.c \
	stack.c \
	hash_table.c \
	IO.c

DEPS = cell_operations.h data_structures.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

sheet: $(OBJ)
	$(CC) -o $@ $^

run: sheet
	./sheet $(a) $(b)

clean:
	rm *.o
	rm sheet.exe
