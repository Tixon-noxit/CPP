//
// Created by Тихон Чабусов on 29.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_TETRISCONTROLLER_H
#define CPP3_BRICKGAME_V2_0_1_TETRISCONTROLLER_H

#include "ncurses.h"

#undef timeout
#undef scroll

#include "../../../../common/inc/IController.h"
#include "../../inc/backend.h"
#include "../../inc/matrix.h"
// #include "../../inc/tetris.h"
#include <QApplication>
#include <QObject>
#include <QTimer>

namespace s21 {

class TetrisController : public QObject, public IController {
  Q_OBJECT

 public:
  TetrisController(QObject* parent = nullptr);

  void UpdateGame() override;

  void HandleStart(UserAction_t action, bool hold) override;

  void HandlePause(UserAction_t action, bool hold) override;

  void HandleLeft(UserAction_t action, bool hold) override;

  void HandleRight(UserAction_t action, bool hold) override;

  void HandleUp(UserAction_t action, bool hold) override;

  void HandleDown(UserAction_t action, bool hold) override;

  void HandleAction(UserAction_t action, bool hold) override;

 private:
  QTimer* game_timer_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_TETRISCONTROLLER_H
