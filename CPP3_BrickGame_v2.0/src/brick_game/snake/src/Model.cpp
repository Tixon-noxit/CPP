//
// Created by Тихон Чабусов on 22.08.2024.
//

#include "../inc/Model.h"

#include <fstream>
#include <iostream>

#include "../../../common/inc/common.h"
#include "../../../common/inc/defines.h"

using namespace s21;

/**
 * @class Конструктор класса
 */
SnakeModel::SnakeModel() {
  // Инициализируем случайные числа
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  // Инициализируем игру
  InitializeGame();
}

/**
 * @brief Устанавливает паузу в игре
 */
void SnakeModel::SetPause() {
  tetg_ = get_current_game_info();
  tetg_->pause = !tetg_->pause;
}

/**
 * @brief Инициализация начального состояния змейки, яблока и других игровых
 * данных
 */
void SnakeModel::InitializeGame() {
  tetg_ = get_current_game_info();
  // Очистка и инициализация игрового поля
  if (tetg_->field != nullptr) {
    delete[] tetg_->field->blocks;  // Освобождаем ранее выделенную память
    delete tetg_->field;
  }

  tetg_->field = new TetField;
  tetg_->field->width = FIELD_WIDTH;
  tetg_->field->height = FIELD_HEIGHT;
  tetg_->field->blocks =
      new TetBlock[tetg_->field->width *
                   tetg_->field->height]();  // Инициализируем блоки

  // Устанавливаем начальные параметры игры
  tetg_->score = 4;
  tetg_->high_score = ReadScore();
  tetg_->level = 0;
  tetg_->pause = 0;
  tetg_->speed = 400;
  tetg_->ticks = 700;

  // Инициализация фигуры
  if (tetg_->figure != nullptr) {
    delete tetg_->figure;  // Освобождаем предыдущую фигуру
  }
  tetg_->figure = new TetFigure;  // Создаём новую фигуру
  tetg_->figure->size = 0;
  tetg_->figure->blocks = tetg_->field->blocks;
  tetg_->figure->x = tetg_->field->width / 2;  // Помещаем фигуру в центр по X
  tetg_->figure->y = 0;  // Начальная позиция по Y (верх игрового поля)

  direction_ = {1, 0};  // Начальное направление: вправо

  // Инициализация змейки
  // Начальная длина змейки равна 4, помещаем её в центр игрового поля
  int snake_start_x = 10;
  int snake_start_y = 4;

  // Очищаем поле перед инициализацией змейки
  std::fill(tetg_->field->blocks,
            tetg_->field->blocks + (tetg_->field->width * tetg_->field->height),
            TetBlock{0});

  // Добавляем сегменты змейки
  snake_body_.clear();  // Очистка тела змейки перед началом
  for (int i = 0; i < 4; ++i) {
    int x = snake_start_x;
    int y = snake_start_y + i;
    int index = (x * tetg_->field->width) + y;
    tetg_->field->blocks[index].b = 1;
    snake_body_.emplace_back(x, y);
  }

  // Генерация первого яблока
  SpawnApple();
}

/**
 * @brief Обновление состояния игры
 */
void SnakeModel::UpdateState() {
  if (!tetg_->pause) {
    MoveSnake();
  }
}

/**
 * @brief Изменение направления в зависимости от текущего направления
 * @param action - направление выбранное пользователем
 */
void SnakeModel::ChangeDirection(UserAction_t action) {
  if (action == UserAction_t::Left) {
    direction_ = {-direction_.second, direction_.first};  // Поворот налево
  } else if (action == UserAction_t::Right) {
    direction_ = {direction_.second, -direction_.first};  // Поворот направо
  }
}

/**
 * @brief Проверка столкновения с яблоком
 * @param new_head_position - Позиция головы змейки после съедания яблока
 * @return
 */
bool SnakeModel::CheckAppleCollision(
    const std::pair<int, int>& new_head_position) {
  return (new_head_position.first == apple_x_ &&
          new_head_position.second == apple_y_);
}

/**
 * @brief Установка нового значения для головы змейки при соблюдении условий
 * игры
 * @param new_head_position
 */
void SnakeModel::AddNewHead(const std::pair<int, int>& new_head_position) {
  // Добавляем новый сегмент в хвост (не удаляем хвост)
  snake_body_.push_front(new_head_position);

  // Обновляем поле: добавляем голову на новую позицию
  int new_index =
      new_head_position.first * tetg_->field->width + new_head_position.second;
  tetg_->field->blocks[new_index].b = 1;
  ++tetg_->score;
  if (tetg_->score > tetg_->high_score) {
    SaveScore(tetg_->score);
    tetg_->high_score = tetg_->score;
  }

  int proper_level = floor(tetg_->score / 5);

  if (tetg_->score > 0) {
    if (proper_level > tetg_->level && tetg_->level < 10) {
      tetg_->level = proper_level;
      tetg_->ticks *= 0.9;  // Увеличить скорость
    }
  }

  if (tetg_->score == 200) {
    tetg_->player->action = Terminate;
  }
}

/**
 * @brief Мониторинг движения змейки на поле
 */
void SnakeModel::MoveSnake() {
  if (snake_body_.empty()) {
    return;
  }

  if (!IsApplePresent()) {
    SpawnApple();
  }

  // Текущая позиция головы змейки
  auto head_position = snake_body_.front();

  // Новая позиция головы
  auto new_head_position =
      std::make_pair(head_position.first + direction_.first,
                     head_position.second + direction_.second);

  // Проверка на столкновение (с краями поля или телом змейки)
  if (CheckCollision(new_head_position)) {
    tetg_->playing = Terminate;
    return;
  }

  if (CheckAppleCollision(new_head_position)) {
    if (!IsApplePresent()) {
      SpawnApple();
    }
    AddNewHead(new_head_position);
  }

  // Добавить новую голову змейки
  snake_body_.push_front(new_head_position);

  // Удалить последний сегмент хвоста, чтобы змейка оставалась той же длины
  auto tail_position = snake_body_.back();
  snake_body_.pop_back();

  // Обновить поле: удалить хвост змейки с карты
  int tail_index =
      tail_position.first * tetg_->field->width + tail_position.second;
  tetg_->field->blocks[tail_index].b = 0;

  // Обновить поле: добавить голову змейки на новую позицию
  int new_index =
      new_head_position.first * tetg_->field->width + new_head_position.second;
  tetg_->field->blocks[new_index].b = 1;
}

/**
 * @brief Проверка столкновений змейки с границами или своим телом
 * @param new_head_position - новая позиция головы змейки в такте
 * @return bool - Было ли столкновение
 */
bool SnakeModel::CheckCollision(const std::pair<int, int>& new_head_position) {
  // Проверка на столкновение с границами поля
  if (new_head_position.first < 0 ||
      new_head_position.first >= tetg_->field->height ||
      new_head_position.second < 0 ||
      new_head_position.second >= tetg_->field->width) {
    return true;
  }

  // Проверка на столкновение с телом змейки
  int new_index =
      new_head_position.first * tetg_->field->width + new_head_position.second;
  if (tetg_->field->blocks[new_index].b == 1) {
    return true;
  }

  return false;
}

/**
 * @brief Поиск яблока на поле
 * @return
 */
bool SnakeModel::IsApplePresent() const {
  // Перебираем все блоки на поле
  for (int x = 0; x < tetg_->field->height; ++x) {
    for (int y = 0; y < tetg_->field->width; ++y) {
      int index = x * tetg_->field->width + y;
      if (tetg_->field->blocks[index].b == 2) {  // 2 - яблоко
        return true;                             // Яблоко найдено
      }
    }
  }
  return false;  // Яблоко не найдено
}

/**
 * @brief Генерация и расположение яблока на поле
 */
void SnakeModel::SpawnApple() {
  int apple_x, apple_y;
  bool is_free;

  do {
    apple_x = std::rand() % tetg_->field->height;
    apple_y = std::rand() % tetg_->field->width;

    int index = apple_x * tetg_->field->width + apple_y;

    // Проверка, что на этой позиции нет ни части змейки, ни другого яблока
    is_free = tetg_->field->blocks[index].b == 0;
  } while (!is_free);

  // Помещаем яблоко на свободную позицию
  int apple_index = apple_x * tetg_->field->width + apple_y;
  tetg_->field->blocks[apple_index].b = 2;  // 2 - яблоко
  apple_x_ = apple_x;
  apple_y_ = apple_y;
}

// Работа с файлами

/**
 * @brief Запись максимально набранного счета игрока в файл
 * @param score
 */
void SnakeModel::SaveScore(int score) const {
  // Открываем файл для записи. std::ios::trunc обрезает файл до нуля байт.
  std::ofstream file(filename, std::ios::trunc);
  if (!file) {
    std::cerr << "Ошибка при открытии файла для записи." << std::endl;
    return;
  }

  // Записываем сумму очков в файл
  file << score << std::endl;

  // Закрываем файл
  file.close();

  if (!file.good()) {
    std::cerr << "Ошибка при записи в файл." << std::endl;
  }
}

/**
 * @brief Считывание максимального счета из файла
 * @return Рекорд игрока
 */
int SnakeModel::ReadScore() const {
  std::ifstream file(filename);
  if (!file) {
    SaveScore(4);
  }

  int score = 4;
  // Читаем значение рекорда из файла
  if (!(file >> score)) {
    std::cerr << "Ошибка при чтении рекорда из файла или файл пуст."
              << std::endl;
    file.close();
    return score;  // Возвращаем -1 в случае ошибки чтения
  }

  file.close();
  return score;
}
