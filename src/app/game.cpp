#include "game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

Game::Game() : is_running_(false) {
  board_.Resize();

  std::wcout << L"\033[3J\033[2J\033[H\033[?25l";
}

Game::~Game() {
  std::cout << L"\033[2J\033[H\033[?25h\033[3J";
}

void Game::Run() {
  using namespace std::chrono;
  const auto frame_duration = milliseconds(TICKS_PER_SECOND / FPS);

  is_running_ = true;
  while (is_running_) {
    auto frame_start = steady_clock::now();

    ProcessInput();

    Update();

    Render();

    auto frame_end = steady_clock::now();
    auto frame_time = frame_end - frame_start;

    if (frame_time < frame_duration) {
      std::this_thread::sleep_for(frame_duration - frame_time);
    }
  }

}

void Game::ProcessInput() {
  char ch;
  if (read(STDIN_FILENO, &ch, 1) == 1) {
    if (ch == 'q') is_running_ = false;
  }
}

void Game::Update() {
  board_.Run();
}

void Game::Render() {
  board_.Print();
}
