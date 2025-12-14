//
// Created by Тихон Чабусов on 22.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_VIEW_CLI_H
#define CPP3_BRICKGAME_V2_0_1_VIEW_CLI_H

#include <ncurses.h>

#include "../../../../common/inc/objects.h"

namespace s21 {

class SnakeViewCLI {
 public:
  SnakeViewCLI() {
    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);  // Скрыть курсор
    keypad(stdscr, TRUE);
    // nodelay(stdscr, TRUE);  // Сделать ввод неблокирующим
    timeout(10);  // Тайм-аут для обновления экрана
  }

  ~SnakeViewCLI() {
    // Закрытие ncurses
    endwin();
  }

  UserAction_t EvenLoop();
};

}  // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_VIEW_CLI_H
