//
// Created by Тихон Чабусов on 22.08.2024.
//

#include "../inc/snake_cli.h"

using namespace s21;

int main() {
  SnakeModel model;
  SnakeViewCLI ncursces;
  SnakeController controller(&model);
  model.InitializeGame();

  showStartScreen();

  while (true) {
    // Отрисовка текущего состояния игры
    printGameInfo_t();

    // Получаем ввод пользователя
    UserAction_t action = ncursces.EvenLoop();

    // Обрабатываем пользовательский ввод
    controller.ProcessInput(action, false);

    GameInfo_t *tetg = get_current_game_info();

    if (tetg->playing == Terminate) {
      break;
    }

    model.UpdateState();
  }

  showEndScreen();

  return 0;
}
