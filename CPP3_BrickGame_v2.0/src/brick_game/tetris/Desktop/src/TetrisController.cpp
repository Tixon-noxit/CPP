//
// Created by Тихон Чабусов on 29.08.2024.
//

#include "../inc/TetrisController.h"

using namespace s21;

TetrisController::TetrisController(QObject* parent) : QObject(parent) {
  game_timer_ = new QTimer(this);
  connect(game_timer_, &QTimer::timeout, this, &TetrisController::UpdateGame);
}

void TetrisController::HandleLeft(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  return;
}

void TetrisController::HandleRight(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  return;
}

void TetrisController::HandleUp(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  return;
}

void TetrisController::HandleDown(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  return;
}

void TetrisController::HandleAction(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  return;
}

void TetrisController::HandlePause(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  pauseGame();
}

void TetrisController::HandleStart(UserAction_t action, bool hold) {
  (void)action;
  (void)hold;
  TetBlock tet_templates[] = {
      {0}, {0}, {1}, {0}, {0}, {0}, {0}, {1}, {0}, {0}, {0}, {0}, {1}, {0}, {0},
      {0}, {0}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
      {0}, {0}, {1}, {0}, {0}, {0}, {1}, {1}, {1}, {0}, {0}, {0}, {0}, {0}, {0},
      {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {1}, {1}, {0},
      {0}, {0}, {1}, {0}, {0}, {0}, {0}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
      {0}, {0}, {0}, {0}, {0}, {0}, {1}, {1}, {0}, {0}, {0}, {0}, {1}, {0}, {0},
      {0}, {0}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
      {0}, {0}, {1}, {1}, {0}, {0}, {1}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
      {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {1}, {1}, {0}, {0},
      {0}, {0}, {1}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
      {0}, {0}, {0}, {0}, {0}, {0}, {1}, {1}, {0}, {0}, {0}, {1}, {1}, {0}, {0},
      {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  dropNewFigure();

  game_timer_->start(1000 / 60);  // 60 FPS, обновление кадра каждые ~16 мс
}

void TetrisController::UpdateGame() {
  calculateTet();
  //      if (!model_->game_over && !model_->GetPause()) {
  //          if(model_->GetScore() < 200) {
  //              model_->UpdateState();
  //              //view_->UpdateView();
  //          }
  ////          else {
  ////              view_->ShowGameVictory();
  ////          }
  //      } else if (!model_->game_over && model_->GetPause()) {
  //          //view_->ShowGamePause();
  //          game_timer_->stop();
  //      }
  //      else {
  //          game_timer_->stop();
  //          //view_->ShowGameOver();
  //      }
}
