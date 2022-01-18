#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
  template <class C>
  void clearDigitsMemory(C& container) {
    for (auto &line: container) {
      fill(line.begin(), line.end(), false);
    }
  }

 public:
  bool isValidSudoku(vector<vector<char>> &board) {
    constexpr int SIZE = 9;
    array<array<bool, SIZE>, SIZE> rows;
    array<array<bool, SIZE>, SIZE> columns;
    array<array<bool, SIZE>, SIZE> squares;
    clearDigitsMemory(rows);
    clearDigitsMemory(columns);
    clearDigitsMemory(squares);

    for (int row = 0; row < board.size(); ++row) {
      const auto &line = board[row];
      for (int column = 0; column < line.size(); ++column) {
        int digit = line[column] - 0x30;
        if (0 < digit and digit < 10) {
          int square_index = 3 * (row / 3) + column / 3;
          const int digit_pos = digit - 1;
          if (rows[row][digit_pos] || columns[column][digit_pos] || squares[square_index][digit_pos]) {
            // digit repeated
            return false;
          }
          rows[row][digit_pos] = true;
          columns[column][digit_pos] = true;
          squares[square_index][digit_pos] = true;
        }
      }
    }

    return true;
  }
};

void TestIsValidSudoku() {
  Solution s;
  {
    vector<vector<char>> board{
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    assert(s.isValidSudoku(board));
  }
  {
    vector<vector<char>> board{
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    assert(not s.isValidSudoku(board));
  }
}

int main() {
  TestIsValidSudoku();
  std::cout << "Ok!" << std::endl;
  return 0;
}
