/******************************************
* list.cc
* (Stub by Alistair Campbell)
* rev. 2019.03
*
* NAME: Jack Kaffenbarger
* DATE: 4/4/19
*
********************************************/

#include "list.h"

// List node constructors provided by Prof. Campbell

list::node::node() : prev(nullptr), next(nullptr) {}

list::node::node(const element & d) : prev(nullptr), data(d), next(nullptr) {}

list::node::node(node *p, node *n) : prev(p), next(n) {}

list::node::node(node *p, const element & d, node * n):
  prev(p), data(d), next(n) {}

// List constructors/destructor/assignment also provided.
// No need to change these.

list::list()
{
  _init();
}

list::~list()
{
  _destroy();
}

list::list(const list & orig)
{
  _copy(orig);
}

list & list::operator=(const list & rhs)
{
  if (this != &rhs) {
    _destroy();
    _copy(rhs);
  }
  return *this;
}

void list::_init()
{
  _front = new node(nullptr, new node(nullptr, nullptr));
  _rear = _current = _front -> next;
  _rear -> prev = _front;
  _current_index = 0;
  _size = 0;
}

void list::_copy(const list & orig)
{
  _init();
  for(size_t i=0; i<orig.size(); i++){
    size_t k = orig.get(int(i));
    add(k, i);
  }
  return;
}

void list::_destroy()
{
  node * next = _front;
  while (_front -> next) {
  next = _front -> next;
  delete _front;
  _front = next;
}
  delete _current;
  _size = 0;

  return;
}

void list::add(const element & item, int index)
{
  int k = index;
  if (index < 0) k += _size;
  if (k < 0) k = 0;

  k = size_t(k);
  list::_set_current_index(k);

  node * baby = new node(_current->prev, item, _current);
  _current = baby->next->prev = baby->prev->next = baby;
  _size++;
  return;
}

void list::remove_at(int index)
{
  size_t k = size_t(index);
  if(index < 0) k += _size;
  list::_set_current_index(size_t(k));
  node * gone = _current;
  _current->next->prev = _current->prev;
  _current = _current -> prev -> next = _current -> next;
  delete gone;
  _size --;
  return;
}

void list::remove(const element & item)
{
  for(size_t i=0; i<_size; i++){
    if(list::get(i) == item){
      list::remove_at(i);
      return;
    }
  }
  return;
}

size_t list::find(const element & item, size_t start_index) const
{
  for(size_t i =start_index; i<_size; i++)
    if(list::get(i) == item) return i;
  return list::size();
}

list::element list::get(int index) const
{
  list::_set_current_index(size_t(index));
  return _current -> data;
}

size_t list::size() const
{
  return _size;
}

void list::output(std::ostream & ostr) const
{
  ostr << '<';
 for (node * p = _front->next; p != _rear; p = p->next) {
   ostr << p->data;
   if (p->next != _rear)
     ostr << ", ";
 }
 ostr << '>';
}

void list::_set_current_index(size_t index) const
{
  node *temp = _front;
  size_t count = 0;

  // First checks if index is between front and _current
  if (index <= _current_index){
    // Then checks if index is closer to front or _current, and increments
    // accordingly
    if (index > (_current_index / 2)){
      count = _current_index;
      temp = _current;
      while (count != index){
        temp = temp -> prev;
        count--;
      }
      _current = temp;
      _current_index = index;
      return;
    }
    else{
      // Closer to front
      temp = _front-> next;
      count = 0;
      while (count != index){
        temp = temp -> next;
        count++;
      }
      _current = temp;
      _current_index = index;
      return;
    }

  }

  // Now that we know the index is between _current and the rear, checks from
  // which side to start incrementing from
  else{
    // Closer to rear
    if (index > (_current_index + (_size - _current_index) / 2)){
      count = _size;
      temp = _rear;
      while (count != index){
        temp = temp -> prev;
        count--;
      }
      _current = temp;
      _current_index = index;
      return;
    }
    else
    // Closer to _current
      count = _current_index;
      temp = _current;
      while (count != index){
        temp = temp -> next;
        count++;
      }
      _current = temp;
      _current_index = index;
      return;
  }
}
