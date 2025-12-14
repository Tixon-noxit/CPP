//
// Created by Тихон Чабусов on 29.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_ICONTROLLER_H
#define CPP3_BRICKGAME_V2_0_1_ICONTROLLER_H

#include "objects.h"

class IController {
 public:
  virtual ~IController() = default;

  virtual void HandleStart(UserAction_t action, bool hold) = 0;
  ;
  virtual void HandlePause(UserAction_t action, bool hold) = 0;
  ;
  virtual void HandleLeft(UserAction_t action, bool hold) = 0;
  ;
  virtual void HandleRight(UserAction_t action, bool hold) = 0;
  ;
  virtual void HandleUp(UserAction_t action, bool hold) = 0;
  ;
  virtual void HandleDown(UserAction_t action, bool hold) = 0;
  ;
  virtual void HandleAction(UserAction_t action, bool hold) = 0;
  ;

 private:
  virtual void UpdateGame() = 0;
  ;
};

#endif  // CPP3_BRICKGAME_V2_0_1_ICONTROLLER_H
