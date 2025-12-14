//
// Created by Тихон Чабусов on 24.04.2024.
//
#include "../inc/matrix.h"

/**
 * @brief Создает игровое поле Tetris заданного размера.
 *
 * @param width Ширина игрового поля.
 * @param height Высота игрового поля.
 * @return Указатель на созданное игровое поле TetField. Возвращает NULL, если
 * не удалось выделить память.
 */
TetField *createTetField(int width, int height) {
  TetField *tetf = (TetField *)malloc(sizeof(TetField));
  if (!tetf) return NULL;
  tetf->width = width;
  tetf->height = height;
  tetf->blocks = (TetBlock *)malloc(sizeof(TetBlock) * width * height);
  for (int i = 0; i < width * height; i++)
    tetf->blocks[i].b = 0;  // Все блоки отсутствуют на поле (в начале игры)

  return tetf;
}

/**
 * @brief Освобождает память, выделенную под игровое поле TetField.
 *
 * @param tetf Указатель на игровое поле, которое нужно освободить.
 */
void freeTetField(TetField *tetf) {
  if (tetf) {
    if (tetf->blocks) free(tetf->blocks);
    free(tetf);
  };
}

/**
 * @brief Перемещает текущую фигуру вниз на одну строку.
 */
void moveFigureDown(void) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure->y++;
}

/**
 * @brief Перемещает текущую фигуру вверх на одну строку.
 */
void moveFigureUp(void) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure->y--;
}

/**
 * @brief Перемещает текущую фигуру влево на один столбец.
 */
void moveFigureLeft(void) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure->x--;
}

/**
 * @brief Перемещает текущую фигуру вправо на один столбец.
 */
void moveFigureRight(void) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure->x++;
}

/**
 * @brief Определяет, произошло ли столкновение фигуры с границами игрового поля
 * или другими фигурами.
 *
 * @return 1, если произошло столкновение; 0, если столкновения нет.
 */
int collisionTet(void) {
  GameInfo_t *tetg = get_current_game_info();
  TetFigure *t = tetg->figure;
  TetField *tf = tetg->field;
  int check = 0;
  for (int i = 0; i < t->size; i++) {
    for (int j = 0; j < t->size; j++) {
      if (t->blocks[i * t->size + j].b != 0) {
        int fx = t->x + j;
        int fy = t->y + i;
        if (fx < 0 || fx >= tf->width || fy < 0 || fy >= tf->height ||
            tf->blocks[fy * tf->width + fx].b != 0) {
          check = 1;  // Проверка столкновения с границами или другими фигурами
        }
      }
    }
  }
  return check;  // Столкновение
}

/**
 * @brief Размещает текущую фигуру на игровом поле после падения.
 */
void plantFigure(void) {
  GameInfo_t *tetg = get_current_game_info();
  TetFigure *t = tetg->figure;
  for (int i = 0; i < t->size; i++) {
    for (int j = 0; j < t->size; j++) {
      if (t->blocks[i * t->size + j].b != 0) {  // Если блок не "пустой"
        int fx = t->x + j;
        int fy = t->y + i;
        tetg->field->blocks[fy * tetg->field->width + fx].b =
            t->blocks[i * t->size + j].b;
      };
    };
  };
}

/**
 * @brief Проверяет, заполнена ли строка на игровом поле.
 *
 * @param i Номер строки для проверки.
 * @param tfl Указатель на игровое поле.
 * @return 1, если строка заполнена; 0, если есть пустые блоки.
 */
int lineFieldTet(int i, TetField *tfl) {
  int flag = 1;
  for (int j = 0; j < tfl->width; j++) {
    if (tfl->blocks[i * tfl->width + j].b == 0) flag = 0;
  };
  return flag;
}

/**
 * @brief Сдвигает строки игрового поля вниз на одну строку, начиная с указанной
 * строки.
 *
 * @param i Номер строки, с которой начинается сдвиг.
 * @param tfl Указатель на игровое поле.
 */
void dropLineTet(int i, TetField *tfl) {
  if (i == 0) {
    for (int j = 0; j < tfl->width; j++) {
      tfl->blocks[j].b = 0;
    };
  } else {
    for (int k = i; k > 0; k--) {
      for (int j = 0; j < tfl->width; j++) {
        tfl->blocks[k * tfl->width + j].b =
            tfl->blocks[(k - 1) * tfl->width + j].b;
      };
    };
  };
}

/**
 * @brief Удаляет заполненные строки на игровом поле и возвращает количество
 * удаленных строк.
 *
 * @return Количество удаленных строк.
 */
int eraseLinesTet(void) {
  GameInfo_t *tetg = get_current_game_info();
  TetField *tfl = tetg->field;
  int count = 0;
  for (int i = tfl->height - 1; i >= 0; i--) {
    while (lineFieldTet(i, tfl)) {
      dropLineTet(i, tfl);
      count++;
    };
  };

  return count;
}

/**
 * @brief Создает и инициализирует новую фигуру Tetris.
 *
 * @return Указатель на созданную фигуру.
 */
TetFigure *createTetFigure(void) {
  GameInfo_t *tetg = get_current_game_info();
  TetFigure *t = (TetFigure *)malloc(sizeof(TetFigure));
  t->x = 0;
  t->y = 0;
  t->size = tetg->figurest->size;
  t->blocks = (TetBlock *)malloc(sizeof(TetBlock) * t->size * t->size);
  return t;
}

/**
 * @brief Освобождает память, выделенную под фигуру Tetris.
 *
 * @param tf Указатель на фигуру, которую нужно освободить.
 */
void freeTetFigure(TetFigure *tf) {
  if (tf) {
    if (tf->blocks) {
      free(tf->blocks);
    };
    free(tf);
  };
}

/**
 * @brief Создает новую фигуру Tetris на основе текущего состояния игры.
 *
 * @param tetg Указатель на структуру с текущим состоянием игры.
 * @return Указатель на созданную фигуру.
 */
TetFigure *createNewTetFigure(GameInfo_t *tetg) {
  TetFigure *new_figure = createTetFigure();
  new_figure->x = tetg->field->width / 2 - new_figure->size / 2;
  new_figure->y = 0;
  int fnum = rand() % tetg->figurest->count;
  for (int i = 0; i < new_figure->size; i++) {
    for (int j = 0; j < new_figure->size; j++) {
      new_figure->blocks[i * new_figure->size + j].b =
          tetg->figurest
              ->blocks[fnum * new_figure->size * new_figure->size +
                       i * new_figure->size + j]
              .b;
    }
  }
  return new_figure;
}

/**
 * @brief Выбрасывает новую фигуру на игровое поле и создает следующую фигуру.
 */
void dropNewFigure(void) {
  GameInfo_t *tetg = get_current_game_info();
  TetFigure *current_t = createNewTetFigure(tetg);
  freeTetFigure(tetg->figure);
  tetg->figure = current_t;
  for (int i = 0; i < tetg->next_figure->size; i++) {
    for (int j = 0; j < tetg->next_figure->size; j++) {
      tetg->figure->blocks[i * tetg->next_figure->size + j] =
          tetg->next_figure->blocks[i * tetg->next_figure->size + j];
    }
  }
  TetFigure *next_t = createNewTetFigure(tetg);
  freeTetFigure(tetg->next_figure);
  tetg->next_figure = next_t;
}

/**
 * @brief Поворачивает текущую фигуру на 90 градусов.
 *
 * @return Указатель на повернутую фигуру.
 */
TetFigure *rotTetFigure(void) {
  GameInfo_t *tetg = get_current_game_info();
  TetFigure *t = createTetFigure();
  TetFigure *told = tetg->figure;
  t->x = told->x;
  t->y = told->y;
  for (int i = 0; i < t->size; i++) {
    for (int j = 0; j < t->size; j++) {
      t->blocks[i * t->size + j].b =
          told->blocks[j * t->size + t->size - 1 - i].b;
    };
  };
  return t;
}
