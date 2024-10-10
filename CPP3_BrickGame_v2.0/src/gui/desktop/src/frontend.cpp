//
// Created by Тихон Чабусов on 25.08.2024.
//

#include "../inc/frontend.h"

#include <QAbstractItemModel>
#include <QApplication>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>

using namespace s21;

View::View(IController* controller, QWidget* parent)
    : QGraphicsView(parent), controller_(controller) {
  scene_ = new QGraphicsScene(this);
  setScene(scene_);

  // Создаем таймер
  update_timer_ = new QTimer(this);

  // Соединяем сигнал таймера с методом UpdateView
  connect(update_timer_, &QTimer::timeout, this, &View::UpdateView);

  // Запускаем таймер с интервалом в 16 миллисекунд (примерно 60 FPS)
  update_timer_->start(16);
}

/**
 * @brief Иницифлизация главного окна игры
 */
void View::InitializeView() {
  GameInfo_t* tetg = get_current_game_info();

  // Задаем размеры для игровых кубиков и статистики
  int gameFieldWidth = tetg->field->width * cell_size_;
  int gameFieldHeight = tetg->field->height * cell_size_;
  int statsWidth =
      gameFieldWidth / 2;  // Делаем ширину области статистики в два раза меньше

  // Устанавливаем размеры сцены: поле для игры и панель статистики
  scene_->setSceneRect(0, 0, gameFieldWidth + statsWidth, gameFieldHeight);

  // Устанавливаем размер виджета (окна)
  this->setFixedSize(gameFieldWidth + statsWidth + 2,
                     gameFieldHeight + 2);  // Немного увеличиваем для рамки

  UpdateView();
}

/**
 * @brief Устанавливает цвет в зависимости от значения игрового блока
 * @param blockType
 * @return Объект цвета QColor
 */
QColor GetBlockColor(int blockType) {
  switch (blockType) {
    case 1:
      return Qt::green;  // Тип 3 — зелёный блок
    case 2:
      return Qt::red;  // Например, тип 1 — это красный блок
    case 3:
      return Qt::blue;  // Тип 2 — синий блок
    default:
      return Qt::black;  // По умолчанию чёрный
  }
}

/**
 * @brief обновление состояния игры
 */
void View::UpdateView() {
  scene_->clear();

  // Получаем игровое поле
  GameInfo_t* tetg = get_current_game_info();
  // Окантовка игрового поля
  QPen border_pen(Qt::white);
  border_pen.setWidth(3);
  scene_->addRect(0, 0, tetg->field->width * cell_size_,
                  tetg->field->height * cell_size_, border_pen);

  // Проходим по всем блокам игрового поля и рисуем их
  for (int y = 0; y < tetg->field->height; ++y) {
    for (int x = 0; x < tetg->field->width; ++x) {
      // Текущий блок
      TetBlock& block = tetg->field->blocks[y * tetg->field->width + x];

      // Если блок не пуст
      if (block.b != 0) {
        // Графический элемент для отображения блока
        QGraphicsRectItem* rect =
            new QGraphicsRectItem(x * cell_size_,  // Позиция по X
                                  y * cell_size_,  // Позиция по Y
                                  cell_size_,      // Ширина блока
                                  cell_size_       // Высота блока
            );

        rect->setBrush(QBrush(GetBlockColor(block.b)));

        // Вывод блока на сцену
        scene_->addItem(rect);
      }
    }
  }

  // Отрисовка панели статистики
  DrawStatsPanel();

  if (tetg->pause) {
    ShowGamePause();
  }

  if (tetg->playing == Terminate) {
    ShowGameOver();
  }
}

/**
 * @brief отрисовка панели статистики игры
 */
void View::DrawStatsPanel() {
  GameInfo_t* tetg = get_current_game_info();

  int statsX =
      tetg->field->width * cell_size_ + 10;  // Начало панели статистики
  int statsWidth = 200;  // Ширина панели статистики
  int statsHeight =
      tetg->field->height * cell_size_;  // Высота панели статистики
  int yPos = 20;  // Начальная Y позиция для каждого элемента статистики

  // Окантовка панели статистики
  QPen stats_border_pen(Qt::white);
  stats_border_pen.setWidth(3);
  scene_->addRect(statsX - 10, 0, statsWidth, statsHeight, stats_border_pen);

  QFont font("Arial", 14);

  // Очки
  QGraphicsTextItem* scoreLabel = scene_->addText("SCORE", font);
  scoreLabel->setPos(statsX, yPos);
  QGraphicsTextItem* scoreValue =
      scene_->addText(QString::number(tetg->score), font);
  scoreValue->setPos(statsX + 60, yPos);
  yPos += 40;

  // Рекорд
  QGraphicsTextItem* highScoreLabel = scene_->addText("Hi-SCORE", font);
  highScoreLabel->setPos(statsX, yPos);
  QGraphicsTextItem* highScoreValue =
      scene_->addText(QString::number(tetg->high_score), font);
  highScoreValue->setPos(statsX + 75, yPos);
  yPos += 40;

  // Уровень
  QGraphicsTextItem* levelLabel = scene_->addText("LEVEL", font);
  levelLabel->setPos(statsX, yPos);
  QGraphicsTextItem* levelValue =
      scene_->addText(QString::number((int)tetg->level), font);
  levelValue->setPos(statsX + 60, yPos);
}

/**
 * @brief Отрисовка сообщение о проигрыше
 */
void View::ShowGameOver() {
  scene_->clear();
  scene_->addText("Game Over", QFont("Arial", 24))
      ->setPos(scene_->width() / 2 - 50, scene_->height() / 2 - 50);
}

/**
 * @brief Отрисовка сообщение о выигрыше
 */
void View::ShowGameVictory() {
  scene_->clear();
  scene_->addText("You Victory", QFont("Arial", 24))
      ->setPos(scene_->width() / 2 - 50, scene_->height() / 2 - 50);
}

void View::ShowGamePause() {
  scene_->addText("Pause", QFont("Arial", 24))
      ->setPos(scene_->width() / 2 - 50, scene_->height() / 2 - 50);
}

void View::keyPressEvent(QKeyEvent* event) {
  if (controller_) {  // Контроллер установлен
    switch (event->key()) {
      case Qt::Key_Left:
        controller_->HandleLeft(Left, false);
        break;
      case Qt::Key_Right:
        controller_->HandleRight(Right, false);
        break;
      case Qt::Key_Up:
        controller_->HandleUp(Up, false);
        break;
      case Qt::Key_Down:
        controller_->HandleDown(Down, false);
        break;
      case Qt::Key_Space:
        controller_->HandleAction(Action, false);
        break;
      case Qt::Key_Escape:
        QApplication::quit();
        break;
      case Qt::Key_P:
        controller_->HandlePause(Pause, false);
        break;
      default:
        QGraphicsView::keyPressEvent(event);
    }
  } else {
    QGraphicsView::keyPressEvent(event);
  }
}