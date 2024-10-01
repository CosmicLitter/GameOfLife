#include "terminal_config.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

TerminalConfig::TerminalConfig() : is_raw_mode_(false) {
  if (tcgetattr(STDIN_FILENO, &original_termios_) == -1) {
    std::cerr << "Unable to retrieve terminal configuration." << std::endl;
    std::exit(1);
  } 

  EnableRawMode();
}

TerminalConfig::~TerminalConfig() {
  DisableRawMode();
}

void TerminalConfig::EnableRawMode() {
  if (is_raw_mode_) return;

  struct termios raw = original_termios_;

  cfmakeraw(&raw);
  // configure non-blocking reads
  raw.c_cc[VTIME] = 0;
  raw.c_cc[VMIN] = 0;

  if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1) {
    std::cerr << "Unable to set terminal into raw mode." << std::endl;
    std::exit(1);
  }

  is_raw_mode_ = true;
}

void TerminalConfig::DisableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSANOW, &original_termios_) == -1) {
    std::cerr << "Unable to restore original terminal configruation." << std::endl;
    std::exit(1);
  }

  is_raw_mode_ = false;
}
