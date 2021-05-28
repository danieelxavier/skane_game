#ifndef GAMESCORE_H
#define GAMESCORE_H

class GameScore {
 public:
  GameScore();
  GameScore(int best_score, int score, int eaten_food);

  int GetScore() const;
  int GetBestScore() const;
  int GetEatenFood() const;
  bool IsBonusActive() const;

  void FinishBonus();
  void StartBonus();
  void IncreaseScore(int points);
  void UpdateBestScore();
  void IncreaseEatenFood();

  void ClearEatenFood();
  void ClearScore();
  void ClearBestScore();

 private:
  int best_score;
  int score;
  int eaten_food;
  bool bonus_active;
};

#endif