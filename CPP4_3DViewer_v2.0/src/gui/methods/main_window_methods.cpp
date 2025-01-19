//
// Created by Тихон Чабусов on 29.10.2024.
//
#include "../MainWindow.h"

using namespace s21;

/**
 * @brief Метод для загрузки выбранного файла
 */
void MainWindow::onLoadModel() {
  const QString fileName = QFileDialog::getOpenFileName(
      this, "Load 3D Model", "", "OBJ Files (*.obj)");
  if (!fileName.isEmpty()) {
    fileNameField->setText(fileName);
    // Загрузка модели через фасад
    try {
      facade_->loadModel(fileName.toStdString());

      // Передача загруженной модели в Scene3DView
      view->setModel();
      view->update();
      // Обновляем информацию о модели
      const int vertexCount = facade_->getModel()->getVertexCount();
      const int faceCount = facade_->getModel()->getFaceCount();
      const QString baseName = QFileInfo(fileName).fileName();
      modelInfoLabel->setText("Model Info: " + baseName +
                              "\nVertices: " + QString::number(vertexCount) +
                              "\nFaces: " + QString::number(faceCount));
    } catch (const std::exception &e) {
      QMessageBox::critical(this, "Error",
                            "Failed to load model: " + QString(e.what()));
    }
  }
}

/**
 * @brief Метод для перемещения модели по осям x,y,z
 */
void MainWindow::onTranslateModel() const {
  const float x = translateXField->text().toFloat();
  const float y = translateYField->text().toFloat();
  const float z = translateZField->text().toFloat();

  // Фасад для трансформации модели
  facade_->translateModel(x, y, z);

  // Обновление отображения после перемещения
  view->update();
}

/**
 * @brief Метод для поворота модели по осям x,y,z
 */
void MainWindow::onRotateModel() const {
  const float x = rotateXField->text().toFloat();
  const float y = rotateYField->text().toFloat();
  const float z = rotateZField->text().toFloat();

  // Используем фасад для применения вращения
  facade_->rotateModel(x, y, z);

  // Обновление сцены после вращения
  view->update();
}

/**
 * @brief Метод для масштабирования модели
 */
void MainWindow::onScaleModel() const {
  const float scale = scaleField->text().toFloat();

  facade_->scaleModel(scale);

  view->update();
}

/**
 * @brief Метод для изменения цвета линий модели при отображении
 *
 * Этот метод открывает диалоговое окно для выбора цвета линий модели.
 * После выбора цвета, значения RGB и альфа-канала извлекаются из объекта
 * QColor, преобразуются в формат float (от 0.0 до 1.0), и передаются в
 * фасад для изменения цвета линий модели.
 *
 * Если цвет выбран корректно (проверяется через метод color.isValid()),
 * изменения применяются к модели через фасад, и обновляется представление.
 *
 * @details Вызов QColorDialog позволяет пользователю выбрать цвет линий
 * модели через графический интерфейс. После выбора фасад вызывает метод,
 * который изменяет цвет линий модели, используя стратегию для передачи
 * параметров цвета. Затем обновляется отображение модели в представлении
 * через вызов view->update().
 *
 */
void MainWindow::onChooseLineColor() {
  if (const QColor color =
          QColorDialog::getColor(Qt::white, this, "Choose Line Color");
      color.isValid()) {
    const float red =
        color.redF();  // QColor возвращает float в диапазоне 0.0 - 1.0
    const float green = color.greenF();
    const float blue = color.blueF();
    const float alpha = color.alphaF();

    facade_->setLineColor(red, green, blue, alpha);
    view->setLineColor();
    view->update();
  }
}

/**
 * @brief Метод для изменения цвета вершин модели при отображении
 *
 * Этот метод открывает диалоговое окно для выбора цвета вершин модели.
 * После того, как пользователь выбирает цвет, значения компонентов цвета
 * (RGB) и альфа-канала (прозрачность) извлекаются из объекта `QColor`
 * и преобразуются в формат `float` (диапазон от 0.0 до 1.0). Затем
 * эти значения передаются в фасад для изменения цвета вершин модели.
 *
 * Если цвет выбран корректно (проверяется через метод `color.isValid()`),
 * фасад вызывает соответствующий метод для изменения цвета вершин модели,
 * и представление обновляется через вызов `view->update()`.
 *
 * @details Вызов `QColorDialog` предоставляет пользователю возможность
 * выбрать цвет вершин модели через графический интерфейс. Выбранный цвет
 * передаётся в контроллер через фасад, где он применяется к модели.
 * В конце метод вызывает обновление представления для визуализации изменений.
 *
 */
void MainWindow::onChooseVertexColor() {
  if (const QColor color =
          QColorDialog::getColor(Qt::white, this, "Choose Vertex Color");
      color.isValid()) {
    const float red = color.redF();
    const float green = color.greenF();
    const float blue = color.blueF();
    const float alpha = color.alphaF();

    facade_->setVertexColor(red, green, blue, alpha);
    view->setVertexColor();
    view->update();
  }
}

/**
 * @brief Метод для изменения цвета фона сцены
 *
 * Этот метод открывает диалоговое окно для выбора цвета фона сцены.
 * После выбора пользователем, компоненты цвета (RGB) и альфа-канала
 * извлекаются из объекта `QColor` и преобразуются в формат `float`
 * (диапазон от 0.0 до 1.0). Эти значения передаются в фасад для изменения
 * цвета фона сцены.
 *
 * Если выбранный цвет является корректным (проверяется через метод
 * `color.isValid()`), фасад вызывает соответствующий метод для изменения цвета
 * фона, и представление обновляется через вызов `view->update()`.
 *
 * @details Вызов `QColorDialog` предоставляет пользователю графический
 * интерфейс для выбора цвета фона. После этого выбранный цвет передаётся в
 * контроллер через фасад, который применяет изменения к модели, обновляя тем
 * самым отображение сцены.
 *
 */
void MainWindow::onChooseBackgroundColor() {
  const QColor color =
      QColorDialog::getColor(Qt::black, this, "Choose Background Color");
  if (color.isValid()) {
    const float red = color.redF();
    const float green = color.greenF();
    const float blue = color.blueF();
    const float alpha = color.alphaF();

    facade_->setBackgroundColor(red, green, blue, alpha);
    view->setBackgroundColor();
    view->update();
  }
}

void MainWindow::onProjectionTypeChanged(const QString &projectionType) const {
  const std::string projectionTypeStd = projectionType.toStdString();

  facade_->setProjectionType(projectionTypeStd);
  view->setProjectionType();
  view->update();
}

void MainWindow::onLineTypeChanged(const QString &projectionType) const {
  const std::string lineTypeStd = projectionType.toStdString();
  facade_->setLineType(lineTypeStd);
  view->setLineType();
  view->update();
}

void MainWindow::onVertexDisplayChanged(const QString &projectionType) const {
  const std::string vertexDisplayStd = projectionType.toStdString();

  facade_->setVertexDisplay(vertexDisplayStd);

  view->update();
}

void MainWindow::onLineWidth(const QString &lineWidth) const {
  const std::string lineWidthStd = lineWidth.toStdString();
  facade_->setLineSize(lineWidthStd);
  view->setLineWidth();
  view->update();
}

void MainWindow::onVertexSizeChanged(const QString &projectionType) const {
  const std::string vertexSizeStd = projectionType.toStdString();

  facade_->setVertexSize(vertexSizeStd);
  view->setVertexSize();
  view->update();
}

void MainWindow::onSaveImage() {
  // Создаем объект диалогового окна
  QFileDialog dialog(this, "Save Image");

  // Настраиваем фильтры для выбора формата
  dialog.setNameFilters({"JPEG Files (*.jpg)", "BMP Files (*.bmp)"});
  dialog.setAcceptMode(QFileDialog::AcceptSave);

  // Показываем диалоговое окно
  if (dialog.exec() == QDialog::Accepted) {
    QString fileName =
        dialog.selectedFiles().first();  // Получаем выбранное имя файла

    if (!fileName.isEmpty()) {
      // Получаем выбранный фильтр

      // Добавляем правильное расширение файла, если оно отсутствует
      if (const QString selectedFilter = dialog.selectedNameFilter();
          selectedFilter.contains("*.jpg") &&
          !fileName.endsWith(".jpg", Qt::CaseInsensitive)) {
        fileName += ".jpg";
      } else if (selectedFilter.contains("*.bmp") &&
                 !fileName.endsWith(".bmp", Qt::CaseInsensitive)) {
        fileName += ".bmp";
      }

      // Захват содержимого сцены в виде изображения

      // Проверяем, что изображение успешно захвачено
      if (const QImage image = view->grabFramebuffer(); !image.isNull()) {
        // Сохраняем изображение в выбранный файл
        if (image.save(fileName)) {
          qDebug() << "Изображение успешно сохранено в файл:" << fileName;
        } else {
          qDebug() << "Ошибка: не удалось сохранить изображение в файл:"
                   << fileName;
        }
      } else {
        qDebug() << "Ошибка: не удалось захватить изображение из фреймбуфера!";
      }
    } else {
      qDebug() << "Ошибка: путь для сохранения изображения пуст!";
    }
  }
}

void MainWindow::onSaveGif() const { view->startRecordingGif(); }

void MainWindow::onSaveScreen() const {
  view->saveSceneAsImage("Screenshots.png");
}