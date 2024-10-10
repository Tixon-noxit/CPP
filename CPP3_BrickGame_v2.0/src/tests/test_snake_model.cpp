//
// Created by Тихон Чабусов on 30.08.2024.
//

#include <gtest/gtest.h>

#include "../brick_game/snake/inc/Model.h"  // путь к SnakeModel
#include "../common/inc/common.h"
#include "../common/inc/defines.h"

using namespace s21;

class SnakeModelTest : public ::testing::Test {
 protected:
  SnakeModel model;

  void SetUp() override { model.InitializeGame(); }
};

TEST_F(SnakeModelTest, InitializationTest) {
  GameInfo_t* gameInfo = get_current_game_info();

  // Проверка начальных условий игры
  EXPECT_EQ(gameInfo->score, 4);
  EXPECT_EQ(gameInfo->level, 0);
  EXPECT_EQ(gameInfo->pause, 0);
  EXPECT_EQ(gameInfo->playing, Start);
  EXPECT_NE(gameInfo->field, nullptr);
  EXPECT_EQ(gameInfo->field->width, FIELD_WIDTH);
  EXPECT_EQ(gameInfo->field->height, FIELD_HEIGHT);
}

TEST_F(SnakeModelTest, MoveSnakeTest) {
  GameInfo_t* gameInfo = get_current_game_info();
  (void)gameInfo;
  // Запоминаем положение головы змейки
  auto old_head = model.GetSnakeBody().front();

  // Перемещаем змейку
  model.UpdateState();
  model.ChangeDirection(Left);
  model.GetSaveScore();

  // Проверяем, что голова змейки переместилась
  auto new_head = model.GetSnakeBody().front();
  EXPECT_NE(old_head, new_head);
}

TEST_F(SnakeModelTest, CheckPauseFunctionality) {
  GameInfo_t gameInfo_2 = updateCurrentState();
  (void)gameInfo_2;
  GameInfo_t* gameInfo = get_current_game_info();

  // Проверка паузы
  model.SetPause();
  EXPECT_TRUE(gameInfo->pause);

  model.SetPause();
  EXPECT_FALSE(gameInfo->pause);
}

TEST_F(SnakeModelTest, CheckAddNewHead) {
  std::pair<int, int> new_head_position = {5, 5};
  model.AddNewHead(new_head_position);
  GameInfo_t* gameInfo = get_current_game_info();

  // Проверка паузы
  model.SetPause();
  EXPECT_TRUE(gameInfo->pause);

  model.SetPause();
  EXPECT_FALSE(gameInfo->pause);
}
