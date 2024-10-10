//
// Created by Тихон Чабусов on 24.04.2024.
//

#ifndef C7_BRICKGAME_V1_0_1_BACKEND_H
#define C7_BRICKGAME_V1_0_1_BACKEND_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>  // для usleep

#include "../../../common/inc/common.h"
#include "../../../common/inc/defines.h"
#include "../../../common/inc/objects.h"
#include "../../../gui/cli/inc/frontend.h"
#include "../inc/matrix.h"

TetFigure* createTetFigure(void);

#ifdef __cplusplus
extern "C" {
#endif

void calculateTet();
// void dropNewFigure();
void createGameInfo_t(int field_width, int field_height, int figures_size,
                      int count, TetBlock* figures_template);
void pauseGame();
void userInput(UserAction_t action, bool hold);

#ifdef __cplusplus
}
#endif

void score_add(int count_line);

int readMaxScore(const char* filename);

void updateMaxScore(const char* filename, int new_score);

// void calculateTet(void);

void freeGameInfo_t(void);

// GameInfo_t updateCurrentState(void);

// void userInput(UserAction_t action, bool hold);
void check_pause(void);
void keystrokes(void);
// void pauseGame(void);

// GameInfo_t *get_current_game_info(void);

// GameInfo_t updateCurrentState(void);

#endif  // C7_BRICKGAME_V1_0_1_BACKEND_H
