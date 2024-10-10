//
// Created by Тихон Чабусов on 22.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_MODEL_H
#define CPP3_BRICKGAME_V2_0_1_MODEL_H

#include <cstdlib>  // rand()
#include <ctime>    // time()
#include <deque>    // std::deque
#include <utility>
#include <vector>

#include "../../../common/inc/objects.h"

namespace s21 {

class SnakeModel {
 private:
  std::deque<std::pair<int, int>> snake_body_;  // Тело змейки (x, y)
  std::pair<int, int> direction_;  // Направление движения змейки
  GameInfo_t* tetg_;  // Структура с игровыми параметрами
  int apple_x_, apple_y_;  // Координаты яблока на поле

 public:
  bool CheckAppleCollision(const std::pair<int, int>& new_head_position);
  SnakeModel();
  void InitializeGame();
  void UpdateState();
  void ChangeDirection(UserAction_t action);
  void SetPause();
  std::deque<std::pair<int, int>> GetSnakeBody() { return snake_body_; };

  // Геттеры
  int GetAppleX() { return apple_x_; };
  int GetAppleY() { return apple_y_; };
  int GetSpeedGame() { return tetg_->ticks; };
  int GetPause() { return tetg_->pause; };
  int GetScore() { return tetg_->score; };
  int GetSpeed() { return tetg_->speed; };
  int GetHighScore() { return tetg_->high_score; };
  int GetLevel() { return tetg_->level; };
  TetField* GetGameField() { return tetg_->field; };
  void GetSaveScore() { SaveScore(2); }
  void AddNewHead(const std::pair<int, int>& new_head_position);

 private:
  void MoveSnake();
  bool CheckCollision(const std::pair<int, int>& new_head_position);
  void SpawnApple();
  bool IsApplePresent() const;

  // Учет достижений игрока
  const std::string filename = "snake_high_scores.txt";
  void SaveScore(int score) const;
  int ReadScore() const;
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_MODEL_H
