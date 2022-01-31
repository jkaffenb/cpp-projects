/******************************************************************************
 *
 * Name:        Jack Kaffenbarger
 *
 * Date:        DATE IT'S DONE
 *
 * Assignment:  Huffman Compression
 *
 * Description:  Takes data from filename, encodes it using Huffman coding,
 *               writes the result to standard output. Also able to reverse.
 *
 ******************************************************************************/
#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "pq.h"

struct hnode {
  int character;
  size_t count;
  hnode *left;
  hnode *right;
  hnode(int character, size_t count,
	      hnode *left=NULL, hnode *right=NULL) :
    character(character), count(count), left(left), right(right) {}
};

int hnode_cmp(hnode * const & a, hnode * const & b)
{
  // Simple comparison function.
  if (a->count == b->count && a->character == b->character) return 0;
  if (a->count == b->count && a->character > b->character) return 1;
  if (a->count == b->count && a->character < b->character) return -1;
  return a->count < b->count ? -1 : 1;
}

bool show_bits = true;

std::string byte_to_bits(int byte)
{
  // Converts one byte to an eight-bit string
  std::string result = "";
  size_t i;
  int v;
  for (i = 0, v = 128; i < 8; i++, v /=2)
    if (byte >= v) {
      result += '1';
      byte -= v;
    }
    else
      result += '0';
  return result;
}

void get_counts(size_t * counts, size_t & size, std::istream & in)
{
  // Get the number of instances of each character and add it to an array
  while (true) {
    int ch = in.get();
    if (!in) break;
    counts[ch]++;
    size++;
  }
}

hnode * make_tree(size_t * counts)
{
  // Given an array, make a minheap of hnodes
  priority_queue<hnode *> queue(hnode_cmp);
  for (size_t i=0; i < 256; i++){
    if (counts[i] > 0) queue.add(new hnode(char(i), counts[i],
    nullptr, nullptr));
  }

  // Given a min heap of hnodes, create a single huffman tree
  while (queue.size() > 1){
    hnode *temp = queue.front();
    queue.remove();
    queue.add(new hnode(temp -> character, temp -> count +
                        queue.front() -> count, temp, queue.front()));
    queue.remove();
  }

  hnode *result = queue.front();
  queue.remove();
  return result;
}

bool has_children(hnode *root)
{
  // Check if a subtree has children
  if ((root->left) or (root->right)) return true;
  return false;
}

void make_codes(hnode *tree, std::string *codes, std::string code="")
{
  // Make an array with the pathways for each leaf on the huffman tree
  if (!has_children(tree)){
    codes[(unsigned char)tree->character] = code;
    return;
  }
  make_codes(tree -> left, codes, code + "0");
  make_codes(tree -> right, codes, code + "1");
}

void write_tree(hnode * tree, std::ostream & ostr)
{
  // Take a huffman tree and recursively write it to the standard output
  if (!tree) return;

  if (has_children(tree)){
    std::cout << "I";
    write_tree(tree->left, ostr);
    write_tree(tree->right, ostr);
  }

  if (!has_children(tree)){
    std::cout << "L" << char(tree->character);
    return;
  }
}

hnode * read_tree(std::istream & istr)
{
  // Opposite of write_tree
  int v = istr.get();
  if (v == 'L') return new hnode(istr.get(), 0, nullptr, nullptr);
  hnode *left = read_tree(istr);
  hnode *right = read_tree(istr);
  return new hnode(left -> character, 0, left, right);
}

int bits_to_byte(std::string bitstr)
{
  // Convert an 8-bit string to a single byte
  int result = 0;
  int v = 128;
  for (size_t i = 0; i < 8; i++){
    if (bitstr[i] == '1') result += v;
    v /= 2;
  }
  return result;
}

void write_compress(std::istream & in, std::string * codes, std::ostream & cout)
{
  // Write the full compression to the standard output
  std::string buffer = "";
  std::string bitstr = "";
  while (true) {
    int ch = in.get();
    if (!in) break;
    buffer += codes[ch];
    if (buffer.size() >= 8){
      bitstr = buffer.substr(0, 8);
      buffer = buffer.substr(8);
      cout << static_cast<char>(bits_to_byte(bitstr));
      }
    }
    // If the entire string isn't divisible by 8, add buffer zeros to the last
    // byte
    if (buffer.size() != 0){
      for (size_t i = buffer.size(); i < 8; i++){
        buffer += "0";
      }
      cout << static_cast<char>(bits_to_byte(buffer));
  }
}

void compress(char *filename)
{
  // Compress a file
  std::ifstream in(filename);
  size_t counts[256] = { }; // initializes all to zero.
  size_t file_size;
  get_counts(counts, file_size, in);
  in.close();

  if (file_size == 0)
    return;

  hnode * tree = make_tree(counts);

  std::string codes[256];
  make_codes(tree, codes);
  std::cout << file_size;
  write_tree(tree, std::cout);
  in.open(filename);
  write_compress(in, codes, std::cout);
}

void uncompress()
{
  // Uncompress a compressed file
  if (std::cin.peek() == EOF)
    return;  // handle empty file
  size_t file_size;
  std::cin >> file_size;
  hnode *tree = read_tree(std::cin);
  size_t count = 0;
  hnode * current_hnode = tree;
  std::string current_bitstr = "";

  while (count < file_size){
    std::string current_bitstr = byte_to_bits(std::cin.get());
    for (size_t i = 0; i < 8; i++){
      if(count == file_size) break;
      if (current_bitstr.substr(i, 1) == "0"){
        current_hnode = current_hnode -> left;
        if (!has_children(current_hnode)){
          std::cout << (char)current_hnode -> character;
          current_hnode = tree;
          count ++;
        }
      }
      if (current_bitstr.substr(i, 1) == "1"){
        current_hnode = current_hnode -> right;
        if (!has_children(current_hnode)){
          std::cout << (char)current_hnode -> character;
          current_hnode = tree;
          count++;
        }
      }
    }
  }
}

/* DON'T MODIFY BELOW */

bool ends_with(const std::string & str, const std::string & suffix)
{
  return str.size() >= suffix.size() and
    str.substr(str.size()-suffix.size()) == suffix;
}

bool is_compress(const std::string & command)
{
  return ends_with(command, "compress") and
    not ends_with(command, "uncompress");
}

int main(int argc, char **argv)
{
  assert(argc==argc);
  if (is_compress(argv[0]))
    if (std::string(argv[1])=="-b") {
      show_bits = true;
      compress(argv[2]);
    }
    else
      compress(argv[1]);
  else
    uncompress();
}
