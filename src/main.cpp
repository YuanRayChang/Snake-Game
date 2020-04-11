#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  bool addBarrier = 0;
  std::cout << "Input 1 to add barrier to the game.\n";
  std::cout << "Input 0 to play the original game.\n";
  std::cin >> addBarrier;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, addBarrier);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}