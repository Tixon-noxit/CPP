//
// Created by Тихон Чабусов on 22.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_CONTROLLER_H
#define CPP3_BRICKGAME_V2_0_1_CONTROLLER_H

#include "../../../../common/inc/objects.h"
#include "../../inc/Model.h"

namespace s21 {

class SnakeController {
 private:
  SnakeModel* model_;

 public:
  SnakeController(SnakeModel* model) : model_(model) {}

  void ProcessInput(UserAction_t action, bool hold) {
    if (hold) {
      // Ускорение змейки
      //              break;
    } else {
      switch (action) {
        case UserAction_t::Left:
        case UserAction_t::Right:
          model_->ChangeDirection(action);
          break;
        case UserAction_t::Start:
          model_->InitializeGame();
          break;
        case UserAction_t::Pause:
          model_->SetPause();
          break;
        case UserAction_t::Up:
          model_->SetPause();
          break;
        case UserAction_t::Terminate:
          // Завершение игры
          break;
        default:
          break;
      }
    }
  }
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_CONTROLLER_H
