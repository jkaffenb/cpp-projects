/************************************************************************
    File: testseq.cc
    Author: Alistair Campbell
    Date: August 30, 2015

    A test program for sequences.  Modify this as much as you
want to thoroughly test your sequence implementation.
************************************************************************/
#include <iostream>
#include <cstdlib>
#include "sequence.h"



int main()
{
  std::cout << "print an empty sequence" << std::endl;
  sequence s1;
  std::cout << s1.size() << std::endl;
  s1.print();
  std::cout << std::endl << std::endl;

  std::cout << "Add a number and print" << std::endl;
  s1.add(4);
  s1.add(4);
  s1.add(4);
  s1.add(4);


  s1.print();
  std::cout << "" << std::endl;
  std::cout << s1.getLongestRun();
  std::cout << std::endl << std::endl;
  //
  // std::cout << "Add a couple more to the left and right" << std::endl;
  // s1.add(90);
  // s1.add(451, 0);
  // s1.print();
  // std::cout << std::endl << std::endl;
  //
  // std::cout << "Elements at each position:" << std::endl;
  // for (size_t i = 0; i < s1.size(); i++)
  //   std::cout << s1.get(i) << std::endl;
  // std::cout << std::endl;
  //
  // std::cout << "Empty?" << std::endl;
  // if (s1.empty())
  //   std::cout << "Empty." << std::endl;
  // else
  //   std::cout << "Not Empty." << std::endl;
  // std::cout << std::endl;
  //
  // std::cout << "Runs?" << std::endl;
  // size_t pos = s1.getLongestRun();
  // if (pos==s1.size()) {
  //   std::cout << "No runs in "; s1.print(); std::cout << std::endl;
  // }
  // else {
  //   std::cout << "Longest run of "; s1.print(); std::cout << " at " << pos << std::endl;
  // }
  // std::cout << std::endl;
  //
  // std::cout << "Filling it up..." << std::endl;
  // while (not s1.full())
  //   s1.add(0);
  // s1.print();
  // std::cout << std::endl << std::endl;
  //
  // std::cout << "Runs NOW?" << std::endl;
  // pos = s1.getLongestRun();
  // if (pos==s1.size()) {
  //   std::cout << "No runs in "; s1.print(); std::cout << std::endl;
  // }
  // else {
  //   std::cout << "Longest run of "; s1.print(); std::cout << " at " << pos << std::endl;
  // }
  // std::cout << std::endl;

  // std::cout << "Clear it." << std::endl;
  // s1.clear();
  // s1.print();
  // std::cout << std::endl << std::endl;
  //
  // std::cout << "Empty?" << std::endl;
  // if (s1.empty())
  //   std::cout << "Empty." << std::endl;
  // else
  //   std::cout << "Not Empty." << std::endl;
  // std::cout << std::endl;

  // std::cout << "A random interaction" << std::endl;
  // srandom(time(NULL));  // a new random sequence each time we run it!
  // for (size_t i = 0; i < 50; i++) {
  //   s1.print();
  //   std::cout << std::endl;
  //   int v;
  //   size_t p;
  //   size_t choice = random() % 6;
  //   if (choice < 3) {
  //     if (s1.full())
	// continue;
  //     v = 1 + random() % 6; // number cube roll.  :-)
  //     p = random() % (s1.size() + 1);
  //     std::cout << "Adding " << v << " at position " << p << std::endl;
  //     s1.add(v, p);
  //   }
  //   else if (choice == 3) {
  //     if (s1.empty())
	// continue;
  //     p = random() % (s1.size());
  //     std::cout << "Removing at position " << p << std::endl;
  //     s1.remove(p);
  //   }
  //   else if (choice == 4) {
  //     if (s1.empty())
	// continue;
  //     v = 1 + random() % 6; // number cube roll.  :-)
  //     p = random() % (s1.size());
  //     std::cout << "Replacing with " << v << " at position " << p << std::endl;
  //     s1.replace(v, p);
  //   }
  //   else {
  //     std::cout << "Longest run of list with size " << s1.size() << " at "
	//    << s1.getLongestRun() << std::endl;
  //   }
  //   s1.print();
  //   std::cout << std::endl;
  // }

  return 0;
}
