//
// Created by Тихон Чабусов on 15.10.2024.
//

#include "../include/ConfigManager.h"

#ifdef __linux__
#include <linux/limits.h>
#endif

using namespace s21;
std::mutex ConfigManager::mutex_;

/**
 * @brief Приватный конструктор для загрузки конфигурации при создании
 * экземпляра.
 *
 * Загружает настройки из файла конфигурации при инициализации.
 */
ConfigManager::ConfigManager() { loadSettings(fileConfigurations); }

/**
 * @brief Загружает настройки из файла конфигурации.
 * @param filePath Путь к файлу конфигурации.
 * Читает файл конфигурации и обновляет параметры модели.
 */
void ConfigManager::loadSettings(const std::string& filePath) {
  std::cout << "ConfigManager is initialized! " << std::endl;
  if (!isConfigExists(filePath)) {
    std::ofstream configFile(filePath);
    char name[PATH_MAX] = {0};
    configFile << standardConfig << std::endl;
    std::cout << "Config file created at " << realpath(filePath.c_str(), name)
              << std::endl;
  }
  std::ifstream configFile(filePath);
  if (!configFile.is_open()) {
    std::cerr << "Unable to open config file!" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(configFile, line)) {
    auto [key, value] = parseLine(line);
    key.erase(std::remove(key.begin(), key.end(), '\"'), key.end());
    value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
    if (!key.empty() && !value.empty()) {
      settings_.emplace(key, value);  // Сохраняем ключ-значение в контейнер
    }
  }

  configFile.close();
}

/**
 * @brief МОтладочный метод - позволяет по ключу получать значение настройки
 *
 * @param key - ключ для поиска настройки и ее значения в контейнере
 *
 * @return - значение искомого параметра в виде строки или пустая строка при его
 * отсутствии
 */
std::string ConfigManager::getSetting(const std::string& key) const {
  if (const auto it = settings_.find(key); it != settings_.end()) {
    return it->second;
  }
  return "";
}

/**
 * @brief Парсит строку конфигурационного файла.
 *
 * @param line Строка из файла конфигурации, содержащая ключ-значение.
 *
 * Эта функция разделяет строку на ключ и значение, после чего
 * обновляет соответствующие параметры модели.
 */
std::pair<std::string, std::string> ConfigManager::parseLine(
    const std::string& line) {
  // Найти позицию разделителя ':'
  if (const auto delimiterPos = line.find(':');
      delimiterPos != std::string::npos) {
    // Извлечь ключ и значение
    std::string key = line.substr(0, delimiterPos);
    std::string value = line.substr(delimiterPos + 1);

    // Удалить пробелы с начала и конца ключа и значения
    trim(key);
    trim(value);

    // Вернуть ключ и значение в виде пары
    return {key, value};
  }

  // Если разделителя нет, вернуть пустую пару
  return {"", ""};
}

/**
 * @brief Удаляет начальные и конечные пробелы из строки.
 *
 * @param str Ссылка на строку, которая будет изменена.
 */
void ConfigManager::trim(std::string& str) {
  str.erase(str.begin(),
            std::find_if(str.begin(), str.end(), [](const unsigned char ch) {
              return !std::isspace(ch);
            }));
  str.erase(
      std::find_if(str.rbegin(), str.rend(),
                   [](const unsigned char ch) { return !std::isspace(ch); })
          .base(),
      str.end());
}

/**
 * @brief Обновляет значение настройки в файле конфигурации.
 *
 * Метод ищет в файле конфигурации строку, содержащую указанный ключ,
 * и заменяет соответствующее значение на новое. Файл конфигурации
 * перезаписывается после внесения изменений, что позволяет сохранить
 * новые параметры между сессиями.
 *
 * @param key Ключ настройки, которую необходимо обновить (например,
 * "backgroundColor").
 * @param r Красный цвет как float
 * @param g Зеленый цвет как float
 * @param b Синий цвет как float
 * @param alpha Альфа канал как float
 * @param newValue Новое значение, которое нужно присвоить указанному ключу.
 * Например, список [0.2, 0.7, 0.3, 1.0] для цветового массива.
 *
 * @note Файл конфигурации должен быть отформатирован в соответствии с
 * JSON-структурой, где каждая пара ключ-значение находится на отдельной
 * строке.
 *
 * @note Принимает список float и конвертирует их в стоку для удобства записи
 */
void ConfigManager::updateSetting(const std::string& key, const float r,
                                  const float g, const float b,
                                  const float alpha) {
  std::ostringstream oss;
  oss << "[" << r << ", " << g << ", " << b << ", " << alpha << "]";
  const std::string colorStr = oss.str();

  updateSetting(key, colorStr);
}

/**
 * @brief Проверяет на существование конфиг файла по текущему пути
 * @param filename Имя файла
 * @return True если конфиг файл существует
 */
bool ConfigManager::isConfigExists(const std::string& filename) {
  return access(filename.c_str(), F_OK) != -1;
}

/**
 * @brief Обновляет значение настройки в файле конфигурации.
 *
 * Метод ищет в файле конфигурации строку, содержащую указанный ключ,
 * и заменяет соответствующее значение на новое. Файл конфигурации
 * перезаписывается после внесения изменений, что позволяет сохранить
 * новые параметры между сессиями.
 *
 * @param key Ключ настройки, которую необходимо обновить (например,
 * "backgroundColor").
 * @param newValue Новое значение, которое нужно присвоить указанному ключу.
 * Например, Число 5 для размера толщины линии.
 *
 * @note Файл конфигурации должен быть отформатирован в соответствии с
 * JSON-структурой, где каждая пара ключ-значение находится на отдельной
 * строке.
 *
 * @note Принимает число int и конвертирует их в стоку для удобства записи
 */
// void ConfigManager::updateSetting(const std::string& key, int value) {
//   std::ostringstream oss;
//   oss << "[" << value << "]";
//   std::string ValueStr = oss.str();
//
//   updateSetting(key, ValueStr);
// }

/**
 * @brief Обновляет значение настройки в файле конфигурации.
 *
 * Метод ищет в файле конфигурации строку, содержащую указанный ключ,
 * и заменяет соответствующее значение на новое. Файл конфигурации
 * перезаписывается после внесения изменений, что позволяет сохранить
 * новые параметры между сессиями.
 *
 * @param key Ключ настройки, которую необходимо обновить (например,
 * "backgroundColor").
 * @param newValue Новое значение, которое нужно присвоить указанному ключу.
 * Например, строка "[0.2, 0.7, 0.3, 1.0]" для цветового массива
 * или "\"Central\"" для строки типа проекции или "5" для толщины линии ребра
 * проекции.
 *
 * @note Файл конфигурации должен быть отформатирован в соответствии с
 * JSON-структурой, где каждая пара ключ-значение находится на отдельной
 * строке.
 *
 * @note Важно передавать строковые значения с кавычками для строк,
 * чтобы сохранить синтаксис JSON (например, "\"Central\"").
 */
void ConfigManager::updateSetting(const std::string& key,
                                  const std::string& newValue) {
  std::lock_guard<std::mutex> lock(mutex_);

  // Открываем конфигурационный файл для чтения
  std::ifstream configFile(fileConfigurations);
  if (!configFile.is_open()) {
    std::cerr << "Unable to open config file!" << std::endl;
    return;
  }

  // Чтение файла в строку
  std::string fileContent((std::istreambuf_iterator<char>(configFile)),
                          std::istreambuf_iterator<char>());
  configFile.close();

  // Поиск ключа
  size_t keyPos = fileContent.find("\"" + key + "\"");
  if (keyPos == std::string::npos) {
    std::cerr << "Key not found in config: " << key << std::endl;
    return;
  }

  // Поиск начала значения (после двоеточия)
  size_t valuePos = fileContent.find(":", keyPos);
  if (valuePos == std::string::npos) {
    std::cerr << "Error parsing config file: missing ':' after key " << key
              << std::endl;
    return;
  }

  // Находим позицию начала значения, пропуская пробелы
  valuePos = fileContent.find_first_not_of(" \t", valuePos + 1);
  if (valuePos == std::string::npos) {
    std::cerr << "Error parsing config file: invalid value position for key "
              << key << std::endl;
    return;
  }

  // Поиск конца значения
  size_t endPos;
  if (fileContent[valuePos] == '[') {
    // Значение — это массив, ищем закрывающую скобку ']'
    endPos = fileContent.find(']', valuePos);
    if (endPos == std::string::npos) {
      std::cerr << "Error parsing config file: incomplete array for key " << key
                << std::endl;
      return;
    }
    endPos++;  // Включаем ']' в замену
  } else if (fileContent[valuePos] == '"') {
    // Значение — это строка, ищем закрывающую кавычку
    endPos = fileContent.find('"', valuePos + 1);
    if (endPos == std::string::npos) {
      std::cerr << "Error parsing config file: incomplete string for key "
                << key << std::endl;
      return;
    }
    endPos++;  // Включаем '"' в замену
  } else {
    // Значение — это число или другой простой тип, ищем запятую или конец
    // строки
    endPos = fileContent.find_first_of(",}", valuePos);
    if (endPos == std::string::npos) {
      std::cerr
          << "Error parsing config file: value not properly terminated for key "
          << key << std::endl;
      return;
    }
  }

  // Проверка: если новое значение не начинается с '[', оборачиваем его в
  // кавычки
  std::string finalValue = newValue;
  if (newValue[0] == '[' || newValue[1] == '[' || newValue[2] == '[') {
    fileContent.replace(valuePos, endPos - valuePos, newValue);
  } else {
    finalValue = "\"" + newValue + "\"";
    fileContent.replace(valuePos, endPos - valuePos, finalValue);
  }

  // Файл с новым содержимым
  std::ofstream outFile(fileConfigurations);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open config file for writing!" << std::endl;
    return;
  }
  outFile << fileContent;
  outFile.close();
}

// Специализация для std::array<float, 4>
template <>
std::array<float, 4> ConfigManager::getSettingAs<std::array<float, 4>>(
    const std::string& key) const {
  // Извлечение значения по ключу
  std::string value = settings_.at(key);

  // Ищем квадратные скобки
  const size_t start = value.find('[');
  const size_t end = value.find(']');
  if (start == std::string::npos || end == std::string::npos) {
    throw std::runtime_error("Array brackets not found in settings");
  }

  // Извлекаем подстроку с значениями и убираем пробелы
  std::string arrayString = value.substr(start + 1, end - start - 1);
  arrayString.erase(
      std::remove_if(arrayString.begin(), arrayString.end(), ::isspace),
      arrayString.end());

  std::array<float, 4> result = {0.0f, 0.0f, 0.0f, 0.0f};
  std::istringstream iss(arrayString);
  char comma;  // Чтение запятых

  for (float& f : result) {
    if (!(iss >> f)) {
      throw std::runtime_error("Failed to read float value");
    }
    if (iss.peek() == ',') {
      iss >> comma;  // Игнорируем запятую
    }
  }

  return result;
}

// Специализация для std::string
template <>
std::string ConfigManager::getSettingAs<std::string>(
    const std::string& key) const {
  const auto it = settings_.find(key);
  if (it == settings_.end()) {
    return "";
  }

  std::string result = it->second;

  // Удаляем запятую, если она есть в конце
  if (!result.empty() && result.back() == ',') {
    result.pop_back();
  }

  return result;
}

// Специализация для int
template <>
int ConfigManager::getSettingAs<int>(const std::string& key) const {
  return std::stoi(settings_.at(key));
}
