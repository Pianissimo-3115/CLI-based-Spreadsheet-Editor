CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g

OBJ = main.o \
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
	@$(CC) $(CFLAGS) -c -o $@ $<

target/release/spreadsheet: $(OBJ)
	@$(CC) -o $@ $^ -lm 

run: target/release/spreadsheet
	@./target/release/spreadsheet $(a) $(b)

debug:
	@$(CC) -g $(SRC) -o target/release/spreadsheet.exe -lm
	@gdb target/release/spreadsheet.exe
	
clean:
	@rm -f target/release/spreadsheet target/release/spreadsheet.exe *.o report/report.pdf report/*.aux report/*.log report/*.bbl report/*.blg report/*.out report/*.toc report/*.lof report/*.lot report/*.nav report/*.snm report/*.vrb

test_%:
	@$(CC) $(CFLAGS) -o tests/test_$* AVL.c stack.c linkedlist.c hash_table.c evaluate_operations.c IO.c ./tests/test_$*.c -lm
	@./tests/test_$*
test:
	@$(CC) $(CFLAGS) -o tests/test_AVL AVL.c stack.c linkedlist.c hash_table.c evaluate_operations.c IO.c ./tests/test_AVL.c -lm
	@./tests/test_AVL
	@$(CC) $(CFLAGS) -o tests/test_stack AVL.c stack.c linkedlist.c hash_table.c evaluate_operations.c IO.c ./tests/test_stack.c -lm
	@./tests/test_stack
	@$(CC) $(CFLAGS) -o tests/test_linkedlist AVL.c stack.c linkedlist.c hash_table.c evaluate_operations.c IO.c ./tests/test_linkedlist.c -lm
	@./tests/test_linkedlist
	@$(CC) $(CFLAGS) -o tests/test_hash_table AVL.c stack.c linkedlist.c hash_table.c evaluate_operations.c IO.c ./tests/test_hash_table.c -lm
	@./tests/test_hash_table
	@$(CC) $(CFLAGS) -o tests/test_evaluate_operations AVL.c stack.c linkedlist.c hash_table.c evaluate_operations.c IO.c ./tests/test_evaluate_operations.c -lm
	@./tests/test_evaluate_operations
	@$(CC) $(CFLAGS) -o tests/test_IO AVL.c stack.c linkedlist.c hash_table.c evaluate_operations.c IO.c ./tests/test_IO.c -lm
	@./tests/test_IO
	@echo "All auto tests passed"
	@echo "Last test (IO test) is a manual test, please check the output"


report/report.pdf: report/report.tex
	pdflatex -output-directory=report report/report.tex
	bibtex report/report || true
	pdflatex -output-directory=report report/report.tex
	pdflatex -output-directory=report report/report.tex

report: report/report.pdf
