#include <iostream>
#include <vector>

// Special Characters
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

/*
================================================================================
== Board                                                                      ==
================================================================================
*/
class Board {
private:
  Cell &Get(int x, int y) { return board_[y * width_ + (x)]; }

  int HandleWrap(int coord, int max) { return (coord + max) % max; }

  void UpdateState() {
    // Use a copy to prevent updated cells from influencing the next generation.
    // Using a simple vector for now, wondering if it should be a copy of a
    // whole Board
    std::vector<Cell> new_board = board_;

    // for each cell...
    for (int y = 0; y < height_; ++y) {
      for (int x = 0; x < width_; ++x) {
        // check and count number of alive neighbors
        int live_neighbors{0};

        for (int dy = -1; dy <= 1; ++dy) {
          for (int dx = -1; dx <= 1; ++dx) {
            // process only the neighbors
            if (dx == 0 && dy == 0) {
              continue;
            }

            int neighbor_x = HandleWrap(x + dx, width_);
            int neighbor_y = HandleWrap(y + dy, height_);

            if (Get(neighbor_x, neighbor_y).first == ALIVE) {
              live_neighbors++;
            }
          }
        }

        // Apply GoL rules
        auto &cell = Get(x, y);
        if (cell.first == ALIVE) {
          // Dies if fewer than 2 or more than 3 neighbors
          if (live_neighbors < 2 || live_neighbors > 3) {
            new_board[y * width_ + x].first = DEAD;
            new_board[y * width_ + x].second = DEAD;
          }
        } else {
          // Dead cells with exactly 3 live neihgbors are revived
          if (live_neighbors == 3) {
            new_board[y * width_ + x].first = ALIVE;
            new_board[y * width_ + x].second = ALIVE;
          }
        }
      }
    }

    // Replace old board with new board
    board_ = new_board;
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

public:
  Board(int width, int height)
      : width_(width), height_(height), is_running_(false),
        board_(std::vector<Cell>(width_ * height_)) {}

  int GetWidth() { return width_; }

  int GetHeight() { return height_; }

  void RandomState() {
    // Seed rand with the current time
    srand(static_cast<unsigned>(time(0)));

    for (auto &cell : board_) {
      if (rand() % 5 == 0) {
        cell.first = ALIVE;
        cell.second = ALIVE;
      }
    }
    Print();
  }

  // Currently runs in an infinite loop
  void Run() {
    is_running_ = true;
    while (is_running_ == true) {
      UpdateState();
      Print();
      std::wcout << std::endl;
    }
  }

  // Increment by a single generation.
  void Next() {
    UpdateState();
    Print();
  }

private:
  int width_;
  int height_;
  bool is_running_;
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

  Board board(90, 42);
  board.RandomState();
  board.Run();

  return 0;
}
