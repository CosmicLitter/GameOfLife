#include "app/game.h"
#include <locale>

int main() {
  // Ensure the default system locale is used to enable UTF8 characters
  std::locale::global(std::locale(""));

  Game game_of_life;
  game_of_life.Run();
  return 0;
}
