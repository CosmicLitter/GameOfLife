#include "board.h"
#include <iostream>

Cell& Board::Get(int x, int y) { return board_[y * width_ + (x)]; }

int Board::HandleWrap(int coord, int max) { return (coord + max) % max; }

void Board::UpdateState() {
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
void Board::Print() {
  for (int i = 0; i < width_ * height_; ++i) {
    auto &cell = board_[i];
    std::wcout << cell.first << cell.second;
    if ((i + 1) % width_ == 0) {
      std::wcout << L'\n';
    }
  }
}

Board::Board(int width, int height)
      : width_(width), height_(height), is_running_(false),
        board_(std::vector<Cell>(width_ * height_)) {}

int Board::GetWidth() { return width_; }

int Board::GetHeight() { return height_; }

void Board::Init() {
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
void Board::Run() {
  Init();
  is_running_ = true;
  while (is_running_ == true) {
    UpdateState();
    Print();
    std::wcout << std::endl;
  }
}
void Board::Step() {
  UpdateState();
  Print();
}
