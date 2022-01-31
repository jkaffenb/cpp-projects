sudoku: sudoku.o sudokuboard.o stack.o
	g++ -o  sudoku sudoku.o sudokuboard.o stack.o

sudoku.o: sudoku.cc sudokuboard.h stack.h
	g++ -c  sudoku.cc

sudokuboard.o: sudokuboard.cc sudokuboard.h
	g++ -c  sudokuboard.cc

stack.o: stack.cc stack.h
	g++ -c stack.cc

clean:
	rm -f *.o sudoku
