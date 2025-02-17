CC = gcc

OBJ = linkedlist.o \
	AVL.o \
	stack.o \
	hash_table.o \
	IO.o \
	IOtest.o \
	main.o

SRC = linkedlist.c \
	AVL.c \
	stack.c \
	hash_table.c \
	IO.c \
	IOtest.c \
	main.c

DEPS = cell_operations.h data_structures.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

sheet: $(OBJ)
	$(CC) -o $@ $^

run: sheet
	./sheet $(a) $(b)

clean:
	rm -f *.o
	rm -f sheet
