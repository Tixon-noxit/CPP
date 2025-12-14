#include "MainWindow.h"

#include <QColorDialog>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMenuBar>

using namespace s21;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  initialize();

  centralWidget = new QWidget(this);
  mainLayout = new QHBoxLayout(centralWidget);

  // Группа для пользовательского интерфейса
  controlsGroup = new QGroupBox("Controls", this);
  controlsLayout = new QVBoxLayout(controlsGroup);

  // Поле для отображения названия файла
  fileNameField = new QLineEdit(this);
  fileNameField->setPlaceholderText("Model file name");
  fileNameField->setReadOnly(true);

  facade_ = new s21::ModelControllerFacade();
  view = new s21::Scene3DView(facade_, this);  // Визуализации модели

  // Поля для ввода значений перемещения, поворота и масштабирования
  translateXField = new QLineEdit(this);
  translateXField->setPlaceholderText("Translate X");
  translateYField = new QLineEdit(this);
  translateYField->setPlaceholderText("Translate Y");
  translateZField = new QLineEdit(this);
  translateZField->setPlaceholderText("Translate Z");

  rotateXField = new QLineEdit(this);
  rotateXField->setPlaceholderText("Rotate X");
  rotateYField = new QLineEdit(this);
  rotateYField->setPlaceholderText("Rotate Y");
  rotateZField = new QLineEdit(this);
  rotateZField->setPlaceholderText("Rotate Z");

  scaleField = new QLineEdit(this);
  scaleField->setPlaceholderText("Scale");

  // Кнопки для применения изменений
  translateButton = new QPushButton("Apply Translation", this);
  rotateButton = new QPushButton("Apply Rotation", this);
  scaleButton = new QPushButton("Apply Scaling", this);

  // Информация о загруженной модели
  modelInfoLabel = new QLabel("Model Info: No model loaded", this);
  modelInfoLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  connect(translateButton, &QPushButton::clicked, this,
          &MainWindow::onTranslateModel);
  connect(rotateButton, &QPushButton::clicked, this,
          &MainWindow::onRotateModel);
  connect(scaleButton, &QPushButton::clicked, this, &MainWindow::onScaleModel);

  // Header menu

  // "File"
  QMenu *fileMenu = menuBar()->addMenu("File");
  loadAction = new QAction("Load Model", this);
  connect(loadAction, &QAction::triggered, this, &MainWindow::onLoadModel);
  fileMenu->addAction(loadAction);

  // "View"
  QMenu *viewMenu = menuBar()->addMenu("View");

  // "Save as"
  QMenu *saveMenu = menuBar()->addMenu("Save as");
  imgSaveAction = new QAction("Image", this);
  saveMenu->addAction(imgSaveAction);
  connect(imgSaveAction, &QAction::triggered, this, &MainWindow::onSaveImage);

  gifSaveAction = new QAction("GIF", this);
  saveMenu->addAction(gifSaveAction);
  connect(gifSaveAction, &QAction::triggered, this, &MainWindow::onSaveGif);

  // screenSaveAction = new QAction("Screenshots", this);
  // saveMenu->addAction(screenSaveAction);
  // connect(screenSaveAction, &QAction::triggered, this,
  //         &MainWindow::onSaveScreen);

  // Подменю для выбора типа проекции
  projectionSubMenu = new QMenu("Projection Type", this);
  viewMenu->addMenu(projectionSubMenu);
  parallelProjectionAction = new QAction("Parallel", this);
  centralProjectionAction = new QAction("Central", this);
  projectionSubMenu->addAction(parallelProjectionAction);
  projectionSubMenu->addAction(centralProjectionAction);
  connect(parallelProjectionAction, &QAction::triggered, this,
          [this]() { onProjectionTypeChanged("Parallel"); });
  connect(centralProjectionAction, &QAction::triggered, this,
          [this]() { onProjectionTypeChanged("Central"); });

  // Подменю для выбора типа линий
  lineTypeSubMenu = new QMenu("Line Type", this);
  viewMenu->addMenu(lineTypeSubMenu);
  solidLineAction = new QAction("Solid", this);
  dashedLineAction = new QAction("Dashed", this);
  lineTypeSubMenu->addAction(solidLineAction);
  lineTypeSubMenu->addAction(dashedLineAction);
  connect(solidLineAction, &QAction::triggered, this,
          [this]() { onLineTypeChanged("Solid"); });
  connect(dashedLineAction, &QAction::triggered, this,
          [this]() { onLineTypeChanged("Dashed"); });

  // Пункт меню для выбора цвета линии
  chooseLineColorAction = new QAction("Choose Line Color", this);
  viewMenu->addAction(chooseLineColorAction);
  connect(chooseLineColorAction, &QAction::triggered, this,
          &MainWindow::onChooseLineColor);

  // Подменю для выбора толщины линии
  lineWidthSubMenu = new QMenu("Line Width", this);
  viewMenu->addMenu(lineWidthSubMenu);
  lineWidthAction1 = new QAction("Thin", this);
  lineWidthAction2 = new QAction("Medium", this);
  lineWidthAction3 = new QAction("Thick", this);
  lineWidthSubMenu->addAction(lineWidthAction1);
  lineWidthSubMenu->addAction(lineWidthAction2);
  lineWidthSubMenu->addAction(lineWidthAction3);

  connect(lineWidthAction1, &QAction::triggered, this,
          [this]() { onLineWidth("Thin"); });
  connect(lineWidthAction2, &QAction::triggered, this,
          [this]() { onLineWidth("Medium"); });
  connect(lineWidthAction3, &QAction::triggered, this,
          [this]() { onLineWidth("Thick"); });

  // Подменю для выбора типа отображения вершин
  vertexTypeSubMenu = new QMenu("Vertex Display", this);
  viewMenu->addMenu(vertexTypeSubMenu);
  noneVertexAction = new QAction("None", this);
  circleVertexAction = new QAction("Circle", this);
  squareVertexAction = new QAction("Square", this);
  vertexTypeSubMenu->addAction(noneVertexAction);
  vertexTypeSubMenu->addAction(circleVertexAction);
  vertexTypeSubMenu->addAction(squareVertexAction);
  connect(noneVertexAction, &QAction::triggered, this,
          [this]() { onVertexDisplayChanged("None"); });
  connect(circleVertexAction, &QAction::triggered, this,
          [this]() { onVertexDisplayChanged("Circle"); });
  connect(squareVertexAction, &QAction::triggered, this,
          [this]() { onVertexDisplayChanged("Square"); });

  // Пункт меню для выбора цвета вершин
  chooseVertexColorAction = new QAction("Choose Vertex Color", this);
  viewMenu->addAction(chooseVertexColorAction);
  connect(chooseVertexColorAction, &QAction::triggered, this,
          &MainWindow::onChooseVertexColor);

  // Подменю для выбора размера вершин
  vertexSizeSubMenu = new QMenu("Vertex Size", this);
  viewMenu->addMenu(vertexSizeSubMenu);
  smallVertexSizeAction = new QAction("Small", this);
  mediumVertexSizeAction = new QAction("Medium", this);
  largeVertexSizeAction = new QAction("Large", this);
  vertexSizeSubMenu->addAction(smallVertexSizeAction);
  vertexSizeSubMenu->addAction(mediumVertexSizeAction);
  vertexSizeSubMenu->addAction(largeVertexSizeAction);
  connect(smallVertexSizeAction, &QAction::triggered, this,
          [this]() { onVertexSizeChanged("Small"); });
  connect(mediumVertexSizeAction, &QAction::triggered, this,
          [this]() { onVertexSizeChanged("Medium"); });
  connect(largeVertexSizeAction, &QAction::triggered, this,
          [this]() { onVertexSizeChanged("Large"); });

  // Пункт меню для выбора цвета фона
  chooseBackgroundColorAction = new QAction("Choose Background Color", this);
  viewMenu->addAction(chooseBackgroundColorAction);
  connect(chooseBackgroundColorAction, &QAction::triggered, this,
          &MainWindow::onChooseBackgroundColor);

  // Привязка кнопок с их обработчиками
  connect(translateButton, &QPushButton::clicked, this,
          &MainWindow::onTranslateModel);
  connect(rotateButton, &QPushButton::clicked, this,
          &MainWindow::onRotateModel);
  connect(scaleButton, &QPushButton::clicked, this, &MainWindow::onScaleModel);

  // Компоновка интерфейса
  controlsLayout->addWidget(fileNameField);
  controlsLayout->addWidget(translateXField);
  controlsLayout->addWidget(translateYField);
  controlsLayout->addWidget(translateZField);
  controlsLayout->addWidget(translateButton);
  controlsLayout->addWidget(rotateXField);
  controlsLayout->addWidget(rotateYField);
  controlsLayout->addWidget(rotateZField);
  controlsLayout->addWidget(rotateButton);
  controlsLayout->addWidget(scaleField);
  controlsLayout->addWidget(scaleButton);

  // Пространство для отступа вверху
  controlsLayout->addStretch();  // Сдвигает modelInfoLabel вниз

  // Информация о модели
  controlsLayout->addWidget(modelInfoLabel);

  // Группа управления и зоны визуализации
  mainLayout->addWidget(controlsGroup, 1);  // Ширина колонки управления
  mainLayout->addWidget(view, 3);  // Ширина колонки просмотра

  // Компоновка для основного виджета
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
  delete facade_;
  // delete fileNameField;  // Поле для отображения названия файла
  // delete translateXField;  // Поле для ввода перемещения по X
  // delete translateYField;  // Поле для ввода перемещения по Y
  // delete translateZField;  // Поле для ввода перемещения по Z
  // delete rotateXField;  // Поле для ввода угла поворота по X
  // delete rotateYField;  // Поле для ввода угла поворота по Y
  // delete rotateZField;  // Поле для ввода угла поворота по Z
  // delete scaleField;  // Поле для ввода коэффициента масштабирования
  // delete modelInfoLabel;  // Информация о загруженной модели
  // delete centralWidget;
  // delete mainLayout;
  // delete controlsGroup;
  // delete controlsLayout;
  // delete loadAction;
  // delete imgSaveAction;
  // delete gifSaveAction;
  // delete screenSaveAction;
  // delete projectionSubMenu;
  // delete parallelProjectionAction;
  // delete centralProjectionAction;
  // delete lineTypeSubMenu;
  // delete solidLineAction;
  // delete dashedLineAction;
  // delete chooseLineColorAction;
  // delete lineWidthSubMenu;
  // delete lineWidthAction1;
  // delete lineWidthAction2;
  // delete lineWidthAction3;
  // delete vertexTypeSubMenu;
  // delete noneVertexAction;
  // delete circleVertexAction;
  // delete squareVertexAction;
  // delete chooseVertexColorAction;
  // delete vertexSizeSubMenu;
  // delete smallVertexSizeAction;
  // delete mediumVertexSizeAction;
  // delete largeVertexSizeAction;
  // delete chooseBackgroundColorAction;
  // delete view;
  // delete translateButton;
  // delete rotateButton;
  // delete scaleButton;
}
