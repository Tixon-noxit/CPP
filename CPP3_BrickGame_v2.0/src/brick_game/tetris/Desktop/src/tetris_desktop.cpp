//
// Created by Тихон Чабусов on 29.08.2024.
//

#include "../inc/tetris_desktop.h"

using namespace s21;

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  // Создаем контроллер Tetris
  TetrisController tetrisController;
  tetrisController.HandleStart(Start, false);
  tetrisController.UpdateGame();
  // Создаем представление и передаем ему контроллер
  View tetrisView(&tetrisController);
  // Инициализация представления
  tetrisView.InitializeView();

  // Отображение представления
  tetrisView.show();

  return app.exec();
}