all: 
	gcc-4.7 -std=gnu++11 sudoku.cpp -O3 -lstdc++ -o sudoku
clean:
	rm sudoku
