#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int best_score)
    : snake(grid_width, grid_height),
      game_score(std::make_shared<GameScore>(best_score, 0 , 0)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {


  renderer.DrawImage("../res/anaconda.png");

  bool running = true;
  while(running) {

    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    //Init with size 3
    snake.GrowBody();
    snake.Update();
    snake.GrowBody();
    snake.Update();

    while (snake.alive && running) {
      frame_start = SDL_GetTicks();

      // Input, Update, Render - the main game loop.
      controller.HandleInput(running, snake);
      Update();

      renderer.Render(snake, food, food_bonus, game_score, time - bonus_time);

      frame_end = SDL_GetTicks();

      // Keep track of how long each loop through the input/update/render cycle
      // takes.
      frame_count++;
      frame_duration = frame_end - frame_start;

      time = frame_end/1000;

      if (time - bonus_time >= 5) {
        game_score->FinishBonus();
      } else {
        game_score->StartBonus();
      }

      if (game_score->GetScore() >= game_score->GetBestScore()) {
        game_score->UpdateBestScore();
      }

      // After every second, update the window title.
      if (frame_end - title_timestamp >= 1000) {
        renderer.UpdateWindowTitle(game_score->GetScore(), frame_count, time);
        frame_count = 0;
        title_timestamp = frame_end;
      }

      // If the time for this frame is too small (i.e. frame_duration is
      // smaller than the target ms_per_frame), delay the loop to
      // achieve the correct frame rate.
      if (frame_duration < target_frame_duration) {
        SDL_Delay(target_frame_duration - frame_duration);
      }
    }

    if (running){
      SDL_Delay(2000);
      renderer.DrawImage("../res/gameover.jpg");
      RestartGame(renderer.GetGridWidth(), renderer.GetGridHeight());
    }

  }
}

void Game::PlaceFood(bool bonus) {
  int x, y, xBonus, yBonus;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    if (bonus) {
      xBonus = random_w(engine);
      yBonus = random_h(engine);

      if (!snake.SnakeCell(x, y) && !snake.SnakeCell(xBonus, yBonus) && !(x == xBonus && y == yBonus)) {
        food.x = x;
        food.y = y;
        food_bonus.x = xBonus;
        food_bonus.y = yBonus;
        return;
      }
    } else if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) {
    return;
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    game_score->IncreaseScore(1);

    if (!game_score->IsBonusActive()) {
      game_score->IncreaseEatenFood();
    }

    if (game_score->GetEatenFood() == 5) {
      bonus_time = time;
      game_score->ClearEatenFood();
      PlaceFood(true);
    } else {
      PlaceFood();
    }

    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Check if there's food bonus over here
  if (game_score->IsBonusActive() && food_bonus.x == new_x && food_bonus.y == new_y) {
    game_score->IncreaseScore((5 - (time - bonus_time)) * 5);
    bonus_time = 0;
    // decrease speed.
    snake.speed -= 0.02;
  }
}

void Game::RestartGame(std::size_t grid_width, std::size_t grid_height) {
  game_score = std::make_shared<GameScore>(game_score->GetBestScore(), 0, 0);
  snake = Snake(grid_width, grid_height);
}

int Game::GetScore() const { return game_score->GetScore(); }
int Game::GetBestScore() const { return game_score->GetBestScore(); }
int Game::GetSize() const { return snake.size; }