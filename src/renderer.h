#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"
#include "snake.h"
#include "game_score.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const &snake, SDL_Point const &food, SDL_Point const &food_bonus, const std::shared_ptr<GameScore> &game_score, int bonus_time);
  void UpdateWindowTitle(int score, int fps, int time);
  void DrawImage(const char *image_path);
  std::size_t GetGridWidth();
  std::size_t GetGridHeight();

 private:
  void RenderFood(SDL_Rect &block, SDL_Point const &food, bool bonus = false);
  void RenderSnake(SDL_Rect &block, Snake const &snake);
  void RenderBonusBar(SDL_Rect &block, int filled, bool bonus_active);
  void RenderGrid(SDL_Rect &block, std::vector<std::vector<bool>> grid, int x_position, int y_position);
  void RenderScore(int score, int best_score);
  void ClearScreen();
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Surface *image_surface = NULL;
  SDL_Texture *sdl_texture = NULL;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  int pixel_width;
  int pixel_height;
};

#endif