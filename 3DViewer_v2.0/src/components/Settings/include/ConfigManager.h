#pragma once

#include <unistd.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define fileConfigurations "../config.json"

namespace s21 {

/**
 * @class ConfigManager
 * @brief Singleton класс для управления конфигурацией приложения.
 *
 * Этот класс отвечает за загрузку конфигурационных настроек из файла
 * и предоставляет доступ к текущей модели настроек. Для предотвращения
 * создания нескольких экземпляров используется паттерн Singleton.
 */
class ConfigManager {
 private:
  /**
   * @brief Мьютекс для обеспечения потокобезопасности при доступе к экземпляру
   * класса.
   */
  static std::mutex mutex_;

  void loadSettings(const std::string& filePath);

  static std::pair<std::string, std::string> parseLine(const std::string& line);

  static void trim(std::string& str);

  std::unordered_map<std::string, std::string>
      settings_;  // Контейнер для хранения настроек

  const std::string standardConfig = R"({
  "backgroundColor": [0, 0, 0, 1],
  "projectionType": "Central",
  "lineColor": [1, 1, 1, 1],
  "lineWidth": "Medium",
  "lineType": "Solid",
  "vertexDisplay": "None",
  "vertexSize": "Medium",
  "vertexColor": [1, 0, 0, 1]
})";

 public:
  ConfigManager();

  // Метод для получения значения по ключу
  [[nodiscard]] std::string getSetting(const std::string& key) const;

  // отладочный - посмотреть что в контейнере настроек
  void printSettings() const {
    std::cout << " " << std::endl;
    for (const auto& [fst, snd] : settings_) {
      std::cout << fst << ": " << snd << std::endl;
    }
    std::cout << " " << std::endl;
  }

  /**
   * @brief Удалённый конструктор копирования для предотвращения клонирования
   * объекта.
   */
  ConfigManager(ConfigManager& other) = delete;

  /**
   * @brief Оператор присваивания удалён для предотвращения копирования объекта.
   */
  void operator=(const ConfigManager&) = delete;

  static void updateSetting(const std::string& key,
                            const std::string& newValue);

  static void updateSetting(const std::string& key, float r, float g, float b,
                            float alpha);

  static bool isConfigExists(const std::string& filename);

  //  void updateSetting(const std::string& key, int value);

  template <typename T>
  T getSettingAs(const std::string& key) const;
};
};  // namespace s21