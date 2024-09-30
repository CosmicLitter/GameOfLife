#include <iostream>
#include <vector>

// Special Characters
const wchar_t ALIVE = L'█'; // '\u2588'
const wchar_t DEAD = L'░';  // '\u2591'

// A cell is two characters long to represent something closer to a square
struct Cell {
  wchar_t first;
  wchar_t second;

  Cell() : first(DEAD), second(DEAD){};
};

class Board {
private:
  Cell &Get(int x, int y) { return board_[y * width_ + (x)]; }

public:
  Board(int width, int height)
      : width_(width), height_(height),
        board_(std::vector<Cell>(width_ * height_)) {}

  int GetWidth() { return width_; }

  int GetHeight() { return height_; }

  // Sets a cell's state to alive
  void Revive(int x, int y) {
    auto &cell = Get(x, y);
    cell.first = ALIVE;
    cell.second = ALIVE;
  }

  // Sets a cell's state to dead
  void Kill(int x, int y) {
    auto &cell = Get(x, y);
    cell.first = DEAD;
    cell.second = DEAD;
  }

  // For now, chance of an alive cell is 10%. Later this should take a custom
  // percentage for number of alive cells
  void RandomState() {
    for (auto &cell : board_) {
      if (rand() % 10 == 0) {
        cell.first = ALIVE;
        cell.second = ALIVE;
      }
    }
  }

  // "Pretty print" the board
  void Print() {
    for (int i = 0; i < width_ * height_; ++i) {
      auto &cell = board_[i];
      std::wcout << cell.first << cell.second;
      if ((i + 1) % width_ == 0) {
        std::wcout << L'\n';
      }
    }
  }

private:
  int width_;
  int height_;
  std::vector<Cell> board_;
};

/*
================================================================================
== Main                                                                       ==
================================================================================
*/
int main() {
  // Ensure the default system locale is used to enable UTF8 characters
  std::locale::global(std::locale(""));

  Board board(40, 35);
  board.RandomState();
  board.Print();

  return 0;
}
