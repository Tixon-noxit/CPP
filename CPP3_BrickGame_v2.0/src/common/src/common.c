//
// Created by Тихон Чабусов on 22.08.2024.
//

#include "../inc/common.h"

/**
 * @brief Получает указатель на текущее состояние игры.
 *
 * @return Указатель на структуру GameInfo_t, представляющую текущее состояние
 * игры.
 */
GameInfo_t *get_current_game_info(void) {
  static GameInfo_t state_t;
  return &state_t;
}

/**
 * @brief Возвращает структуру, содержащую информацию о текущем состоянии игры.
 *
 * Эта функция должна вызываться из интерфейса с некоторой периодичностью для
 * поддержания интерфейса в актуальном состоянии.
 *
 * @return Текущая структура состояния игры.
 */
GameInfo_t updateCurrentState(void) {
  GameInfo_t *tetg = get_current_game_info();
  return *tetg;
}