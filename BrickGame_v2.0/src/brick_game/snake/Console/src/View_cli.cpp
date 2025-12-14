//
// Created by Тихон Чабусов on 25.08.2024.
//

#include "../inc/View_cli.h"

using namespace s21;

UserAction_t SnakeViewCLI::EvenLoop() {
  /**
   * @brief Обработка нажатий клавиш пользователем.
   *
   * Функция обрабатывает нажатия клавиш и выполняет соответствующие действия,
   * такие как перемещение фигуры, поворот, приостановка игры и выход.
   */

  int ch = getch();
  UserAction_t action;
  int speed = 100;
  switch (ch) {
    case 'S':
    case 's':
      action = Start;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case ' ':
      action = Action;
      speed = 40;
      timeout(speed);
      break;
    case 'P':
    case 'p':
      action = Pause;
      break;
    case 27:
      action = Up;
      break;
    case ERR:
    default:
      action = Down;
      break;
  }
  napms(speed);
  return action;
};
