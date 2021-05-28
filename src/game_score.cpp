#include "game_score.h"
#include <iostream>

GameScore::GameScore()
    : best_score(0),
      score(0),
      eaten_food(0),
      bonus_active(false) {
}

GameScore::GameScore(int best_score, int score, int eaten_food)
    : best_score(best_score),
      score(score),
      eaten_food(eaten_food),
      bonus_active(false) {
}



int GameScore::GetScore() const { return score; }
int GameScore::GetBestScore() const { return best_score; }
int GameScore::GetEatenFood() const { return eaten_food; }
bool GameScore::IsBonusActive() const { return bonus_active; }

void GameScore::FinishBonus() {
  bonus_active = false;
}

void GameScore::StartBonus() {
  bonus_active = true;
}

void GameScore::IncreaseScore(int points) {
  score += points;
}

void GameScore::UpdateBestScore() {
  best_score = score;
}

void GameScore::IncreaseEatenFood() {
  eaten_food++;
}

void GameScore::ClearEatenFood() {
  eaten_food = 0;
}

void GameScore::ClearScore() {
  score = 0;
}

void GameScore::ClearBestScore() {
  best_score = 0;
}