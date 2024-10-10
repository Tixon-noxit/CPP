//
// Created by Тихон Чабусов on 07.05.2024.
//

#include "test.h"

void writeTestMaxScore(const char *filename, int score) {
  FILE *file = fopen(filename, "w");
  if (file != NULL) {
    fprintf(file, "%d", score);
    fclose(file);
  }
}

// Создание и освобождение GameInfo для тестов
GameInfo_t *createMockGameInfo(void) {
  GameInfo_t *game_info = malloc(sizeof(GameInfo_t));
  game_info->field = createTetField(10, 20);
  game_info->figure = malloc(sizeof(TetFigure));
  game_info->next_figure = malloc(sizeof(TetFigure));
  game_info->figurest = malloc(sizeof(TetFiguresT));
  game_info->player = malloc(sizeof(TetPlayer));
  game_info->ticks = 10;
  game_info->ticks_left = 10;
  game_info->score = 0;
  game_info->playing = Start;
  return game_info;
}

void freeMockGameInfo(GameInfo_t *game_info) {
  free(game_info->field);
  free(game_info->figure);
  free(game_info->next_figure);
  free(game_info->figurest);
  free(game_info->player);
  free(game_info);
}

START_TEST(createTetField_test) {
  int width = 10;
  int height = 20;
  TetField *field = createTetField(width, height);

  ck_assert_ptr_nonnull(field);             // поле не NULL
  ck_assert_int_eq(field->width, width);    // ширина
  ck_assert_int_eq(field->height, height);  // высота
  ck_assert_ptr_nonnull(field->blocks);     // блоки не NULL

  for (int i = 0; i < width * height; i++) {
    ck_assert_int_eq(field->blocks[i].b,
                     0);  // все блоки инициализированы как 0
  }

  // Освобождаем память
  free(field->blocks);
  free(field);
}

END_TEST

// Тест для moveFigureDown
START_TEST(test_moveFigureDown) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure = malloc(sizeof(TetFigure));  // Инициализируем фигуру
  tetg->figure->x = 0;
  tetg->figure->y = 0;
  moveFigureDown();
  ck_assert_int_eq(tetg->figure->y, 1);

  // Освобождаем память
  free(tetg->figure);
}

END_TEST

// Тест для moveFigureUp
START_TEST(test_moveFigureUp) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure = malloc(sizeof(TetFigure));  // Инициализируем фигуру
  tetg->figure->x = 0;
  tetg->figure->y = 0;
  moveFigureUp();
  ck_assert_int_eq(tetg->figure->y, -1);

  // Освобождаем память
  free(tetg->figure);
}

END_TEST

// Тест для moveFigureLeft
START_TEST(test_moveFigureLeft) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure = malloc(sizeof(TetFigure));  // Инициализируем фигуру
  tetg->figure->x = 0;
  tetg->figure->y = 0;
  moveFigureLeft();
  ck_assert_int_eq(tetg->figure->x, -1);

  // Освобождаем память
  free(tetg->figure);
}

END_TEST

// Тест для moveFigureRight
START_TEST(test_moveFigureRight) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure = malloc(sizeof(TetFigure));  // Инициализируем фигуру
  tetg->figure->x = 0;
  tetg->figure->y = 0;
  moveFigureRight();
  ck_assert_int_eq(tetg->figure->x, 1);

  // Освобождаем память
  free(tetg->figure);
}

END_TEST

// Тест для freeTetField
START_TEST(freeTetField_test) {
  int width = 10;
  int height = 20;
  TetField *field = createTetField(width, height);
  ck_assert_ptr_nonnull(field);  // поле не NULL
  freeTetField(field);
}

END_TEST

// Тест для lineFieldTet
START_TEST(test_lineFieldTet) {
  int width = 10;
  int height = 20;
  TetField *field = createTetField(width, height);

  // поле создано успешно
  ck_assert_ptr_nonnull(field);

  // Заполнить строку 5 полностью
  for (int j = 0; j < width; j++) {
    field->blocks[5 * width + j].b = 1;
  }

  // Проверить, что строка 5 полностью заполнена
  ck_assert_int_eq(lineFieldTet(5, field), 1);

  // Заполнить строку 10 частично
  for (int j = 0; j < width / 2; j++) {
    field->blocks[10 * width + j].b = 1;
  }

  // Проверить, что строка 10 не полностью заполнена
  ck_assert_int_eq(lineFieldTet(10, field), 0);

  // Проверить пустую строку
  ck_assert_int_eq(lineFieldTet(15, field), 0);

  freeTetField(field);
}

END_TEST

// Тест для dropLineTet
START_TEST(test_dropLineTet) {
  int width = 10;
  int height = 20;
  TetField *field = createTetField(width, height);

  // Поле создано успешно
  ck_assert_ptr_nonnull(field);

  // Строки для тестирования
  for (int j = 0; j < width; j++) {
    field->blocks[1 * width + j].b = 1;  // Заполняем строку 1
    field->blocks[2 * width + j].b = 2;  // Заполняем строку 2
  }

  // Состояние до сдвига
  for (int j = 0; j < width; j++) {
    ck_assert_int_eq(field->blocks[1 * width + j].b, 1);
    ck_assert_int_eq(field->blocks[2 * width + j].b, 2);
  }

  // Сдвиг строки 2
  dropLineTet(2, field);

  // Проверить состояние после сдвига
  for (int j = 0; j < width; j++) {
    ck_assert_int_eq(field->blocks[1 * width + j].b,
                     0);  // Строка 1 должна быть очищена
    ck_assert_int_eq(field->blocks[2 * width + j].b,
                     1);  // Строка 2 должна быть сдвинута на место строки 1
  }

  // Освобождаем память
  freeTetField(field);
}

END_TEST

// Тест для get_current_game_info
START_TEST(test_get_current_game_info) {
  // Указатель на текущее состояние игры
  GameInfo_t *game_info_1 = get_current_game_info();
  ck_assert_ptr_nonnull(game_info_1);

  game_info_1->score = 50;
  game_info_1->level = 1;
  game_info_1->playing = 1;

  // Указатель на текущее состояние игры снова
  GameInfo_t *game_info_2 = get_current_game_info();
  ck_assert_ptr_nonnull(game_info_2);
  ck_assert_ptr_eq(game_info_1, game_info_2);
  ck_assert_int_eq(game_info_2->score, 50);
  ck_assert_int_eq(game_info_2->level, 1);
  ck_assert_int_eq(game_info_2->playing, 1);

  game_info_2->score = 100;
  game_info_2->level = 2;

  ck_assert_int_eq(game_info_1->score, 100);
  ck_assert_int_eq(game_info_1->level, 2);
}

END_TEST

// Тест createGameInfo_t
START_TEST(test_createGameInfo_t) {
  int field_width = 10;
  int field_height = 20;
  int figures_size = 3;
  int count = 5;

  TetBlock template[3 * 3 * 5] = {
      {0}, {0}, {0}, {0}, {1}, {0}, {0}, {0}, {0},
  };

  // Инициализация игровых параметров
  createGameInfo_t(field_width, field_height, figures_size, count, template);

  // Текущее состояние игры
  GameInfo_t *game_info = get_current_game_info();
  ck_assert_ptr_nonnull(game_info);

  ck_assert_ptr_nonnull(game_info->field);
  ck_assert_int_eq(game_info->field->width, field_width);
  ck_assert_int_eq(game_info->field->height, field_height);

  // Параметры набора фигур
  ck_assert_ptr_nonnull(game_info->figurest);
  ck_assert_int_eq(game_info->figurest->count, count);
  ck_assert_int_eq(game_info->figurest->size, figures_size);
  ck_assert_ptr_nonnull(game_info->figurest->blocks);

  // Инициализация других параметров
  //  ck_assert_int_eq(game_info->ticks, TET_TICK_START);
  ck_assert_int_eq(game_info->ticks_left, TET_TICK_START);
  ck_assert_int_eq(game_info->score, 0);
  ck_assert_ptr_nonnull(game_info->next_figure);
  ck_assert_int_eq(game_info->level, 0);
  ck_assert_ptr_nonnull(game_info->player);
  ck_assert_int_eq(game_info->player->action, TET_PLAYER_NOP);
  ck_assert_int_eq(game_info->playing, Start);

  free(game_info->field->blocks);
  free(game_info->field);
  free(game_info->figurest);
  free(game_info->next_figure->blocks);
  free(game_info->next_figure);
  free(game_info->player);
}

END_TEST

START_TEST(test_updateMaxScore) {
  const char *test_file = "max_score.txt";

  // Начальный максимальный счет
  int initial_score = 100;
  writeTestMaxScore(test_file, initial_score);

  // Файл был создан и содержит начальный максимальный счет
  int read_score = readMaxScore(test_file);
  ck_assert_int_eq(read_score, initial_score);

  // Обновить максимальный счет, если новый счет больше
  int new_score = 150;
  updateMaxScore(test_file, new_score);

  // Максимальный счет обновился
  read_score = readMaxScore(test_file);
  ck_assert_int_eq(read_score, new_score);

  // Максимальный счет не обновляется, если новый счет меньше
  new_score = 50;
  updateMaxScore(test_file, new_score);

  // Максимальный счет остался прежним
  read_score = readMaxScore(test_file);
  ck_assert_int_eq(read_score, 150);

  // Удалить тестовый файл
  remove(test_file);
}

END_TEST

// Тест для calculateTet
START_TEST(test_calculateTet_no_collision) {
  GameInfo_t *game_info = createMockGameInfo();
  game_info->figure->y = 0;
  game_info->ticks_left = 0;

  calculateTet();

  ck_assert_int_eq(game_info->figure->y, 0);
  ck_assert_int_eq(game_info->ticks_left, 0);

  freeMockGameInfo(game_info);
}

END_TEST

START_TEST(test_calculateTet_with_collision) {
  GameInfo_t *game_info = createMockGameInfo();
  game_info->figure->y = 0;
  game_info->ticks_left = 0;

  calculateTet();

  ck_assert_int_eq(game_info->figure->y, 0);
  ck_assert_int_eq(game_info->ticks_left, 0);

  freeMockGameInfo(game_info);
}

END_TEST

START_TEST(test_calculateTet_erase_lines) {
  GameInfo_t *game_info = createMockGameInfo();
  game_info->ticks_left = 0;

  calculateTet();

  ck_assert_int_eq(game_info->score, 0);
  ck_assert_int_eq(game_info->ticks_left, 0);

  freeMockGameInfo(game_info);
}

END_TEST

START_TEST(test_calculateTet_game_over) {
  GameInfo_t *game_info = createMockGameInfo();
  game_info->ticks_left = 0;

  calculateTet();

  ck_assert_int_eq(game_info->playing, 0);
  ck_assert_int_eq(game_info->ticks_left, 0);

  freeMockGameInfo(game_info);
}

END_TEST

START_TEST(test_calculateTet_drop_new_figure_no_collision) {
  GameInfo_t *game_info = createMockGameInfo();

  game_info->figure->y = 0;

  TetFigure *new_figure = malloc(sizeof(TetFigure));
  new_figure->blocks = malloc(5 * 5 * sizeof(TetBlock));
  game_info->next_figure = new_figure;

  calculateTet();

  ck_assert_int_eq(game_info->playing, Start);
  ck_assert_int_eq(game_info->ticks_left, 10);

  freeMockGameInfo(game_info);
}

END_TEST

START_TEST(test_calculateTet_drop_new_figure_with_collision) {
  GameInfo_t *game_info = createMockGameInfo();

  game_info->figure->y = 0;

  TetFigure *new_figure = malloc(sizeof(TetFigure));
  new_figure->blocks = malloc(5 * 5 * sizeof(TetBlock));
  game_info->next_figure = new_figure;

  calculateTet();

  ck_assert_int_eq(game_info->playing, 0);
  ck_assert_int_eq(game_info->ticks_left, 10);

  freeMockGameInfo(game_info);
}

END_TEST

START_TEST(test_calculateTet_moveFigureDown) {
  GameInfo_t *game_info = createMockGameInfo();

  game_info->figure->y = 0;
  game_info->ticks_left = 0;

  TetFigure *new_figure = malloc(sizeof(TetFigure));
  new_figure->blocks = malloc(5 * 5 * sizeof(TetBlock));
  game_info->next_figure = new_figure;

  calculateTet();

  ck_assert_int_eq(game_info->playing, 0);

  freeMockGameInfo(game_info);
}

END_TEST

START_TEST(test_score_add_single_line) {
  GameInfo_t *game_info = createMockGameInfo();

  score_add(1);
  score_add(2);
  score_add(3);
  score_add(4);

  ck_assert_int_eq(game_info->score, 0);

  freeMockGameInfo(game_info);
}

END_TEST

// Тест для freeGameInfo_t
START_TEST(test_freeGameInfo_t_all_allocated) {
  GameInfo_t *game_info = createMockGameInfo();

  TetField *field = game_info->field;
  TetFiguresT *figurest = game_info->figurest;
  TetPlayer *player = game_info->player;

  // Вызов тестируемой функции
  freeGameInfo_t();

  ck_assert_ptr_eq(game_info->field, field);
  ck_assert_ptr_eq(game_info->figurest, figurest);
  ck_assert_ptr_eq(game_info->player, player);

  freeMockGameInfo(game_info);
}

END_TEST

START_TEST(test_userInput_Left) {
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();
  tetg->player->action = Left;
  userInput(tetg->player->action, false);
  freeGameInfo_t();
}

END_TEST

START_TEST(test_userInput_Right) {
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();

  // Начальная позиция фигуры
  int initial_x = tetg->figure->x;

  tetg->player->action = Right;
  userInput(tetg->player->action, false);

  // Проверка новой позиции фигуры
  ck_assert_int_eq(tetg->figure->x, initial_x + 1);

  freeGameInfo_t();
}

END_TEST

START_TEST(test_userInput_Down) {
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();

  tetg->player->action = Down;
  userInput(tetg->player->action, false);

  // Проверка новой позиции фигуры
  //  ck_assert_int_eq(tetg->figure->y, 1);

  freeGameInfo_t();
}

END_TEST

START_TEST(test_userInput_TET_PLAYER_NOP) {
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();
  tetg->player->action = TET_PLAYER_NOP;
  userInput(tetg->player->action, false);
  freeGameInfo_t();
}

END_TEST

START_TEST(test_userInput_Action) {
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();
  tetg->figure = createTetFigure();
  tetg->player->action = Action;
  userInput(tetg->player->action, false);
  freeGameInfo_t();
}

END_TEST

START_TEST(test_userInput_ESCAPE_BTN) {
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();
  tetg->player->action = ESCAPE_BTN;
  userInput(tetg->player->action, false);

  freeGameInfo_t();
}

END_TEST

START_TEST(test_plantFigure) {
  // Инициализация игры
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();
  TetField *tf = tetg->field;
  createTetFigure();
  TetFigure *t = tetg->figure;

  // Установка начальной позиции фигуры
  t->x = 3;
  t->y = 0;
  // Заполнение блоков фигуры
  for (int i = 0; i < t->size; i++) {
    for (int j = 0; j < t->size; j++) {
      t->blocks[i * t->size + j].b =
          1;  // Предполагаем, что все блоки фигуры заполнены
    }
  }

  // Вызов функции plantFigure
  plantFigure();

  // Проверка размещения блоков фигуры в игровом поле
  for (int i = 0; i < t->size; i++) {
    for (int j = 0; j < t->size; j++) {
      int fx = t->x + j;
      int fy = t->y + i;
      ck_assert_int_eq(tf->blocks[fy * tf->width + fx].b, 1);
    }
  }

  // Очистка ресурсов
  freeGameInfo_t();
}
END_TEST

START_TEST(test_eraseLinesTet) {
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();
  TetField *tfl = tetg->field;

  // Заполнение нескольких строк игрового поля
  for (int i = tfl->height - 1; i >= tfl->height - 3; i--) {
    for (int j = 0; j < tfl->width; j++) {
      tfl->blocks[i * tfl->width + j].b =
          1;  // Предполагаем, что блок заполнен значением 1
    }
  }

  // Проверка, что строки заполнены
  for (int i = tfl->height - 1; i >= tfl->height - 3; i--) {
    ck_assert_int_eq(lineFieldTet(i, tfl),
                     1);  // Проверяем, что строка заполнена
  }

  // Вызов функции eraseLinesTet и проверка результата
  int erased_lines = eraseLinesTet();
  ck_assert_int_eq(erased_lines, 3);  // Проверяем, что было удалено 3 строки

  // Проверка, что строки удалены
  for (int i = tfl->height - 1; i >= tfl->height - 3; i--) {
    for (int j = 0; j < tfl->width; j++) {
      ck_assert_int_eq(tfl->blocks[i * tfl->width + j].b,
                       0);  // Проверяем, что строки очищены
    }
  }

  freeGameInfo_t();
}

END_TEST

// START_TEST(test_updateCurrentState) {
//     createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
//     GameInfo_t tetg = updateCurrentState();
//     TetFigure *t = (TetFigure *)malloc(sizeof(TetFigure));
//     t->size = tetg.figurest->size;
//     t->blocks = (TetBlock *)malloc(sizeof(TetBlock) * t->size * t->size);
//
//     freeTetFigure(t);
//     freeGameInfo_t();
//
// }
//
// END_TEST

START_TEST(test_updateCurrentState) {
  // Инициализация игрового состояния
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *initial_tetg = get_current_game_info();
  createTetFigure();

  // Изменение состояния игры
  initial_tetg->score = 100;
  initial_tetg->level = 2;
  initial_tetg->figure->x = 3;
  initial_tetg->figure->y = 5;

  // Вызов функции updateCurrentState
  GameInfo_t updated_tetg = updateCurrentState();

  // Проверка, что возвращенное состояние совпадает с ожидаемым
  ck_assert_int_eq(updated_tetg.score, 100);
  ck_assert_int_eq(updated_tetg.level, 2);
  ck_assert_int_eq(updated_tetg.figure->x, 3);
  ck_assert_int_eq(updated_tetg.figure->y, 5);

  // Очистка ресурсов
  freeGameInfo_t();
}

END_TEST

START_TEST(test_dropNewFigure) {
  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();

  TetFigure *initial_figure = tetg->figure;
  TetFigure *initial_next_figure = tetg->next_figure;

  dropNewFigure();

  // Проверяем, что новые фигуры созданы и не равны старым
  ck_assert_ptr_ne(tetg->figure, initial_figure);
  ck_assert_ptr_ne(tetg->next_figure, initial_next_figure);

  // Проверяем, что память под новые фигуры выделена
  ck_assert_ptr_nonnull(tetg->figure);
  ck_assert_ptr_nonnull(tetg->next_figure);

  // Освобождение ресурсов
  freeGameInfo_t();
}
END_TEST

// START_TEST(test_rotete_figure)
//{
//     createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
//     GameInfo_t *tetg = get_current_game_info();
//     tetg->playing = Action;
//
//
// }
// END_TEST

// START_TEST(test_rotTetFigure_allocation) {
//     createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
//     GameInfo_t *tetg = get_current_game_info();
//
//     // Задаем начальные координаты для текущей фигуры
//     tetg->figure->x = 3;
//     tetg->figure->y = 4;
//     int x = tetg->figure->x;
//     int y = tetg->figure->y;
//
//     rotTetFigure();
//
//     // Проверяем, что координаты скопированы правильно
//     ck_assert_int_eq(x, tetg->figure->x);
//     ck_assert_int_eq(y, tetg->figure->y);
//
//     // Освобождение ресурсов
////    freeTetFigure(rotated_figure);
//    freeGameInfo_t();
//}
// END_TEST

Suite *example_create(void) {
  Suite *suite = suite_create("TESTS");

  TCase *tc_createTetField = tcase_create("s21_createTetField_test_case_2");
  tcase_add_test(tc_createTetField, createTetField_test);
  suite_add_tcase(suite, tc_createTetField);

  TCase *tc_RLUD = tcase_create("MoveFigure");
  tcase_add_test(tc_RLUD, test_moveFigureDown);
  tcase_add_test(tc_RLUD, test_moveFigureUp);
  tcase_add_test(tc_RLUD, test_moveFigureLeft);
  tcase_add_test(tc_RLUD, test_moveFigureRight);
  suite_add_tcase(suite, tc_RLUD);

  //  TCase *tc_rotTetFigure = tcase_create("rotTetFigure");
  //  tcase_add_test(tc_rotTetFigure, test_rotTetFigure_allocation);
  //  suite_add_tcase(suite, tc_rotTetFigure);

  TCase *tc_Free = tcase_create("FreeMemory");
  tcase_add_test(tc_Free, freeTetField_test);
  tcase_add_test(tc_Free, test_freeGameInfo_t_all_allocated);
  suite_add_tcase(suite, tc_Free);

  TCase *tc_lineFieldTet = tcase_create("lineFieldTet");
  tcase_add_test(tc_lineFieldTet, test_lineFieldTet);
  suite_add_tcase(suite, tc_lineFieldTet);

  TCase *tc_dropLineTet = tcase_create("dropLineTet");
  tcase_add_test(tc_dropLineTet, test_dropLineTet);
  suite_add_tcase(suite, tc_dropLineTet);

  TCase *tc_test_get_current_game_info =
      tcase_create("test_get_current_game_info");
  tcase_add_test(tc_test_get_current_game_info, test_get_current_game_info);
  suite_add_tcase(suite, tc_test_get_current_game_info);

  TCase *tc_test_createGameInfo_t = tcase_create("test_createGameInfo_t");
  tcase_add_test(tc_test_createGameInfo_t, test_createGameInfo_t);
  suite_add_tcase(suite, tc_test_createGameInfo_t);

  TCase *tc_test_updateMaxScore = tcase_create("test_updateMaxScore");
  tcase_add_test(tc_test_updateMaxScore, test_updateMaxScore);
  suite_add_tcase(suite, tc_test_updateMaxScore);

  TCase *tc_test_calculateTet = tcase_create("test_calculateTet");
  tcase_add_test(tc_test_calculateTet, test_calculateTet_no_collision);
  tcase_add_test(tc_test_calculateTet, test_calculateTet_with_collision);
  tcase_add_test(tc_test_calculateTet, test_calculateTet_erase_lines);
  tcase_add_test(tc_test_calculateTet, test_calculateTet_game_over);
  tcase_add_test(tc_test_calculateTet,
                 test_calculateTet_drop_new_figure_no_collision);
  tcase_add_test(tc_test_calculateTet,
                 test_calculateTet_drop_new_figure_with_collision);
  tcase_add_test(tc_test_calculateTet, test_calculateTet_moveFigureDown);
  suite_add_tcase(suite, tc_test_calculateTet);

  TCase *tc_score_add = tcase_create("score_add");
  tcase_add_test(tc_score_add, test_score_add_single_line);
  suite_add_tcase(suite, tc_score_add);

  TCase *tc_test_userInput_self_1 = tcase_create("test_userInput");
  tcase_add_test(tc_test_userInput_self_1, test_userInput_Left);
  tcase_add_test(tc_test_userInput_self_1, test_userInput_Right);
  tcase_add_test(tc_test_userInput_self_1, test_userInput_Down);
  tcase_add_test(tc_test_userInput_self_1, test_userInput_TET_PLAYER_NOP);
  tcase_add_test(tc_test_userInput_self_1, test_userInput_Action);
  tcase_add_test(tc_test_userInput_self_1, test_userInput_ESCAPE_BTN);
  suite_add_tcase(suite, tc_test_userInput_self_1);

  TCase *tc_plantFigure = tcase_create("plantFigure");
  tcase_add_test(tc_plantFigure, test_plantFigure);
  suite_add_tcase(suite, tc_plantFigure);

  TCase *tc_eraseLinesTet = tcase_create("eraseLinesTet");
  tcase_add_test(tc_eraseLinesTet, test_eraseLinesTet);
  suite_add_tcase(suite, tc_eraseLinesTet);

  TCase *tc_updateCurrentState = tcase_create("updateCurrentState");
  tcase_add_test(tc_updateCurrentState, test_updateCurrentState);
  suite_add_tcase(suite, tc_updateCurrentState);

  TCase *tc_test_dropNewFigure = tcase_create("test_dropNewFigure");
  tcase_add_test(tc_test_dropNewFigure, test_dropNewFigure);
  suite_add_tcase(suite, tc_test_dropNewFigure);

  return suite;
}

int main(void) {
  Suite *s = example_create();
  SRunner *runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  int count = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
