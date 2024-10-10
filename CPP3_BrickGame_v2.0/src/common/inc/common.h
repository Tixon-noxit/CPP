//
// Created by Тихон Чабусов on 22.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_COMMON_H
#define CPP3_BRICKGAME_V2_0_1_COMMON_H

#include "./objects.h"

#ifdef __cplusplus
extern "C" {
#endif

GameInfo_t *get_current_game_info(void);
GameInfo_t updateCurrentState(void);
#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICKGAME_V2_0_1_COMMON_H
