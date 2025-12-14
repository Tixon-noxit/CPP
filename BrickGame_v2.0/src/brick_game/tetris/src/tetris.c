/**
 * @file tetris.c
 * @brief Функции для управления игровым процессом Tetris.
 *
 * Этот файл содержит основной игровой цикл.
 */

#include "../inc/tetris.h"

/**
 * @brief Главная функция, управляющая игровым циклом.
 *
 * Функция инициализирует игру, запускает основной игровой цикл, обрабатывает
 * ввод пользователя, проверяет состояние паузы и обновляет отображение игры.
 * Завершает игру при достижении условия окончания.
 *
 * @return int Статус завершения программы.
 */
int main(void) {
  struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};  // Фиксация времени

  showStartScreen();  // Показ экрана с сообщением перед началом игры

  WIN_INIT;

  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();
  dropNewFigure();

  while (tetg->playing != Terminate && tetg->level < 11) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    keystrokes();
    check_pause();
    printGameInfo_t();

    clock_gettime(CLOCK_MONOTONIC, &sp_end);
    if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
        (ts2.tv_nsec == 33000000 - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
      nanosleep(&ts2, &ts1);
    };
  };

  freeGameInfo_t();
  endwin();
  return 0;
}
