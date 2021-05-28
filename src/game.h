#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "game_score.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int best_score);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetBestScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point food_bonus;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::shared_ptr<GameScore> game_score;

  int bonus_time{-6};
  int time{0};

  void PlaceFood(bool bonus = false);
  void Update();
  void RestartGame(std::size_t grid_width, std::size_t grid_height);
};

#endif