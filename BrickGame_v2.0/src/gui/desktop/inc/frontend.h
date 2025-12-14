//
// Created by Тихон Чабусов on 25.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_VIEW_DESCKTOP_H
#define CPP3_BRICKGAME_V2_0_1_VIEW_DESCKTOP_H

#include <ncurses.h>

#undef scroll
#undef timeout

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
// #include "Model.h"
#include "../../../common/inc/IController.h"
#include "../../../common/inc/common.h"
#include "../../../common/inc/defines.h"

namespace s21 {

class View : public QGraphicsView {
  Q_OBJECT

 public:
  explicit View(IController* controller, QWidget* parent = nullptr);
  void InitializeView();
  void UpdateView();
  void ShowGameOver();
  void ShowGameVictory();
  void ShowGamePause();

 protected:
  void keyPressEvent(QKeyEvent* event) override;

 private:
  IController* controller_;
  QGraphicsScene* scene_;
  void DrawStatsPanel();
  QTimer* update_timer_;
  int cell_size_ = 30;  // Размер одной клетки на поле
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_VIEW_DESCKTOP_H
