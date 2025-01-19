//
// Created by Тихон Чабусов on 10.11.2024.
//

#ifndef GIFCREATOR_H
#define GIFCREATOR_H

#include <QCoreApplication>
#include <QDir>
#include <QImage>
#include <QObject>
#include <QStandardPaths>
#include <QString>

#include "gif.h"

class GifCreator : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString imageFilePathMask READ imageFilePathMask)
  Q_PROPERTY(QString gifFilePath READ gifFilePath)

 public:
  explicit GifCreator(QObject *parent = nullptr);
  ~GifCreator() override = default;

  static QString imageFilePathMask();
  static QString gifFilePath();

  Q_INVOKABLE static bool createGif(int frames_count, int frame_delay);

  static QString tempDirPath();
};

#endif  // GIFCREATOR_H
