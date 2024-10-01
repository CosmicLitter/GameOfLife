#ifndef GAME_H 
#define GAME_H 

#include "../board/board.h"
#include "terminal_config.h"
#include <cstdint>

using Ticks = uint64_t;
class Game {
private:
  static constexpr int FPS = 15;
  static constexpr Ticks TICKS_PER_SECOND = 1000;

public:
  Game();
  ~Game();

  void Run();

  void ProcessInput();

  void Update();

  void Render();

private:
  bool is_running_;
  Board board_;
  TerminalConfig config_;
};

#endif
