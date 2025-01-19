#ifndef SCENE3DVIEW_H
#define SCENE3DVIEW_H

#include <QColor>
#include <QFileDialog>
#include <QImage>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QRandomGenerator>
#include <QTimer>
#include <QWheelEvent>

#include "../components/Settings/include/SettingsModel.h"
#include "../components/controllers/include/ModelControllerFacade.h"
#include "../models/include/Model.h"
#include "../models/include/OBJParser.h"
#include "methods/GifCreator.h"

namespace s21 {

class Scene3DView final : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit Scene3DView(ModelControllerFacade *facade, QWidget *parent);

  ~Scene3DView() override;

  // Метод для установки модели
  void setModel();

  void saveSceneAsImage(const QString &fileName);

  void setLineColor();
  void setLineWidth();
  void setLineType();
  void setProjectionType();
  void setVertexColor();
  void setVertexSize();
  void setVertexShape();
  void setBackgroundColor();

  void startRecordingGif();

 protected:
  void initializeGL() override;

  void resizeGL(int w, int h) override;

  void paintGL() override;

 private:
  Model *model_ = nullptr;
  ModelControllerFacade *facade_ = nullptr;
  GifWriter *gifWriter_ =
      nullptr;  // Указатель на GifWriter для управления записью
  void DrawObj();

  void load_settings();

  void initialize() {
    std::cout << typeid(this).name() << " is initialized! " << std::endl;
  }

 protected:
  void wheelEvent(QWheelEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  std::string projectionType_;  // Тип проекции фигуры
  bool isLMBPressed = false;
  bool isMMBPressed = false;
  std::unique_ptr<QPointF> firstMousePos;

  // Color
  static QColor arrayToQColor(const std::array<float, 4> &colorArray);
  QColor lineColor_;        // Цвет линии ребра
  float lineWidth_{};       // Ширина линии ребра
  std::string lineType_;    // Тип линии ребра
  QColor vertexColor_;      // Цвет вершины
  float vertexSize_{};      // Размер ширины
  QString vertexDisplay_;   // Тип отображения вершины
  QColor backgroundColor_;  // Цвет фона сцены

  QString gifFileName_;
  int frameCount_{};
  QTimer *recordTimer_ = nullptr;

  QMatrix4x4 projection;
  QMatrix4x4 view;
  QVector3D cameraPos;
  QVector3D cameraFront;
  QVector3D cameraUp;
  float yaw{}, pitch{};
  float zoom{};
  QPoint lastMousePosition;
  QTimer *captureGifTimer = nullptr;
};

};      // namespace s21
#endif  // SCENE3DVIEW_H
