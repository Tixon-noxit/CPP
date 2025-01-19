#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>

#include "../components/controllers/include/ModelControllerFacade.h"
#include "Scene3DView.h"

namespace s21 {

class MainWindow final : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void onLoadModel();
  void onTranslateModel() const;
  void onRotateModel() const;
  void onScaleModel() const;
  void onChooseLineColor();
  void onChooseVertexColor();
  void onChooseBackgroundColor();
  void onProjectionTypeChanged(const QString &projectionType) const;
  void onLineTypeChanged(const QString &projectionType) const;
  void onLineWidth(const QString &lineWidth) const;
  void onVertexDisplayChanged(const QString &projectionType) const;
  void onVertexSizeChanged(const QString &projectionType) const;
  void onSaveImage();
  void onSaveGif() const;

  void onSaveScreen() const;

 private:
  void initialize() {
    std::cout << typeid(this).name() << " is initialized! " << std::endl;
  }

  QLineEdit *fileNameField;  // Поле для отображения названия файла
  QLineEdit *translateXField;  // Поле для ввода перемещения по X
  QLineEdit *translateYField;  // Поле для ввода перемещения по Y
  QLineEdit *translateZField;  // Поле для ввода перемещения по Z
  QLineEdit *rotateXField;  // Поле для ввода угла поворота по X
  QLineEdit *rotateYField;  // Поле для ввода угла поворота по Y
  QLineEdit *rotateZField;  // Поле для ввода угла поворота по Z
  QLineEdit *scaleField;  // Поле для ввода коэффициента масштабирования
  QLabel *modelInfoLabel;  // Информация о загруженной модели
  QWidget *centralWidget;
  QHBoxLayout *mainLayout;
  QGroupBox *controlsGroup;
  QVBoxLayout *controlsLayout;
  QAction *loadAction;
  QAction *imgSaveAction;
  QAction *gifSaveAction;
  // QAction *screenSaveAction;
  QMenu *projectionSubMenu;
  QAction *parallelProjectionAction;
  QAction *centralProjectionAction;
  QMenu *lineTypeSubMenu;
  QAction *solidLineAction;
  QAction *dashedLineAction;
  QAction *chooseLineColorAction;
  QMenu *lineWidthSubMenu;
  QAction *lineWidthAction1;
  QAction *lineWidthAction2;
  QAction *lineWidthAction3;
  QMenu *vertexTypeSubMenu;
  QAction *noneVertexAction;
  QAction *circleVertexAction;
  QAction *squareVertexAction;
  QAction *chooseVertexColorAction;
  QMenu *vertexSizeSubMenu;
  QAction *smallVertexSizeAction;
  QAction *mediumVertexSizeAction;
  QAction *largeVertexSizeAction;
  QAction *chooseBackgroundColorAction;
  QPushButton *translateButton;
  QPushButton *rotateButton;
  QPushButton *scaleButton;

  s21::ModelControllerFacade *facade_;
  s21::Scene3DView *view;  // Зона визуализации модели
};
}  // namespace s21
#endif  // MAINWINDOW_H
