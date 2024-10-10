//
// Created by Тихон Чабусов on 24.04.2024.
//

#ifndef C7_BRICKGAME_V1_0_1_FRONTEND_H
#define C7_BRICKGAME_V1_0_1_FRONTEND_H

#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../../../brick_game/tetris/inc/backend.h"
#include "../../../common/inc/common.h"
#include "../../../common/inc/defines.h"
#include "../../../common/inc/objects.h"

#ifdef __cplusplus
extern "C" {
#endif
void printGameInfo_t(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
void showStartScreen(void);
void showEndScreen(void);
void showPauseScreen(void);
#ifdef __cplusplus
}
#endif

#endif  // C7_BRICKGAME_V1_0_1_FRONTEND_H
