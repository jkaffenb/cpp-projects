/************************************************************************
    File: stack.cc
    Author: Jack Kaffenbarger
    Date: 3/5/19
    Assignment:  Sudoku

    Implementation of a simple linked list stack class

************************************************************************/

#include <iostream>
#include "stack.h"

stack::stack()
{
  _top = nullptr;
}

void stack::push(const size_t & item)
{

  _top = new node(item, _top);
}

void stack::pop()
{
 node *baby = _top;
 _top = _top -> next;
 delete baby;
}

size_t stack::top() const
{

  return _top -> data;
}
