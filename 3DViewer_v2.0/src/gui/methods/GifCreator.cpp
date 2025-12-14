//
// Created by Тихон Чабусов on 10.11.2024.
//

#include "GifCreator.h"

/**
 * @brief Конструктор класса `GifCreator`.
 *
 * Инициализирует объект класса `GifCreator` с указанным родителем.
 * Используется для создания экземпляра класса, предназначенного для управления
 * процессом создания GIF-файлов из последовательности изображений.
 *
 * @param parent Указатель на родительский объект типа `QObject`.
 *               Если не указан, объект создаётся без родителя (значение по
 * умолчанию — `nullptr`).
 *
 * @details
 * Родительский объект используется для управления временем жизни экземпляра
 * `GifCreator` в рамках системы управления памятью Qt. Если родитель
 * установлен, то при удалении родительского объекта будет автоматически удалён
 * и объект `GifCreator`.
 *
 * Пример использования:
 * ```cpp
 * GifCreator* creator = new GifCreator(this); // Создание с родителем
 * GifCreator* standaloneCreator = new GifCreator(); // Создание без родителя
 * ```
 */
GifCreator::GifCreator(QObject *parent) : QObject(parent) {}

/**
 * @brief Возвращает шаблон пути для сохранения кадров GIF.
 *
 * Метод формирует путь к файлам, в которых будут сохраняться отдельные кадры
 * GIF-анимации. Путь включает временную директорию и шаблон имени файла.
 *
 * @details
 * - Проверяет наличие временной директории, указанной методом `tempDirPath()`.
 * - Если директория не существует, создает её с помощью `QDir::mkpath`.
 * - Формирует и возвращает строку с шаблоном пути, где `%1` — это место для
 * номера кадра.
 *
 * Пример возвращаемого значения: `/tmp/my_temp_dir/frame_%1.png`.
 * `%1` заменяется реальным номером кадра при сохранении.
 *
 * @return QString Шаблон пути к файлу, включая временную директорию и имя
 * кадра. Если временная директория не задана, возвращает пустую строку.
 */
QString GifCreator::imageFilePathMask() {
  const QString tmpDir = tempDirPath();

  if (!tmpDir.isEmpty()) {
    if (QDir().mkpath(
            tmpDir)) {  // Создание временной папки (если она не существует)
      qDebug() << "Created temp folder: " << tmpDir;
    }
  }
  return QDir(tmpDir).filePath("frame_%1.png");  // Шаблон пути для изображений
}

/**
 * @brief Возвращает полный путь к конечному GIF-файлу.
 *
 * Метод формирует и возвращает путь, по которому будет сохранён результирующий
 * GIF-файл. Путь строится на основе временной директории, указанной методом
 * `tempDirPath()`, с именем файла `output.gif`.
 *
 * @details
 * - Использует значение, возвращаемое `tempDirPath()` для определения базовой
 * директории.
 * - Если `tempDirPath` возвращает пустую строку, результат будет неполным.
 * - Путь к файлу формируется с использованием `QDir::filePath`, что гарантирует
 * корректную обработку разделителей путей.
 *
 * Пример возвращаемого значения: `/tmp/my_temp_dir/output.gif`.
 *
 * @return QString Полный путь к конечному GIF-файлу. Если временная директория
 * не задана, путь может быть некорректным.
 */
QString GifCreator::gifFilePath() {
  return QDir(tempDirPath()).filePath("output.gif");
}

/**
 * @brief Возвращает путь к временной директории для сохранения кадров и
 * GIF-файлов.
 *
 * Метод формирует и возвращает путь к временной директории, используемой для
 * хранения промежуточных файлов (кадров) и конечного GIF-файла.
 *
 * @details
 * - Базовый путь вычисляется относительно директории, в которой находится
 * исполняемый файл. Для получения пути используется метод
 * `QCoreApplication::applicationDirPath`.
 * - К базовому пути добавляется поддиректория `save_gif_folder`.
 *
 * Пример возвращаемого значения: `/path/to/executable/save_gif_folder`.
 *
 * Данная директория должна существовать или быть созданной методом,
 * использующим этот путь.
 *
 * @return QString Полный путь к временной директории. Если путь не может быть
 * определён, возвращает пустую строку.
 */
QString GifCreator::tempDirPath() {
  // Путь к директории с исполняемым файлом
  const QString projectDir = QCoreApplication::applicationDirPath();
  return projectDir + "/save_gif_folder";  // Путь к папке для скринов и GIF
}

/**
 * @brief Создаёт GIF-файл из сохранённых кадров.
 *
 * Метод объединяет последовательность изображений (кадров), сохранённых в
 * формате PNG, в единую GIF-анимацию. Также метод очищает временную директорию
 * от кадров после успешного создания GIF.
 *
 * @param frames_count Количество кадров, которые нужно включить в GIF.
 * @param frame_delay Задержка между кадрами в миллисекундах.
 *
 * @details
 * 1. Загружает первый кадр для определения размеров GIF.
 * 2. Инициализирует запись GIF с помощью `GifWriter`.
 * 3. Поочерёдно загружает кадры, конвертирует их в формат RGBA8888 и добавляет
 * в GIF.
 * 4. После успешного завершения записи завершает работу с `GifWriter` и удаляет
 * временные файлы (PNG).
 *
 * Если на любом этапе возникает ошибка (например, невозможность загрузить кадр
 * или записать его в GIF), процесс прерывается, и временные файлы остаются для
 * отладки.
 *
 * Пример использования:
 * ```cpp
 * GifCreator creator;
 * if (creator.createGif(10, 100)) {
 *     qDebug() << "GIF создан успешно!";
 * } else {
 *     qDebug() << "Ошибка создания GIF.";
 * }
 * ```
 *
 * @return bool Возвращает `true` при успешном создании GIF. Возвращает `false`,
 * если произошла ошибка на любом этапе процесса.
 */
bool GifCreator::createGif(const int frames_count, const int frame_delay) {
  const QImage first_image(imageFilePathMask().arg(0));
  if (first_image.isNull()) {
    qDebug() << "Не удалось загрузить первый кадр.";
    qDebug() << "Сохранение кадра в:" << first_image;
    return false;
  }

  GifWriter gif_writer;
  if (!GifBegin(&gif_writer, gifFilePath().toUtf8(),
                static_cast<uint32_t>(first_image.width()),
                static_cast<uint32_t>(first_image.height()),
                static_cast<uint32_t>(frame_delay))) {
    qDebug() << "Не удалось инициализировать запись GIF.";
    return false;
  }

  for (int frame = 0; frame < frames_count; ++frame) {
    QImage image(imageFilePathMask().arg(frame));
    if (image.isNull()) {
      qDebug() << "Кадр" << frame << "не удалось загрузить.";
      GifEnd(&gif_writer);
      return false;
    }

    qDebug() << "Кадр" << frame << "Успешно загружен.";

    // Конвертация в формат RGBA8888
    QImage rgba_image = image.convertToFormat(QImage::Format_RGBA8888);
    if (!GifWriteFrame(&gif_writer, rgba_image.constBits(),
                       static_cast<uint32_t>(rgba_image.width()),
                       static_cast<uint32_t>(rgba_image.height()),
                       static_cast<uint32_t>(frame_delay))) {
      qDebug() << "Ошибка записи кадра" << frame << "в GIF.";
      GifEnd(&gif_writer);
      return false;
    }
  }

  if (!GifEnd(&gif_writer)) {
    qDebug() << "Ошибка завершения записи GIF.";
    return false;
  }

  qDebug() << "GIF успешно создан!";

  // Удаление всех PNG файлов
  QDir dir(tempDirPath());
  dir.setNameFilters(QStringList() << "frame_*.png");
  dir.setFilter(QDir::Files);

  // Удаление всех файлов, соответствующих фильтру
  QFileInfoList files = dir.entryInfoList();
  for (const QFileInfo &fileInfo : files) {
    if (fileInfo.isFile()) {
      if (QFile::remove(fileInfo.absoluteFilePath())) {
        qDebug() << "Удален файл:" << fileInfo.absoluteFilePath();
      } else {
        qDebug() << "Ошибка при удалении файла:" << fileInfo.absoluteFilePath();
      }
    }
  }

  return true;
}
