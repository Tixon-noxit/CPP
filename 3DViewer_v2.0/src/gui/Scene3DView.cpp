#include "Scene3DView.h"

#include <QOpenGLShaderProgram>
#include <utility>

using namespace s21;

Scene3DView::Scene3DView(ModelControllerFacade* facade, QWidget* parent)
    : QOpenGLWidget(parent), facade_(facade) {
  initialize();
  load_settings();
}
Scene3DView::~Scene3DView() {
  // delete model_;
  delete gifWriter_;
  // delete facade_;
  delete recordTimer_;
  delete captureGifTimer;
}

void Scene3DView::load_settings() {
  lineColor_ =
      arrayToQColor(facade_->getModel()->getSettings()->getLineColor());
  backgroundColor_ =
      arrayToQColor(facade_->getModel()->getSettings()->getBackgroundColor());
  vertexColor_ =
      arrayToQColor(facade_->getModel()->getSettings()->getVertexColor());
  lineWidth_ = facade_->getModel()->getSettings()->getLineSize();
  projectionType_ = facade_->getModel()->getSettings()->getProjectionType();
  vertexDisplay_ = QString::fromStdString(
      facade_->getModel()->getSettings()->getVertexDisplay());
  vertexSize_ = facade_->getModel()->getSettings()->getVertexSize();
  lineType_ = facade_->getModel()->getSettings()->getLineType();
  std::cout << "load_color is initialized! " << std::endl;
}
void Scene3DView::wheelEvent(QWheelEvent* event) {
  QOpenGLWidget::wheelEvent(event);
  if (const double delta = 1.0 + qAbs(event->angleDelta().y()) / 720.0;
      delta > 0.0) {
    const double factor = event->angleDelta().y() < 0 ? 1 / delta : delta;
    facade_->scaleModel(static_cast<float>(factor));
    update();
  }
  event->accept();
}
void Scene3DView::mousePressEvent(QMouseEvent* event) {
  QOpenGLWidget::mousePressEvent(event);
  if (event->buttons() == Qt::LeftButton) {
    isLMBPressed = true;
  } else if (event->buttons() == Qt::MiddleButton) {
    isMMBPressed = true;
  }
  if (firstMousePos == nullptr)
    firstMousePos = std::make_unique<QPointF>(event->position());
  else
    *firstMousePos = event->position();
}
void Scene3DView::mouseReleaseEvent(QMouseEvent* event) {
  QOpenGLWidget::mouseReleaseEvent(event);
  isLMBPressed = false;
  isMMBPressed = false;
  firstMousePos = nullptr;
}
void Scene3DView::mouseMoveEvent(QMouseEvent* event) {
  QOpenGLWidget::mouseMoveEvent(event);
  if (!isLMBPressed && !isMMBPressed) {
    event->ignore();
    return;
  }
  const auto pos = event->position();
  const QPointF diff = pos - *firstMousePos;
  if (isLMBPressed) {
    facade_->rotateModel(static_cast<float>(diff.y()),
                         static_cast<float>(diff.x()),
                         static_cast<float>(-diff.y()));
  } else if (isMMBPressed) {
    facade_->translateModel(static_cast<float>(diff.x() / 100),
                            static_cast<float>(-diff.y() / 100),
                            static_cast<float>(-diff.x() / 100));
  }
  *firstMousePos = event->position();
  update();
  event->accept();
}

void Scene3DView::setProjectionType() {
  projectionType_ = facade_->getModel()->getSettings()->getProjectionType();
  update();
}

void Scene3DView::setModel() {
  this->model_ = facade_->getModel();
  update();
}

// Установка цвета ребер
void Scene3DView::setLineColor() {
  lineColor_ =
      arrayToQColor(facade_->getModel()->getSettings()->getLineColor());
  update();
}

// Установка толщины ребер
void Scene3DView::setLineWidth() {
  lineWidth_ = facade_->getModel()->getSettings()->getLineSize();
  update();
}

// Установка типа линий для ребер (сплошная, пунктирная)
void Scene3DView::setLineType() {
  lineType_ = facade_->getModel()->getSettings()->getLineType();
  update();
}

// Установка цвета вершин
void Scene3DView::setVertexColor() {
  vertexColor_ =
      arrayToQColor(facade_->getModel()->getSettings()->getVertexColor());
  update();
}

// Установка размера вершин
void Scene3DView::setVertexSize() {
  vertexSize_ = facade_->getModel()->getSettings()->getVertexSize();
  update();
}

// Установка формы вершин (круг или квадрат)
void Scene3DView::setVertexShape() {
  vertexDisplay_ = QString::fromStdString(
      facade_->getModel()->getSettings()->getVertexDisplay());
  update();
}

// Установка цвета фона
void Scene3DView::setBackgroundColor() {
  backgroundColor_ =
      arrayToQColor(facade_->getModel()->getSettings()->getBackgroundColor());
  update();
}

void Scene3DView::initializeGL() {
  initializeOpenGLFunctions();

  glClearColor(backgroundColor_.redF(), backgroundColor_.greenF(),
               backgroundColor_.blueF(), backgroundColor_.alphaF());
  glDisable(GL_LIGHTING);  // !!!!!!!!!!!!
  glColor4f(lineColor_.redF(), lineColor_.greenF(), lineColor_.blueF(),
            lineColor_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);  // Очищаем буферы цвета и глубины
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);  // Включаем освещение
  glEnable(GL_LIGHT0);  // Используем один источник света (свет 0)

  // Настройка света
  constexpr GLfloat lightPosition[] = {3.0f, 3.0f, 3.0f,
                                       1.0f};  // Позиция света
  constexpr GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};  // Фоновый свет
  constexpr GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f,
                                      1.0f};  // Диффузное освещение
  constexpr GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f,
                                       1.0f};  // Зеркальное освещение

  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

  glEnable(GL_NORMALIZE);  // Автоматическая нормализация
}

void Scene3DView::resizeGL(const int w, const int h) {
  glViewport(0, 0, w, h);
  projection.setToIdentity();
  projection.perspective(zoom, static_cast<float>(w) / static_cast<float>(h),
                         0.1f, 100.0f);
}

void Scene3DView::paintGL() {
  // Очистка экрана и установка цвета фона
  glClearColor(backgroundColor_.redF(), backgroundColor_.greenF(),
               backgroundColor_.blueF(), backgroundColor_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);  // Очищаем буфер цвета и глубины
  glMatrixMode(GL_PROJECTION);

  // --- Установка модельной матрицы (позиционирование объекта) ---
  QMatrix4x4 modelMatrix;
  modelMatrix.setToIdentity();  // Сброс матрицы
  modelMatrix.translate(0.0f, 0.0f, 0.0f);  // Можем оставить модель в центре

  // Проверяем, инициализирован ли facade_
  if (facade_ != nullptr) {
    // Применяем вращение вокруг осей X, Y, Z
    modelMatrix.rotate(0.0f, 1.0f, 0.0f);  // Вращение вокруг оси X
    modelMatrix.rotate(0.0f, 0.0f, 1.0f);  // Вращение вокруг оси Y
    modelMatrix.rotate(0.0f, 0.0f, 0.0f);  // Вращение вокруг оси Z
  }

  // --- Установка матрицы вида (камера) ---
  QMatrix4x4 viewMatrix;
  cameraPos =
      QVector3D(3.0f, 3.0f, 3.0f);  // Камера смотрит с позиции (3, 3, 3)
  constexpr QVector3D target(0.0f, 0.0f, 0.0f);  // Смотрим на центр сцены
  constexpr QVector3D upVector(0.0f, 1.0f, 0.0f);  // "Вверх" по оси Y
  viewMatrix.lookAt(cameraPos, target, upVector);

  // --- Установка матрицы проекции для выбора типа вида ---
  QMatrix4x4 projectionMatrix;

  const float aspectRatio =
      static_cast<float>(width()) / static_cast<float>(height());

  if (projectionType_ == "Central") {
    // Центральная (перспективная) проекция
    constexpr float fieldOfView = 45.0f;  // Поле зрения
    projectionMatrix.perspective(fieldOfView, aspectRatio, 0.1f, 100.0f);
  } else {
    // Параллельная (ортографическая) проекция
    constexpr float orthoSize = 4.0f;
    projectionMatrix.ortho(-orthoSize * aspectRatio, orthoSize * aspectRatio,
                           -orthoSize, orthoSize, 0.1f, 100.0f);
  }

  // --- Рассчитываем итоговую матрицу MVP (Model-View-Projection) ---
  const QMatrix4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

  // Устанавливаем матрицу в OpenGL
  glLoadMatrixf(mvpMatrix.constData());

  // Устанавливаем толщину линий для отображения граней
  glLineWidth(lineWidth_);

  // Проверяем, есть ли модель для отрисовки
  if (model_ && !model_->getVertices().empty() && !model_->getFaces().empty()) {
    // Отрисовка объекта
    glDisable(
        GL_LIGHTING);  // Отключаем освещение, чтобы применить цвет напрямую
    DrawObj();
    glEnable(GL_LIGHTING);  // Включаем освещение снова
  }
}

void Scene3DView::DrawObj() {
  glDisable(GL_LIGHTING);

  // Настройка цвета ребер
  glColor4f(lineColor_.redF(), lineColor_.greenF(), lineColor_.blueF(),
            lineColor_.alphaF());

  // Толщина линий
  GLfloat lineWidth = lineWidth_;
  glLineWidth(lineWidth);
  glGetFloatv(GL_LINE_WIDTH, &lineWidth);

  // Настройка типа линий (сплошные или пунктирные)
  if (lineType_ == "Dashed") {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(18, 0xAAAA);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glFlush();
  // Отрисовка рёбер
  glBegin(GL_LINES);
  for (const auto& [faces] : model_->getFaces()) {
    for (size_t i = 0; i < faces.size(); ++i) {
      const int vertexIndex = static_cast<int>(faces[i].v.data) - 1;
      const int nextVertexIndex =
          static_cast<int>(faces[(i + 1) % faces.size()].v.data) - 1;

      if (vertexIndex < 0 || vertexIndex >= model_->getVertices().size() ||
          nextVertexIndex < 0 ||
          nextVertexIndex >= model_->getVertices().size())
        continue;

      const auto& vertex = model_->getVertices()[vertexIndex];
      const auto& nextVertex = model_->getVertices()[nextVertexIndex];

      glVertex3f(static_cast<GLfloat>(vertex.x.data),
                 static_cast<GLfloat>(vertex.y.data),
                 static_cast<GLfloat>(vertex.z.data));
      glVertex3f(static_cast<GLfloat>(nextVertex.x.data),
                 static_cast<GLfloat>(nextVertex.y.data),
                 static_cast<GLfloat>(nextVertex.z.data));
    }
  }
  glEnd();
  const std::string vertexDisplay =
      std::move(facade_->getModel()->getSettings()->getVertexDisplay());

  // Отрисовка вершин
  if (vertexDisplay != "None") {
    glPointSize(vertexSize_ * 2);
    glColor4f(lineColor_.redF(), lineColor_.greenF(), lineColor_.blueF(),
              lineColor_.alphaF());

    if (vertexDisplay == "Circle") {
      glEnable(GL_POINT_SMOOTH);  // Cглаживание точек
      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);  // Оптимизация сглаживания

      glBegin(GL_POINTS);
      glColor4f(vertexColor_.redF(), vertexColor_.greenF(),
                vertexColor_.blueF(), vertexColor_.alphaF());

      for (const auto& [faces] : model_->getFaces()) {
        for (const auto& [v, vn] : faces) {
          const int vertexIndex = static_cast<int>(v.data) - 1;
          if (vertexIndex < 0 || vertexIndex >= model_->getVertices().size())
            continue;

          const auto& vertex = model_->getVertices()[vertexIndex];
          glVertex3f(static_cast<GLfloat>(vertex.x.data),
                     static_cast<GLfloat>(vertex.y.data),
                     static_cast<GLfloat>(vertex.z.data));
        }
      }
      glEnd();

      glDisable(GL_POINT_SMOOTH);
    } else if (vertexDisplay == "Square") {
      glBegin(GL_QUADS);
      glColor4f(vertexColor_.redF(), vertexColor_.greenF(),
                vertexColor_.blueF(), vertexColor_.alphaF());
      const GLfloat offset =
          (vertexSize_ * 0.1f) / 3.0f;  // Смещение для квадрата
      for (const auto& [faces] : model_->getFaces()) {
        for (const auto& [v, vn] : faces) {
          const int vertexIndex = static_cast<int>(v.data) - 1;
          if (vertexIndex < 0 || vertexIndex >= model_->getVertices().size())
            continue;

          const auto& vertex = model_->getVertices()[vertexIndex];
          glVertex3f(static_cast<GLfloat>(vertex.x.data - offset),
                     static_cast<GLfloat>(vertex.y.data - offset),
                     static_cast<GLfloat>(vertex.z.data));
          glVertex3f(static_cast<GLfloat>(vertex.x.data + offset),
                     static_cast<GLfloat>(vertex.y.data - offset),
                     static_cast<GLfloat>(vertex.z.data));
          glVertex3f(static_cast<GLfloat>(vertex.x.data + offset),
                     static_cast<GLfloat>(vertex.y.data + offset),
                     static_cast<GLfloat>(vertex.z.data));
          glVertex3f(static_cast<GLfloat>(vertex.x.data - offset),
                     static_cast<GLfloat>(vertex.y.data + offset),
                     static_cast<GLfloat>(vertex.z.data));
        }
      }
      glEnd();
    }
  }

  glEnable(GL_LIGHTING);  // Включаем освещение снова

  // Отключаем пунктирные линии после завершения
  glDisable(GL_LINE_STIPPLE);
}

void Scene3DView::startRecordingGif() {
  // Количество кадров и интервал между ними
  int framesCount = 50;
  int frameDelay = 100;  // Задержка в миллисекундах
  int frameNumber = 0;
  qDebug() << "Начало записи GIF";
  // Создаем экземпляр GifCreator
  GifCreator gifCreator;

  // Настраиваем таймер для захвата кадров
  captureGifTimer = new QTimer(this);
  captureGifTimer->setInterval(frameDelay);
  // Запуск таймера для захвата кадров
  connect(
      captureGifTimer, &QTimer::timeout, this,
      [this, frameNumber, framesCount, frameDelay, &gifCreator,
       ptrTimerCopy = captureGifTimer]() mutable {
        if (frameNumber < framesCount) {
          // Захват кадра из OpenGL-виджета
          const QImage frame = grabFramebuffer();
          //      QString filePath =
          //      QString("frame_%1.png").arg(frameNumber);

          const QString screenshotsDir =
              gifCreator.tempDirPath();  // Папка для сохранения скриншотов

          // Убедитесь, что папка существует
          if (!QDir().mkpath(screenshotsDir)) {
            std::cout << "Cannot create screenshot directory "
                      << screenshotsDir.toStdString() << std::endl;
          }

          // Создание пути к файлу для скриншота
          const QString filePath =
              QDir(screenshotsDir)
                  .filePath(QString("frame_%1.png").arg(frameNumber));
          qDebug() << "Путь к файлу:" << filePath;

          if (!frame.isNull()) {
            qDebug() << "Фрейм:" << frameNumber << " создан!";
            if (frame.save(filePath))
              qDebug() << "Фрейм: " << frameNumber << " сохранен!";
          } else {
            qDebug() << "Фрейм пустой!";
          }

          ++frameNumber;  // Увеличение номера кадра

        } else {
          ptrTimerCopy->stop();  // Остановка таймера после захвата всех кадров

          if (gifCreator.createGif(framesCount, frameDelay / 10)) {
            qDebug() << "GIF создан:" << gifCreator.gifFilePath();
          } else {
            qDebug() << "Ошибка при создании GIF.";
          }
        }
      });

  // Запуск таймера
  captureGifTimer->start();
}

void Scene3DView::saveSceneAsImage(const QString& fileName) {
  // Захватываем текущее изображение с экрана.
  // Сохраняем изображение в файл
  if (const QImage image = grabFramebuffer(); !image.save(fileName)) {
    qDebug() << "Не удалось сохранить изображение!";
  } else {
    qDebug() << "Изображение сохранено в файл:" << fileName;
  }
}

/**
 * @brief Конвертирует массив в QColor
 * @param colorArray - массив из 4 float (параметры цвета)
 * @return Объект типа QColor
 */
QColor Scene3DView::arrayToQColor(const std::array<float, 4>& colorArray) {
  // Каждый компонент цвета в QColor должен быть в диапазоне [0, 255],
  // поэтому float значения (в диапазоне [0.0, 1.0]) умножаем на 255
  const int red = static_cast<int>(colorArray[0] * 255);
  const int green = static_cast<int>(colorArray[1] * 255);
  const int blue = static_cast<int>(colorArray[2] * 255);
  const int alpha = static_cast<int>(colorArray[3] * 255);

  return {red, green, blue, alpha};
}