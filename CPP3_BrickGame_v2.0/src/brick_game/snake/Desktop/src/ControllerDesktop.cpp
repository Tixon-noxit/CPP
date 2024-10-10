//
// Created by Тихон Чабусов on 27.08.2024.
//

#include "../inc/ControllerDesktop.h"

namespace s21 {

/**
 * @class Конструктор контроллера
 * @param model - модель с которой будет произведена работа
 * @param parent
 */
SnakeController::SnakeController(SnakeModel* model, QObject* parent)
    : QObject(parent), model_(model) {
  game_timer_ = new QTimer(this);
  connect(game_timer_, &QTimer::timeout, this, &SnakeController::UpdateGame);
  game_timer_->start(100);
}

/**
 * @brief Нажат Старт (S)
 * @param action
 * @param hold
 */
void SnakeController::HandleStart(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  return;
}

/**
 * @brief Нажат Пауза (P)
 * @param action
 * @param hold
 */
void SnakeController::HandlePause(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  model_->SetPause();
}

/**
 * @brief Нажат Влево (<-)
 * @param action
 * @param hold
 */
void SnakeController::HandleLeft(UserAction_t action, bool hold) {
  (void)hold;
  model_->ChangeDirection(action);
}

/**
 * @brief Нажат В право (->)
 * @param action
 * @param hold
 */
void SnakeController::HandleRight(UserAction_t action, bool hold) {
  (void)hold;
  model_->ChangeDirection(action);
}

/**
 * @brief Нажат вверх (В данной игре не используется)
 * @param action
 * @param hold
 */
void SnakeController::HandleUp(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  return;
}

/**
 * @brief Нажат Вниз ()
 * @param action
 * @param hold
 */
void SnakeController::HandleDown(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  return;
}

/**
 * @brief Нажат Действие (пробел)
 * @param action
 * @param hold
 */
void SnakeController::HandleAction(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  model_->UpdateState();
  game_timer_->start(model_->GetSpeed() / 2);
}

/**
 * @brief Обновление игровой ситуации - вызывается таймером контроллера
 */
void SnakeController::UpdateGame() {
  model_->UpdateState();
  game_timer_->start(model_->GetSpeed() / model_->GetLevel());
}
}  // namespace s21