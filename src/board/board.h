#ifndef BOARD_H
#define BOARD_H

// Special Characters
#include <vector>
const wchar_t ALIVE = L'█'; // '\u2588'
const wchar_t DEAD = L'░';  // '\u2591'

// A cell is two characters long to represent something closer to a square
// There's likely a better approach, but considering how most fixed-width
// fonts are not square, this seems the simplest way to support most use-cases
struct Cell {
  wchar_t first;
  wchar_t second;

  Cell() : first(DEAD), second(DEAD){};
};

class Board {
private:
  Cell& Get(int x, int y);

  // toroidal wrapping
  int HandleWrap(int coord, int max);

  void UpdateState();

  void Init();

  void Print();

public:
  Board(int width, int height);

  int GetWidth();

  int GetHeight();

  void Run();

  // Increment by a single generation
  void Step();

private:
  int width_;
  int height_;
  bool is_running_;
  std::vector<Cell> board_;
};

#endif
