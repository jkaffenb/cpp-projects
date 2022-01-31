/************************************************************************
    File: sudokuboard.h
    Author: Jack Kaffenbarger
    Date: 3/3/19
    Assignment:  Sudoku

    solve any sudoku using backtracking and a linked list stack class

************************************************************************/
#include <cstdlib>

struct tuple {
  size_t row;
  size_t column;
  tuple(size_t r, size_t c) : row(r), column(c) {}
};

class sudokuboard {

 private:

  char board[9][9];

 public:

  sudokuboard(std::string all_rows);

  void print();
  //print board

  char get(size_t r, size_t c);
  //get value at position

  void place(size_t r, size_t c, char n);
  //place value at position

  void remove(size_t r, size_t c);
  // change to '_' at position

  bool can_place(size_t r, size_t c, size_t n);
  // true iff the board would allow placing
  // n at (r,c)

  tuple most_constrained();
  //find most constrained square on the board

  bool solved(); // true iff there are no blank spots on the board

};
