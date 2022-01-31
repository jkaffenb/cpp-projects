/************************************************************************
    File: stack.h
    Author: Jack Kaffenbarger
    Date: 3/5/19
    Assignment:  Sudoku

    Implementation of a simple linked list stack class

************************************************************************/

#include <cstdlib>

struct node {
  size_t data;
  node *next;
  node(size_t d, node * n) {
    data = d;
    next = n;
  }
};

class stack {
private:
  // Data:
  node *_top;
  size_t *data;

public:
  stack();
  void push(const size_t & item);
  void pop();
  size_t top() const;

};
