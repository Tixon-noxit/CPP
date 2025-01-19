//
// Created by KWAZAR_ on 13.09.2024.
//

#include <QApplication>

#include "components/Settings/include/SettingsModel.h"
#include "gui/MainWindow.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.resize(800, 600);
  window.show();

  return app.exec();
}