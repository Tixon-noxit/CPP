//
// Created by Тихон Чабусов on 15.10.2024.
//

#pragma once

#include <array>
#include <iostream>
#include <sstream>
#include <string>

#include "./ConfigManager.h"

namespace s21 {
/**
 * @class SettingsModel
 * @brief Класс для хранения и управления конфигурационными настройками.
 *
 * Этот класс предоставляет интерфейс для установки и получения конфигурационных
 * параметров, таких как цвет фона, тип проекции и толщина линии.
 */
class SettingsModel {
 public:
  // Сеттеры
  void setBackgroundColor(float r, float g, float b, float alpha);

  void setLineColor(float r, float g, float b, float alpha);

  void setVertexColor(float r, float g, float b, float alpha);

  void setProjectionType(const std::string& type);

  void setLineType(const std::string& type);

  void setVertexDisplay(const std::string& type);

  void setVertexSize(const std::string& type);

  void setLineSize(const std::string& size);

  // Геттеры

  [[nodiscard]] const std::array<float, 4>& getBackgroundColor() const;

  [[nodiscard]] const std::array<float, 4>& getLineColor() const;

  [[nodiscard]] const std::array<float, 4>& getVertexColor() const;

  [[nodiscard]] std::string getProjectionType() const;

  [[nodiscard]] std::string getLineType() const;

  [[nodiscard]] std::string getVertexDisplay() const;

  [[nodiscard]] float getVertexSize() const;

  [[nodiscard]] float getLineSize() const;

 private:
  static void initializeSettings(const std::string& className) {
    std::cout << className << " is initialized! " << std::endl;
  }

  std::unique_ptr<ConfigManager> config_ = std::make_unique<ConfigManager>();

  /**
   * @brief Цвет контура ребра, представленный массивом из четырёх значений: R,
   * G, B, Alpha.
   */
  std::array<float, 4> lineColor_{};

  /**
   * @brief Цвет ребра, представленный массивом из четырёх значений: R, G, B,
   * Alpha.
   */
  std::array<float, 4> vertexColor_{};

  /**
   * @brief Тип проекции, задается как строка (например, "параллельная",
   * "Центральная").
   */
  std::string projectionType_;

  /**
   * @brief Тип контура ребра, задается как строка (например, "сплошная",
   * "пунктирная").
   */
  std::string lineType_;

  /**
   * @brief Способ отображения, задается как строка (например, "отсутствует",
   * "круг", "квадрат").
   */
  std::string vertexDisplay_;

  /**
   * @brief Размер ребер, задается как строка (например, "Small", "Medium",
   * "Large").
   */
  std::string vertexSize_;

  /**
   * @brief Толщина линии, задается в виде целого числа.
   */
  std::string lineWidth_;

  /**
   * @brief Цвет фона, представленный массивом из четырёх значений: R, G, B,
   * Alpha.
   */
  std::array<float, 4> backgroundColor_{};

 public:
  SettingsModel();
};

}  // namespace s21