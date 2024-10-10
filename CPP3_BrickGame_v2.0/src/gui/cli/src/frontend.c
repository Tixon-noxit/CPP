//
// Created by Тихон Чабусов on 24.04.2024.
//
#include "../inc/frontend.h"

/**
 * @brief Функция для отрисовки текста по центру заданной области.
 *
 * @param top_y Верхняя граница области.
 * @param bottom_y Нижняя граница области.
 * @param left_x Левая граница области.
 * @param right_x Правая граница области.
 * @param text Текст для отображения.
 */
void draw_centered_text(int top_y, int bottom_y, int left_x, int right_x,
                        const char* text) {
  int text_length = strlen(text);
  int center_y = (top_y + bottom_y) / 2;
  int center_x = (left_x + right_x - text_length) / 2;

  mvprintw(center_y, center_x, "%s", text);
}

/**
 * @brief Отрисовка прямоугольника вокруг игровой области.
 *
 * @param top_y Координата Y верхней границы.
 * @param bottom_y Координата Y нижней границы.
 * @param left_x Координата X левой границы.
 * @param right_x Координата X правой границы.
 */
void draw_game_area_border(int top_y, int bottom_y, int left_x, int right_x) {
  // Верхняя и нижняя линии
  mvhline(top_y, left_x, ACS_HLINE, right_x - left_x + 1);
  mvhline(bottom_y, left_x, ACS_HLINE, right_x - left_x + 1);
  // Левая и правая линии
  mvvline(top_y + 1, left_x, ACS_VLINE, bottom_y - top_y - 1);
  mvvline(top_y + 1, right_x, ACS_VLINE, bottom_y - top_y - 1);
  // Угловые символы
  mvaddch(top_y, left_x, ACS_ULCORNER);   // Верхний левый угол
  mvaddch(top_y, right_x, ACS_URCORNER);  // Верхний правый угол
  mvaddch(bottom_y, left_x, ACS_LLCORNER);  // Нижний левый угол
  mvaddch(bottom_y, right_x, ACS_LRCORNER);  // Нижний правый угол
}

/**
 * @brief Отрисовка прямоугольника с текстом внутри.
 *
 * @param top_y Верхняя граница.
 * @param bottom_y Нижняя граница.
 * @param left_x Левая граница.
 * @param right_x Правая граница.
 * @param title Заголовок для отображения внутри рамки.
 * @param content Текстовое содержимое для отображения.
 */
void draw_bordered_text_area(int top_y, int bottom_y, int left_x, int right_x,
                             const char* title, const char* content) {
  draw_game_area_border(top_y, bottom_y, left_x, right_x);
  mvprintw(top_y, left_x, "%s", title);
  mvprintw((top_y + bottom_y) / 2, left_x + 1, "%s", content);
}

/**
 * @brief Отрисовка блока с фигурой.
 *
 * @param y Координата Y для отображения.
 * @param x Координата X для отображения.
 * @param figure Фигура для отображения.
 */
void draw_figure(int y, int x, TetFigure* figure) {
  for (int i = 0; i < figure->size; ++i) {
    for (int j = 0; j < figure->size; ++j) {
      char ch = figure->blocks[i * figure->size + j].b == 0 ? ' ' : '#';
      mvprintw(y + i, x + j * 2, "%c", ch);
    }
  }
}

/**
 * @brief Отрисовка игровой статистики (следующая фигура, счет, рекорд,
 * уровень).
 */
void print_game_statistics(GameInfo_t* tetg) {
  TetField* field = tetg->field;

  if (tetg->next_figure) {
    // Отрисовка следующей фигуры
    draw_bordered_text_area(
        2, 2 + tetg->next_figure->size + 2, (field->width) * 2 + 5,
        (field->width) * 2 + 3 + tetg->next_figure->size * 2 + 1, "NEXT", "");
    draw_figure(3, (field->width) * 2 + 4, tetg->next_figure);
  } else {
    // Отрисовка размера змейки
    char size[12];
    sprintf(size, "%d", tetg->figure->size);
    draw_bordered_text_area(6, 8, (field->width) * 2 + 5,
                            (field->width) * 2 + 3 + 11, "SIZE", size);
  }

  // Отрисовка счета
  char score_str[12];
  sprintf(score_str, "%d", tetg->score);
  draw_bordered_text_area(10, 12, (field->width) * 2 + 5,
                          (field->width) * 2 + 3 + 11, "SCORE", score_str);

  // Отрисовка рекорда
  char max_score_str[12];
  sprintf(max_score_str, "%d", tetg->high_score);
  draw_bordered_text_area(13, 15, (field->width) * 2 + 5,
                          (field->width) * 2 + 3 + 11, "Hi-SCORE",
                          max_score_str);

  // Отрисовка уровня
  char level_str[12];
  sprintf(level_str, "%d", tetg->level);
  draw_bordered_text_area(16, 18, (field->width) * 2 + 5,
                          (field->width) * 2 + 3 + 11, "LEVEL", level_str);
}

/**
 * @brief Отрисовка игровой области и фигур.
 */
void printGameInfo_t(void) {
  GameInfo_t* tetg = get_current_game_info();

  if (!tetg) {
    fprintf(stderr, "Error: get_current_game_info returned NULL\n");
    return;
  }

  TetField* tf = tetg->field;
  TetFigure* t = tetg->figure;

  curs_set(0);  // Скрыть курсор

  int offsetX = 2;
  int offsetY = 0;

  // Отрисовка игровой области
  for (int i = 0; i < tf->height; ++i) {
    for (int j = 0; j < tf->width; ++j) {
      int sum = (tf->blocks[i * tf->width + j].b != 0);

      int x = (j - t->x) * 2;
      int y = i - t->y;
      if (x >= 0 && x < t->size * 2 && y >= 0 && y < t->size) {
        sum |= (t->blocks[y * t->size + x / 2].b != 0);
      }

      mvprintw(i + offsetY, j * 2 + offsetX, "%s", sum ? "[]" : "  ");
    }
  }

  // Отрисовка границ
  draw_game_area_border(offsetY, tf->height + offsetY, offsetX - 1,
                        offsetX + (tf->width) * 2);
  draw_game_area_border(offsetY, tf->height + offsetY,
                        offsetX + (tf->width) * 2,
                        offsetX + (tf->width) * 2 + 14);

  // Отрисовка статистики
  print_game_statistics(tetg);

  if (tetg->pause) {
    showPauseScreen();
  }

  refresh();
}

/**
 * @brief Экран старта игры.
 */
void showStartScreen(void) {
  initscr();
  noecho();
  curs_set(0);

  int top_y = 0, bottom_y = 20, left_x = 1, right_x = 22;

  draw_game_area_border(top_y, bottom_y, left_x, right_x);
  draw_game_area_border(top_y, bottom_y, left_x + 21, right_x + 14);
  draw_centered_text(top_y, bottom_y, left_x, right_x, "Press S to start");

  while (getch() != 's' && getch() != 'S') {
    // Ожидание нажатия клавиши 'S' или 's'
  }

  clear();
  refresh();
  endwin();
}

/**
 * @brief Экран проигрыша.
 */
void showEndScreen(void) {
  initscr();
  noecho();
  curs_set(0);

  int top_y = 0, bottom_y = 20, left_x = 1, right_x = 22;

  draw_game_area_border(top_y, bottom_y, left_x, right_x);
  draw_game_area_border(top_y, bottom_y, left_x + 21, right_x + 14);
  draw_centered_text(top_y, bottom_y, left_x, right_x, "Game Over");

  while (getch() != 's' && getch() != 'S') {
    // Ожидание нажатия клавиши 'S' или 's'
  }

  clear();
  refresh();
  endwin();
}

/**
 * @brief Экран Паузы.
 */
void showPauseScreen(void) {
  int top_y = 0, bottom_y = 20, left_x = 1, right_x = 22;

  draw_game_area_border(top_y, bottom_y, left_x, right_x);
  draw_game_area_border(top_y, bottom_y, left_x + 21, right_x + 14);
  draw_centered_text(top_y, bottom_y, left_x, right_x, "Pause");
}
