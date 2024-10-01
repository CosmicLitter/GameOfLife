#include "board/board.h"
#include <locale>

/*
================================================================================
== Main                                                                       ==
================================================================================
*/
int main() {
  // Ensure the default system locale is used to enable UTF8 characters
  std::locale::global(std::locale(""));

  Board board(90, 42);
  board.Run();

  return 0;
}
