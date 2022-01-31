/******************************************************************************
*                                                                             *
* wordfind.cc                                                                 *
* Jack Kaffenbarger                                                           *
* Wordfind                                                                    *
* 2/8/19                                                                      *
*                                                                             *
* PRE: word consists of lowercase letters                                     *
* POST: If word is found in grid, starting anywhere                           *
*      and in any of the 8 directions, it is converted                        *
*      to uppercase in the grid, and true is returned.                        *
*      otherwise, grid is unchanged, and false is returned.                   *
*                                                                             *
******************************************************************************/

#include <wordgrid.h>
//-function: bool find(string word, wordgrid & grid)------------------------


bool is_in_bounds(wordgrid & grid, size_t x_loc, size_t y_loc)
{
  size_t count = 0;
  size_t variable = 0;

  //several if statements making sure that the given coordinates are in bounds
  if (x_loc != variable){
    count += 1;
  }
  if (y_loc < variable){
    return false;
  }
  if (y_loc != variable){
    count += 1;
  }
  if (y_loc == variable){
    count += 1;
  }
  if (x_loc < grid.size()){
    count += 1;
  }
  if (y_loc < grid.size()){
    count += 1;
  }
  if (count == 4){
    return true;
  }
  return false;
}

void cap_lst(wordgrid & grid, size_t xlocation, size_t ylocation,
string word, size_t index)
{
  //Capitalizes a given location
  grid.set(xlocation, ylocation, toupper(word[index]));
}

bool word_cap_locations(size_t start_row, size_t start_col, size_t dr,
size_t dc, string word, wordgrid & grid)
{
  size_t shifted_row = start_row;
  size_t shifted_col = start_col;

  //loops thru and capitalizes the appropriate words
  for (size_t i = 1; i < word.length() + 1; i++){
    cap_lst(grid, shifted_row, shifted_col, word, i - 1);
    shifted_row += dr;
    shifted_col += dc;
  }
return true;
}

bool pattern_search_at_in(string word, wordgrid & grid, size_t start_row,
size_t start_col, int dr, int dc)
{
  size_t current_row = start_row;
  size_t current_col = start_col;
  bool in_bounds = false;
  bool result = true;

  //runs through the word and grid with a given direction, if sucessful
  //passes the information to word_cap_locations so the grid can be modified
  for (size_t i = 0; i < word.length(); i++){
    if (word.length() == 1){
      result = word_cap_locations(start_row, start_col, 0, 0, word, grid);
      return result;
    }
    in_bounds = is_in_bounds(grid, current_row, current_col);
    if (in_bounds == false){
      return false;
    }
    if (grid.get(current_row, current_col) != word[i]){
      return false;
    }
    current_row += dr;
    current_col += dc;
  }
result = word_cap_locations(start_row, start_col, dr, dc, word, grid);
return result;
}

bool pattern_search_at(string word, wordgrid & grid, size_t start_row,
size_t start_col)
{
  word = word;
  grid = grid;
  start_row = start_row;
  start_col = start_col;
  bool result = false;
  int direction[16] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};

  //loop thru directions
  for (size_t i = 0; i < 16; i += 2){
    int dr = 0;
    int dc = 0;
    dr += direction[i];
    dc += direction[i + 1];
    result = pattern_search_at_in(word, grid, start_row, start_col, dr, dc);
    if (result){
      return result;
    }
  }
return result;
}

bool pattern_search(string word, wordgrid & grid, size_t xlocations,
  size_t ylocations)
{
  bool result = false;
  size_t start_row = 0;
  size_t start_col = 0;

  // for loop that passes the starting locations to pattern_search_at
  for (size_t i = 0; i < word.length(); i++){
    start_row = 0;
    start_col = 0;
    start_row += xlocations;
    start_col += ylocations;
    if (start_row > 100){   //added in case of bounds errors
      return false;
    }
    if (start_col > 100){
      return false;
    }
    result = pattern_search_at(word, grid, start_row, start_col);
    if (result){
      return result;
    }
  }
return result;
}

bool find(string word, wordgrid & grid)
{
  size_t answer = 0;
  size_t *xlocations = new size_t[word.length()];  //intializing variables
  size_t *ylocations = new size_t[word.length()];
  bool result = false;

//geting the possible first locations for the keyword
  for (size_t i = 0; i < grid.size(); i++){
    for (size_t j = 0; j < grid.size(); j++){
      if (grid.get(i, j) == word[0]){
        xlocations[answer] = i;
        ylocations[answer] = j;
        answer += 1;
      }
    }
  }

//calls the helper functions
  for (size_t i = 0; i < word.length(); i++){
    result = pattern_search(word, grid, xlocations[i], ylocations[i]);
    if (result){
      return true;
    }
  }
return false;
}

//------------------------------------------------------------------------
int main()
{
  size_t dim = 0;  // size of the word grid
  string word = ""; // word to search for
  bool found = false;  // whether the word is found in the grid.
  string one_row = ""; // dim characters (one row) read from stdin
  string all_rows = ""; // dim x dim characters

  // SETUP
  std::cin >> dim;  // read the dimension
  // read each row and append to the string of all rows
  for (size_t r = 0; r < dim ; r = r + 1) {
    std::cin >> one_row;
    all_rows += one_row;
  }
  wordgrid grid(dim, all_rows);  // create the grid from that data
  std::cin >> word; // read the word

  // SEARCH  (you do)
  found = find(word, grid);

  // REPORT
  if (found) {
    std::cout << "FOUND!" << std::endl;
    std::cout << grid;
  }
  else
    std::cout << "NOT FOUND!" << std::endl;
}
