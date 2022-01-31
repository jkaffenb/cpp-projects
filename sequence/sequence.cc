/************************************************************************
    File: sequence.cc
    Author: Jack Kaffenbarger
    Date: 2/14/19
    Assignment:  Sequence

    Implementation of a simple array-based sequence class.

************************************************************************/
#include <iostream>
#include "sequence.h"

/*** Constructor ***/
sequence::sequence()
{
  // Initializes this sequence with 0 elements
  _size = 0;
}

/*** const member functions ***/


size_t sequence::size() const
{
  // return the number of elements in this sequence
  return _size;
}

bool sequence::empty() const
{
  // return true if this sequence has no elements, false otherwise.
  if(sequence::size() == 0)
    return true;
  return false;
}

bool sequence::full() const
{
  // return true if this sequence has _capacity elements, false otherwise.
  if(sequence::size() == _capacity)
    return true;
  return false;
}

void sequence::print() const
{
  // Produce output with std::cout: a single open square bracket, the elements
  // of the sequence, separated by commas and spaces, followed by a single
  // close square bracket.  No newline.
  // Examples of output:
  //  []
  //  [6]
  //  [9, -1, 4]
  //std::cout << "size is " << sequence::size() << std::endl;
  if(sequence::size() == 0){
    std::cout << "[]";
    return;
  }
  if(sequence::size() == 1){
    std::cout << "[";
    std::cout << _data[0];
    std::cout << "]";
    return;
  }

  std::cout << "[";

  for(size_t i = 0; i < _size; i++){
    if(i + 1 == _size){
      std::cout << _data[i];
      std::cout << "]";
      return;
    }
    std::cout << _data[i];
    std::cout << ",";
    std::cout << " ";
  }


}

int sequence::get(size_t position) const
{
  // Precondition:  position < size()
  // Return the element at the given position.
  return _data[position];

}

size_t sequence::getLongestRun() const
{
  // Determine the length of the longest run of two or more identical adjacent
  // elements of this sequence.  Return the smallest starting position of a
  // run with this length.  If no such run occurs, return size().
  // (This method may use auxiliary stand-alone functions, but, again, you
  // cannot change this  file.  This means that you cannot define auxiliary
  // methods.)
  size_t longestrun = 1;
  size_t currentrun = 0;
  size_t position = 0;

  //for loop that keeps the current run, and if broken and larger than the
  //longest run replaces it. If the run is not broken but the loop runs to the
  //end, slightly different if statement to get the correct position
  for(size_t i = 1; i < sequence::size(); i++){
    if (_data[i] == _data[i-1]){
      currentrun += 1;
      if (i == sequence::size() - 1){
        if (currentrun > longestrun){
          //std::cout << position << std::endl;
          longestrun = currentrun + 1;
          position = i - longestrun + 1;
        }
      }

    }
    if (_data[i] != _data[i-1]){
      if (currentrun > longestrun){
        longestrun = currentrun;
        position = i - longestrun - 1;
      }
      currentrun = 0;
    }
  }

//if there is no longest run, return the size, otherwise, return the position
//of the longset run
  if(longestrun < 2)
    return sequence::size();
  return position;
}

/*** non-const member functions ***/


void sequence::add(int item)
{
  // Preconditions:
  //   The sequence has N elements.
  //   N != _capacity;
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ...VN-1]
  // Adds item to the end of the sequence.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, ..., VN-1, item];
  //   size() == N+1.
  // if (sequence::size() == 0){
  //   std::cout << _data[0] << std::endl;
  //   _data[0] += item;
  //   _size += 1;
  //   return;
  // }

  _data[sequence::size()] = item;
  _size += 1;
}

void sequence::add(int item, size_t position)
{
  // Preconditions:
  //   The sequence has N elements.
  //   N != capacity;
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ..., Vposition,... VN-1];
  //   position <= size()
  // Inserts item at the given position.  All elements with indices at position
  // or greater are shifted to the right.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, V2, ..., item, Vposition,..., VN-1];
  //   size() == N+1
  for(size_t i = sequence::size() + 1; i > position ; i -= 1){
    _data[i] = _data[i - 1];
  }
  _data[position] = item;
  _size += 1;

}

void sequence::remove(size_t position)
{
  // Preconditions:
  //   The sequence has N elements
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1,  ..., Vposition-1, Vposition, Vposition+1, ... VN-1];
  //   0 <= position and position < N
  // The item at the given position is discarded.  All elements with greater
  // indices are shifted to the left.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, ..., Vposition-1, Vposition+1, ..., VN-1]
  //   size() == N-1.
  for(size_t i = position; i < sequence::size() - 1; i++){
    _data[i] = _data[i + 1];
  }
  _size -= 1;
}


void sequence::replace(int newitem, size_t position)
{
  // Preconditions:
  //   The sequence has N elements.
  //   0 <= position < N
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ..., Vposition,... VN-1];
  // Replaces the item at the given position with the given new item.
  // Postcondition:
  //   The sequence contains elements
  //     [V0, V1, V2, ..., newitem,... VN-1];
  //   size() == N  (unchanged)
  _data[position] = newitem;

}

void sequence::clear()
{
  // Remove all elements from the sequence.
  // Postcondition:
  //   size() == 0
  _size = 0;
}
