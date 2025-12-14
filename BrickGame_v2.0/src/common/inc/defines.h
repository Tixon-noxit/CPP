#ifndef DEFINES_H
#define DEFINES_H

#define WIN_INIT            \
  {                         \
    initscr();              \
    cbreak();               \
    noecho();               \
    keypad(stdscr, TRUE);   \
    nodelay(stdscr, TRUE);  \
    scrollok(stdscr, TRUE); \
  }

#define MAX_SCORE_FILE "max_score.txt"

#define FIELD_WIDTH 10   // Ширина поля в пикселях
#define FIELD_HEIGHT 20  // Высота поля в пикселях

#define ESCAPE 27

// Определение начального значения тактов игры
#define TET_TICK_START 70 * 100
// #define TET_TICK_START 20 * 100

// Время задержки между каждым шагом падения фигуры в микросекундах
#define FALL_DELAY_US 50000  // Например, 200 миллисекунд (200000 микросекунд)

#endif
