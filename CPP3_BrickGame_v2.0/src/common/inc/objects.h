#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>

/**
 * @brief Структура для представления блока тетриса.
 */
typedef struct {
  int b;  ///< Значение блока.
} TetBlock;

/**
 * @brief Структура для представления фигуры тетриса.
 */
typedef struct {
  int x;     ///< Позиция X фигуры на поле.
  int y;     ///< Позиция Y фигуры на поле.
  int size;  ///< Размер фигуры.
  TetBlock *blocks;  ///< Массив блоков, составляющих фигуру.
} TetFigure;

/**
 * @brief Структура для хранения набора фигур тетриса.
 */
typedef struct {
  int count;  ///< Количество фигур в наборе.
  int size;   ///< Размер каждой фигуры.
  TetBlock *blocks;  ///< Массив блоков, составляющих набор фигур.
} TetFiguresT;

/**
 * @brief Структура для представления игрового поля тетриса.
 */
typedef struct {
  int width;         ///< Ширина поля.
  int height;        ///< Высота поля.
  TetBlock *blocks;  ///< Массив блоков, составляющих игровое поле.
} TetField;

/**
 * @brief Перечисление действий игрока.
 */
enum {
  TET_PLAYER_NOP = 0,  ///< Бездействие.
  ESCAPE_BTN           ///< Выход из игры.
};

/**
 * @brief Перечисление действий игрока в игре Tetris.
 */
typedef enum {
  Start,      ///< Начало игры.
  Pause,      ///< Пауза в игре.
  Terminate,  ///< Завершение игры.
  Left,       ///< Движение фигуры влево.
  Right,      ///< Движение фигуры вправо.
  Up,
  Down,   ///< Движение фигуры вниз.
  Action  ///< Вращение фигуры.
} UserAction_t;

/**
 * @brief Структура для представления действий игрока.
 */
typedef struct {
  int action;  ///< Действие игрока.
} TetPlayer;

/**
 * @brief Структура для представления состояния игры.
 */
typedef struct {
  TetField *field;         ///< Игровое поле.
  TetFigure *figure;       ///< Текущая фигура.
  TetFigure *next_figure;  ///< Следующая фигура.
  TetFiguresT *figurest;   ///< Набор фигур.
  TetPlayer *player;       ///< Действие игрока.
  int ticks;               ///< Количество тактов игры.
  int ticks_left;  ///< Оставшееся количество тактов до следующего действия.
  int playing;     ///< Состояние игры.
  int score;       ///< Очки игрока.
  int high_score;  ///< Максимальные очки игрока.
  int level;       ///< Уровень игры.
  int speed;
  int pause;  ///< Флаг, указывающий, находится ли игра в режиме паузы.
} GameInfo_t;

#endif
