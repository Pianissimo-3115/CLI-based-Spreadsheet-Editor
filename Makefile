CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g

OBJ = main.c \
	linkedlist.o \
	AVL.o \
	stack.o \
	hash_table.o \
	evaluate_operations.o \
	IO.o


SRC = main.c \
	linkedlist.c \
	AVL.c \
	stack.c \
	hash_table.c \
	evaluate_operations.c \
	IO.c

DEPS = cell_operations.h data_structures.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

sheet: $(OBJ)
	$(CC) -o $@ $^

run: sheet
	./sheet $(a) $(b)

debug:
	gcc -g main.c linkedlist.c AVL.c stack.c hash_table.c evaluate_operations.c IO.c -o sheet.exe
	gdb sheet.exe
	
clean:
	rm -f sheet sheet.exe *.o

