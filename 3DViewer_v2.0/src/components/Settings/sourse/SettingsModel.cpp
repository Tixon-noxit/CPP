//
// Created by Тихон Чабусов on 15.10.2024.
//

#include "../include/SettingsModel.h"

using namespace s21;

SettingsModel::SettingsModel() {
  initializeSettings("SettingsModel");
  try {
    projectionType_ = config_->getSettingAs<std::string>("projectionType");
  } catch (const std::exception& e) {
    projectionType_ = "Central";
    std::cerr << "Error retrieving projectionType: " << e.what() << std::endl;
  }

  try {
    lineType_ = config_->getSettingAs<std::string>("lineType");
  } catch (const std::exception& e) {
    lineType_ = "Solid";
    std::cerr << "Error retrieving lineType: " << e.what() << std::endl;
  }

  try {
    vertexSize_ = config_->getSettingAs<std::string>("vertexSize");
  } catch (const std::exception& e) {
    vertexSize_ = "Medium";
    std::cerr << "Error retrieving vertexSize: " << e.what() << std::endl;
  }

  try {
    lineWidth_ = config_->getSettingAs<std::string>("lineWidth");
  } catch (const std::exception& e) {
    lineWidth_ = "Thin";
    std::cerr << "Error retrieving lineWidth: " << e.what() << std::endl;
  }

  try {
    vertexDisplay_ = config_->getSettingAs<std::string>("vertexDisplay");
  } catch (const std::exception& e) {
    lineWidth_ = "None";
    std::cerr << "Error retrieving vertexDisplay: " << e.what() << std::endl;
  }

  vertexColor_ = {0.0f, 0.0f, 0.0f, 0.0f};
  try {
    vertexColor_ = config_->getSettingAs<std::array<float, 4>>("vertexColor");
  } catch (const std::exception& e) {
    std::cerr << "Error retrieving vertexColor color: " << e.what()
              << std::endl;
  }

  lineColor_ = {0.0f, 0.0f, 0.0f, 0.0f};
  try {
    lineColor_ = config_->getSettingAs<std::array<float, 4>>("lineColor");
  } catch (const std::exception& e) {
    std::cerr << "Error retrieving lineColor color: " << e.what() << std::endl;
  }

  backgroundColor_ = {0.0f, 0.0f, 0.0f, 0.0f};
  try {
    backgroundColor_ =
        config_->getSettingAs<std::array<float, 4>>("backgroundColor");
  } catch (const std::exception& e) {
    std::cerr << "Error retrieving background color: " << e.what() << std::endl;
  }
}

// SET ----------------------------------------------------------------

/**
 * @brief Устанавливает цвет фона.
 *
 * @param r Красный канал цвета (диапазон 0.0 - 1.0).
 * @param g Зелёный канал цвета (диапазон 0.0 - 1.0).
 * @param b Синий канал цвета (диапазон 0.0 - 1.0).
 * @param alpha Альфа-канал (прозрачность, диапазон 0.0 - 1.0).
 *
 * Этот метод задает цвет фона, который представлен массивом из 4-х значений:
 * красный, зелёный, синий и альфа (прозрачность).
 */
void SettingsModel::setBackgroundColor(float r, float g, float b, float alpha) {
  backgroundColor_ = {r, g, b, alpha};
  config_->updateSetting("backgroundColor", r, g, b, alpha);
}

/**
 * @brief Устанавливает цвет контура ребра.
 *
 * @param r Красный канал цвета (диапазон 0.0 - 1.0).
 * @param g Зелёный канал цвета (диапазон 0.0 - 1.0).
 * @param b Синий канал цвета (диапазон 0.0 - 1.0).
 * @param alpha Альфа-канал (прозрачность, диапазон 0.0 - 1.0).
 *
 * Этот метод задает цвет контура ребра, который представлен массивом из 4-х
 * значений: красный, зелёный, синий и альфа (прозрачность).
 */
void SettingsModel::setLineColor(float r, float g, float b, float alpha) {
  lineColor_ = {r, g, b, alpha};
  config_->updateSetting("lineColor", r, g, b, alpha);
}

/**
 * @brief Устанавливает цвет ребра.
 *
 * @param r Красный канал цвета (диапазон 0.0 - 1.0).
 * @param g Зелёный канал цвета (диапазон 0.0 - 1.0).
 * @param b Синий канал цвета (диапазон 0.0 - 1.0).
 * @param alpha Альфа-канал (прозрачность, диапазон 0.0 - 1.0).
 *
 * Этот метод задает цвет ребра, который представлен массивом из 4-х значений:
 * красный, зелёный, синий и альфа (прозрачность).
 */
void SettingsModel::setVertexColor(float r, float g, float b, float alpha) {
  vertexColor_ = {r, g, b, alpha};
  config_->updateSetting("vertexColor", r, g, b, alpha);
}

/**
 * @brief Устанавливает тип проекции.
 *
 * @param type Строка, содержащая тип проекции (например, "параллельная " или
 * "центральная").
 */
void SettingsModel::setProjectionType(const std::string& type) {
  projectionType_ = type;
  config_->updateSetting("projectionType", type);
}

/**
 * @brief Устанавливает размер ребер.
 *
 * @param type Строка, содержащая размер ребер.
 */
void SettingsModel::setVertexSize(const std::string& type) {
  vertexSize_ = type;
  config_->updateSetting("vertexSize", type);
}

/**
 * @brief Устанавливает способ отображения.
 *
 * @param type Строка, содержащая тип ребер.
 */
void SettingsModel::setVertexDisplay(const std::string& type) {
  vertexDisplay_ = type;
  config_->updateSetting("vertexDisplay", type);
}

/**
 * @brief Устанавливает тип ребер.
 *
 * @param type Строка, содержащая тип ребер (например, "сплошная" или
 * "пунктирная").
 */
void SettingsModel::setLineType(const std::string& type) {
  lineType_ = type;
  config_->updateSetting("lineType", type);
}

/**
 * @brief Устанавливает толщину линии.
 *
 * @param size Строка, представляющее толщину линии.
 */
void SettingsModel::setLineSize(const std::string& size) {
  lineWidth_ = size;
  config_->updateSetting("lineWidth", size);
}

// GET ----------------------------------------------------------------

/**
 * @brief Возвращает текущий цвет фона.
 *
 * @return Константная ссылка на массив, содержащий значения цветовых каналов
 * (R, G, B, Alpha).
 */
const std::array<float, 4>& SettingsModel::getBackgroundColor() const {
  return backgroundColor_;
}

/**
 * @brief Возвращает текущий цвет линий.
 *
 * @return Константная ссылка на массив, содержащий значения цветовых каналов
 * (R, G, B, Alpha).
 */
const std::array<float, 4>& SettingsModel::getLineColor() const {
  return lineColor_;
}

/**
 * @brief Возвращает текущий цвет ребер.
 *
 * @return Константная ссылка на массив, содержащий значения цветовых каналов
 * (R, G, B, Alpha).
 */
const std::array<float, 4>& SettingsModel::getVertexColor() const {
  return vertexColor_;
}

/**
 * @brief Возвращает текущий тип проекции.
 *
 * @return Строка, содержащая тип проекции.
 */
std::string SettingsModel::getProjectionType() const { return projectionType_; }

/**
 * @brief Возвращает текущий тип контура ребер.
 *
 * @return Строка, содержащая тип проекции.
 */
std::string SettingsModel::getLineType() const { return lineType_; }

/**
 * @brief Возвращает текущий тип отображения ребер.
 *
 * @return Строка, содержащая тип проекции.
 */
std::string SettingsModel::getVertexDisplay() const { return vertexDisplay_; }

/**
 * @brief Возвращает текущий тип размера ребер.
 *
 * @return Число, размер ребер проекции.
 */
float SettingsModel::getVertexSize() const {
  if (vertexSize_ == "Large") {
    return 20.0f;
  } else if (vertexSize_ == "Medium") {
    return 10.0f;
  } else {
    return 1.0f;
  }
}

/**
 * @brief Возвращает текущую толщину линии.
 *
 * @return Строка, представляющая толщину линии.
 */
float SettingsModel::getLineSize() const {
  float lineWidth;

  if (lineWidth_ == "Thick") {
    lineWidth = 7.0f;
  } else if (lineWidth_ == "Medium") {
    lineWidth = 4.0f;
  } else {
    lineWidth = 1.0f;
  }
  return lineWidth;
}
