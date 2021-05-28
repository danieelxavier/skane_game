#include "renderer.h"
#include "char_samples.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  pixel_width = screen_width / grid_width;
  pixel_height = screen_height / grid_height;

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width + 50*5,
                                screen_height + pixel_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const &snake, SDL_Point const &food,
                      SDL_Point const &food_bonus, bool bonus_active,
                      int bonus_time, int eaten_food, int score,
                      int best_score) {
  SDL_Rect block;
  block.w = pixel_width;
  block.h = pixel_height;

  int filled = grid_width * (20 * eaten_food) / 100;

  ClearScreen();

  RenderFood(block, food);

  if (bonus_active) {
    RenderFood(block, food_bonus, bonus_active);
    filled = grid_width * (20 * (5 - bonus_time)) / 100;
  }

  RenderBonusBar(block, filled, bonus_active);

  RenderSnake(block, snake);

  SDL_Event event;
  SDL_RenderFillRect(sdl_renderer, &block);

  RenderScore(score, best_score);
  SDL_RenderPresent(sdl_renderer);

}

void Renderer::ClearScreen() {
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x5C, 0x08, 0xFF);
  SDL_RenderClear(sdl_renderer);
}

void Renderer::RenderBonusBar(SDL_Rect &block, int filled, bool bonus_active) {

  SDL_Point bonus_bar;
  bonus_bar.y = grid_height;

  if (bonus_active) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x30, 0xFF, 0xF8, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0x50, 0xDE, 0x6C, 0xFF);
  }

  for(int i = 0; i < filled ; i++) {
    bonus_bar.x = i;
    block.x = bonus_bar.x * block.w;
    block.y = bonus_bar.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  SDL_SetRenderDrawColor(sdl_renderer, 0xB0, 0xB0, 0xB0, 0xFF);
  for(int i = filled; i <= grid_width; i++) {
    bonus_bar.x = i;
    block.x = bonus_bar.x * block.w;
    block.y = bonus_bar.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

}

void Renderer::RenderFood(SDL_Rect &block, SDL_Point const &food, bool bonus) {

  if (bonus) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x30, 0xFF, 0xF8, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  }

  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

}

void Renderer::RenderSnake(SDL_Rect &block, Snake const &snake) {

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }

}

void Renderer::RenderScore(int score, int best_score) {
  SDL_Rect score_block;
  score_block.w = 50*5;
  score_block.h = 5;

  SDL_SetRenderDrawColor(sdl_renderer, 0x2D, 0x2D, 0x2D, 0xFF);

  for (int i = 0; i < screen_height; i++) {
    score_block.x = screen_width;
    score_block.y = i * score_block.h;
    SDL_RenderFillRect(sdl_renderer, &score_block);
  }
  score_block.w = 5;
  score_block.h = 5;
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  int x_position = screen_width + score_block.w * 3;
  int y_position = screen_width / 5;

  auto grid = Anaconda();
  RenderGrid(score_block, grid, x_position, y_position);

  // new line
  x_position = screen_width + score_block.w * 3;
  y_position += (grid.size() * 3) * score_block.h;

  grid = Score();
  RenderGrid(score_block, grid, x_position, y_position);
  x_position += (grid[0].size() + 1) * score_block.w;

  grid = TwoDots();
  RenderGrid(score_block, grid, x_position, y_position);
  x_position += (grid[0].size() + 2) * score_block.w;

  int scoreAux = score;
  int num1 = scoreAux / 1000;
  scoreAux = scoreAux % 1000;

  int num2 = scoreAux / 100;
  scoreAux = scoreAux % 100;

  int num3 = scoreAux / 10;
  scoreAux = scoreAux % 10;

  int num4 = scoreAux;

  grid = GridFromNumber(num1);
  if (grid.size() > 0){
    RenderGrid(score_block, grid, x_position, y_position);
    x_position += (grid[0].size() + 1) * score_block.w;
  }

  grid = GridFromNumber(num2);
  if (grid.size() > 0){
    RenderGrid(score_block, grid, x_position, y_position);
    x_position += (grid[0].size() + 1) * score_block.w;
  }

  grid = GridFromNumber(num3);
  if (grid.size() > 0){
    RenderGrid(score_block, grid, x_position, y_position);
    x_position += (grid[0].size() + 1) * score_block.w;
  }

  grid = GridFromNumber(num4);
  if (grid.size() > 0){
    RenderGrid(score_block, grid, x_position, y_position);
    x_position += (grid[0].size() + 1) * score_block.w;
  }


  // new line
  x_position = screen_width + score_block.w * 3;
  y_position += (grid.size() * 3) * score_block.h;

  grid = Best();
  RenderGrid(score_block, grid, x_position, y_position);
  x_position += (grid[0].size() + 1) * score_block.w;

  grid = TwoDots();
  RenderGrid(score_block, grid, x_position, y_position);
  x_position += (grid[0].size() + 6) * score_block.w;

  scoreAux = best_score;
  num1 = scoreAux / 1000;
  scoreAux = scoreAux % 1000;

  num2 = scoreAux / 100;
  scoreAux = scoreAux % 100;

  num3 = scoreAux / 10;
  scoreAux = scoreAux % 10;

  num4 = scoreAux;


  grid = GridFromNumber(num1);
  if (grid.size() > 0){
    RenderGrid(score_block, grid, x_position, y_position);
    x_position += (grid[0].size() + 1) * score_block.w;
  }

  grid = GridFromNumber(num2);
  if (grid.size() > 0){
    RenderGrid(score_block, grid, x_position, y_position);
    x_position += (grid[0].size() + 1) * score_block.w;
  }

  grid = GridFromNumber(num3);
  if (grid.size() > 0){
    RenderGrid(score_block, grid, x_position, y_position);
    x_position += (grid[0].size() + 1) * score_block.w;
  }

  grid = GridFromNumber(num4);
  if (grid.size() > 0){
    RenderGrid(score_block, grid, x_position, y_position);
    x_position += (grid[0].size() + 1) * score_block.w;
  }


}

void Renderer::RenderGrid(SDL_Rect &block, std::vector<std::vector<bool>> grid, int x_position, int y_position) {
  for (int i = 0; i < grid.size(); i++) {
    auto line = grid[i];
    for (int j = 0; j < line.size(); j++) {
      if (line[j]) {
        block.x = x_position + j * block.w;
        block.y = y_position + i * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
      }
    }
  }
}

void Renderer::DrawImage(const char *image_path) {
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_Rect m_image_position;
  m_image_position.x = 0;
  m_image_position.y = 0;
  m_image_position.w = 640;
  m_image_position.h = 480;

  image_surface = IMG_Load(image_path);
  sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, image_surface);

  if (!image_surface) {
    std::cout << "Fail to load image!" << std::endl;
    return;
  } else {
    SDL_RenderCopy(sdl_renderer, sdl_texture, NULL, NULL);
    SDL_RenderPresent(sdl_renderer);
    SDL_Delay(2000);
  }
}

void Renderer::UpdateWindowTitle(int score, int fps, int time) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " | FPS: " + std::to_string(fps) +
                    " | TIME: " + std::to_string(time)};

  SDL_SetWindowTitle(sdl_window, title.c_str());
}

std::size_t Renderer::GetGridWidth() {
  return grid_width;
}

std::size_t Renderer::GetGridHeight() {
  return grid_height;
}
