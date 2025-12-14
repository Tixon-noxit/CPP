//
// Created by Тихон Чабусов on 25.08.2024.
//

// g++ -std=c++17 -Wall -Wextra -I../inc src/snake_desktop.cpp
// ../../gui/desktop/src/frontend.cpp ../../common/src/common.c  src/Model.cpp
// `pkg-config --cflags --libs gtkmm-3.0` -o snake_desktop

#include "../inc/snake_desktop.h"

/**
 * @brief Главная функция игровой сессии - запускает игровой цикл
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::SnakeModel model;
  s21::SnakeController controller(&model);
  s21::View view(&controller);

  //    controller.StartGame();
  view.InitializeView();

  view.show();

  return app.exec();
}
