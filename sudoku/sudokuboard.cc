/************************************************************************
    File: sudokuboard.cc
    Author: Jack Kaffenbarger
    Date: 3/5/19
    Assignment:  Sudoku

    solve any sudoku using backtracking and a linked list stack class

************************************************************************/
#include <cstdlib>
#include <iostream>
#include "sudokuboard.h"

sudokuboard::sudokuboard(std::string all_rows)
{
  for(size_t i = 0; i<9; i++){
    for(size_t j = 0; j < 9; j++){
      board[i][j] = all_rows[i * 9 + j];
    }
  }
}

void sudokuboard::print()
{
  for(size_t i = 0; i<9; i++){
    for(size_t j = 0; j<9; j++){
      std::cout << board[i][j];
    }
    std::cout << std::endl;
}
}

char sudokuboard::get(size_t r, size_t c)
{
  return board[r][c];
}

void sudokuboard::place(size_t r, size_t c, char n)
{
  board[r][c] = n;
}

void sudokuboard::remove(size_t r, size_t c)
{
  board[r][c] = '_';
}

bool sudokuboard::can_place(size_t r, size_t c, size_t n)
{
  if(n > 9) return false;
  char num = '0' + n;
  //CITE: Dan Comey
  //DESC: smart way of converting a size_t to char

  if(board[r][c] != '_'){
    //std::cout << "place" << std::endl;
      return false;
  }

  for(size_t i = 0; i < 9; i ++){
    if(board[r][i] == num){
      return false;
    }

    if(board[i][c] == num ){
      return false;
    }


}
size_t starting_box_r = r / 3 * 3;  //could be more effiecient if you start from
size_t starting_box_c = c / 3 * 3;  //middle of box instead of doubly checking
for(size_t j = 0; j < 3; j++){      //the top and left side edges of the box
  for(size_t k = 0; k < 3; k++){    // will change if time
  if(board[starting_box_r + j][starting_box_c +k] == num){
    return false;
  }
  }
}

return true;

}

tuple sudokuboard::most_constrained(){
  //run through board
  //if '_'
  //run thorugh 0-9 each time onec an be placed, add one to the count once loops
  //finished, if count ==1 return tuple, if count < lowest count, store lowest
  size_t cur_count = 0;
  size_t lowest_count = 10;
  size_t low_c = 10;
  size_t low_r = 10;
  for(size_t r = 0; r < 9; r++){
    for(size_t c = 0; c < 9; c++){
      if(board[r][c] == '_'){
        cur_count = 0;
        for(size_t i = 1; i < 10; i++){
          if(sudokuboard::can_place(r, c, i)){
            cur_count++;
              }
          if(i == 9){
            if(cur_count == 0){
              lowest_count = cur_count;
              low_c = c;
              low_r = r;
              return tuple (low_r, low_c);
            }
            if(cur_count < lowest_count){
              lowest_count = cur_count;
              low_c = c;
              low_r = r;
              cur_count = 0;
            }
          }
        }
      }
    }
  }
  return tuple (low_r, low_c);
}



bool sudokuboard::solved(){
  // true iff there are no blank spots on the board
  // run through board, if == _ return false
for(size_t i = 0; i < 9; i ++){
  for (size_t j = 0; j < 9; j ++){
    if(board[i][j] == '_')
      return false;
  }
}
  return true;
}
