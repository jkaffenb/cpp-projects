/************************************************************************
    File: randwrite.cc
    Author: Jack Kaffenbarger
    Date: 4/18/19
    Assignment:  Random Writer

    Produces random text based on character possiblilites
************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "list.h"
using namespace std;

void error(std::string msg)
{
  // Write a message on the standard error stream
  // and exit.
  std::cerr << msg << std::endl;
  exit(1);  // non-zero indicates an error.
}


int main(int argc, char **argv)
{
  // Make sure correct amount of commands were put in
  if (argc != 5)
    error(std::string("Usage: ") + argv[0] + " FLENAME");
  list mylist;

  // Make sure file is openable
  std::ofstream out(argv[4]);
  if (!out)
    error(std::string("Trouble opening file: ") + argv[4]);

  // Make sure no negative inputs for k and length
  if (atoi(argv[2]) < 0 or atoi(argv[3]) < 0){
    error(std::string("No negative inputs: "));
  }
  size_t k = atoi(argv[2]);
  size_t length = atoi(argv[3]);
  std::ifstream textstream(argv[1]);

  // Make sure the file was opened properly
  if (!textstream)
    error(std::string("Trouble opening file: ") + argv[1]);

  while (true) {  // loop-and-a-half to read characters
    int v = textstream.get();
    if (!textstream)
      break;
    mylist.add((char)v, mylist.size());
  }

  // Make sure that k is smaller than the size of mylist
  if (mylist.size() <= k){
    error(std::string("k is too large: "));
  }

  // Intialize lists used and a random starting place
  size_t random_start_place = rand() % mylist.size();
  list seed_list;
  list pos_next_letter;

  // Create original list
  for (size_t i = 0; i < k; i++){
    seed_list.add(mylist.get(random_start_place + i), seed_list.size());
    out.put(mylist.get(random_start_place + i));
  }
  // While loop that runs through until the length is fulfilled
  size_t check_count = 0;
  size_t loop_count = k;
  while (loop_count < length){
    // Runs through the entire list
    for (size_t j = 0; j < mylist.size() - seed_list.size(); j++){
      check_count = 0;
      // If the letter matchs k[0], check the remaining characters
      if (mylist.find(seed_list.get(0), j) != mylist.size()){
        j = mylist.find(seed_list.get(0), j);
        // Make sure the loop won't go out of bounds
        if (j + k > mylist.size()) break;
        for (size_t l = 0; l < k; l++){
          if (mylist.get(j + l) == seed_list.get(l)){
            check_count++;
          }
        }
        // If all the characters match, add the next character to pos_next_letter
        if (check_count == k){
          pos_next_letter.add(mylist.get(j + k), 0);
        }
      }

    }
    // If no possible next letter, find a new random seed and change
    // length accordingly
    if (pos_next_letter.size() == 0){
      while (seed_list.size() > 0){
        seed_list.remove_at(0);
      }
      random_start_place = rand() % mylist.size();
      for (size_t i = 0; i < k; i++){
        seed_list.add(mylist.get(random_start_place + i), seed_list.size());
        out.put(mylist.get(random_start_place + i));
        loop_count++;
      }
    }
    // If there are possible next letters, randomly choose one and increment
    // length
    else {
      loop_count++;
      int next_seed_letter = pos_next_letter.get(rand() % pos_next_letter.size());
      out.put(next_seed_letter);
      seed_list.add(next_seed_letter, seed_list.size());
      seed_list.remove_at(0);
      while (pos_next_letter.size() > 0){
        pos_next_letter.remove_at(0);
      }
    }
  }
  // This prevents a weird error I was getting for some reason, not really sure
  // why
  mylist.get(0);
  seed_list.get(0);
  pos_next_letter.get(0);
  return 0;
}
