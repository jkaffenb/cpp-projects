/******************************************************************************
precompression.cc
Skeleton for precompression lab exercise
Spring 2019

Skeleton by Alistair Campbell
Implementations by
******************************************************************************/

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <fstream>

// Forward declarations
void error(std::string msg, int code = 1);
struct hnode;
struct node;

// To be implemented in step 3
void insert(node * & n, hnode *p);

// To be implemented in step 5
void traverse(hnode *n, std::string code, std::string *codes);

// End of forward declarations

// Structure for building a Huffman tree for compression
struct hnode {
  int character;
  size_t count;
  hnode *left;
  hnode *right;
  hnode(int ch, size_t co, hnode *lft, hnode *rgt):
    character(ch), count(co), left(lft), right(rgt) {}
};

// Structure for a linked list of hnode pointers
struct node {
  hnode *data;
  node *next;
};



int main(int argc, char **argv)
{
  int ary[256];
  for (size_t i=0; i < 256; i++){
    ary[i] = 0;
  }
  if (argc != 2)
    error(std::string("USAGE: ") + argv[0] + " FILENAME");
  std::ifstream in(argv[1]);
  if (!in)
    error(std::string("Can't open file ") + argv[1]);
  while (true) {
    int ch = in.get();
    if (!in) break;
    // The following line may be deleted or modified.
    //std::cout << static_cast<char>(ch) << std::endl;
    ary[ch]++;
  }
  size_t diff_char_count = 0;
  size_t total_char_count = 0;
  for (size_t i = 0; i < 256; i++){
    if (ary[i] > 0) {
      std::cout << ary[i] << std::endl;
      diff_char_count++;
      total_char_count += ary[i];
    }
  }
  std::cout << "---" << '\n';
  std::cout << diff_char_count << '\n';
  std::cout << total_char_count << '\n';
}

bool is_less(hnode * const & a, hnode * const & b)
{
  // Decide whether a should come before b.
  return a->count < b->count or (a->count == b->count and
                                 a->character < b->character);
}

void insert(node * & n, hnode *p)
{
  // insert p into the linked list dominated by n, in the correct position
  // Delete this comment and line:
  //assert(&n == &n and &p == &p);
  node * prev = nullptr;
  while (n->next){
    if (is_less(p, n->data)){
      node *baby = new node(p, n);
      prev-> next = baby;
      n-> next = prev;
      return;
    }
    prev-> next = n;
    n=n-> next;
  }
  return;
}


void traverse(hnode *n, std::string code, std::string *codes)
{
    // At a leaf, store code in codes[character]
    // Recursive calls add "0" or "1" to code
    assert(&n==&n and &code == &code and &codes == &codes);
}

void error(std::string msg, int code)
{
  std::cerr << msg << std::endl;
  exit(code);
}



//.--- -- .---
