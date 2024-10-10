//
// Created by Тихон Чабусов on 27.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_CONTROLLERDESKTOP_H
#define CPP3_BRICKGAME_V2_0_1_CONTROLLERDESKTOP_H

#include <ncurses.h>
#undef timeout
#undef scroll

#include <QObject>
#include <QTimer>

#include "../../../../common/inc/IController.h"
#include "../../inc/Model.h"

namespace s21 {
class SnakeView;

class SnakeController : public QObject, public IController {
  Q_OBJECT

 public:
  explicit SnakeController(SnakeModel* model, QObject* parent = nullptr);

  void HandleStart(UserAction_t action, bool hold) override;
  void HandlePause(UserAction_t action, bool hold) override;
  void HandleLeft(UserAction_t action, bool hold) override;
  void HandleRight(UserAction_t action, bool hold) override;
  void HandleUp(UserAction_t action, bool hold) override;
  void HandleDown(UserAction_t action, bool hold) override;
  void HandleAction(UserAction_t action, bool hold) override;

 private:
  void UpdateGame() override;
  SnakeModel* model_;
  QTimer* game_timer_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_CONTROLLERDESKTOP_H
