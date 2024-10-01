#ifndef TERMINAL_CONFIG_H
#define TERMINAL_CONFIG_H

#include <termios.h>

class TerminalConfig {
private:
  void EnableRawMode();

  void DisableRawMode();

public:
  TerminalConfig();
  ~TerminalConfig();

private:
  struct termios original_termios_;
  bool is_raw_mode_;
};

#endif
