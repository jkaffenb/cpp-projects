/************************************************************************
    File: sudoku.cc
    Author: Jack Kaffenbarger
    Date: 3/5/19
    Assignment:  Sudoku

    solve any sudoku using backtracking and a linked list stack class

************************************************************************/


#include <iostream>
#include <cstdlib>
#include "sudokuboard.h"
#include "stack.h"


void solve_it(sudokuboard & board){
  stack stack1;

  size_t row = 10;
  size_t col = 10;
  //size_t try_count = 0;
  row = board.most_constrained().row;
  col = board.most_constrained().column;
  size_t temp = 0;

  //run until the board is solved
  while(!board.solved()){
    for(size_t i = 1; i < 11; i++){
      //loop through all possible values at the most constrained spot, keep
      //track of each new number added to the board
      if(board.can_place(row, col, i + temp)){
        stack1.push(row);
        stack1.push(col);
        stack1.push(i + temp);
        char num = '0' + i + temp;
        board.place(row, col, num);
        row = board.most_constrained().row;
        col = board.most_constrained().column;
        if(board.solved()){
          //checks to make sure the board isnt solved every time a num is placed
          board.print();
          return;
        }
        temp = 0;
        break; //cite miles
        //CITE: Miles Wyner
        //DESC: suggested using a break statement to avoid an infinite loop with
        //backtracking
      }
      if(i + temp > 9){
        //if no possible values, go back to the previous inputted value and try
        //all other values, rinse and repeat
        temp = stack1.top();
        stack1.pop();
        col = stack1.top();
        stack1.pop();
        row = stack1.top();
        stack1.pop();
        board.place(row, col, '_');
        break;
      }
    }
  }
}

int main()
{
    std::string row;
    std::string all_rows;
    // read each row and append to the string of all rows
    for (size_t r = 0; r < 9; r++){
      std::cin >> row;
      all_rows += row;
    }

    //create board and run solve function
    sudokuboard board(all_rows);
    if(board.solved()){
      board.print();
      return 0;
    }
    solve_it(board);
    return 0;

}
