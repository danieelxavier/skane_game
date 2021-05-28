#include <iostream>
#include <fstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGameContentWidth{640};
  constexpr std::size_t kGameContentHeight{240};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::string bestScoreFile = "../res/best";

  std::ifstream infile(bestScoreFile);

  int bestScore = 0;

  if (infile.good()) {
    std::string sLine;
    getline(infile, sLine);
    if(!sLine.empty())
      bestScore = std::stoi(sLine);
  }

  infile.close();

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, bestScore);

  game.Run(controller, renderer, kMsPerFrame);

  int score = game.GetBestScore();
  if(score > bestScore) {
    bestScore = score;

    std::ofstream file;
    file.open (bestScoreFile);
    file << std::to_string(bestScore);
    file.close();
  }

  return 0;
}