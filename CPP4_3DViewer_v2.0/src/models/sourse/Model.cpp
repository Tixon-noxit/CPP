#include "../include/Model.h"

#include <iostream>

namespace s21 {

void Model::loadFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file!");
  }
  notation_ = s21::parseOBJ(file);

  if (notation_ == nullptr) {
    throw std::runtime_error("Failed to parse OBJ file!");
  }
}

void Model::translate(const float x, const float y, const float z) const {
  for (auto& vertex : notation_->geometricVertices) {
    vertex.x.data += x;
    vertex.y.data += y;
    vertex.z.data += z;
  }

  std::cout << "Translate - "
            << "x: " << x << ", "
            << "y: " << y << ", "
            << "z: " << z << ", " << std::endl;
}

void Model::rotate(const float angleX, const float angleY,
                   const float angleZ) const {
  const float radX = angleX * M_PI / 180.0;
  const float radY = angleY * M_PI / 180.0;
  const float radZ = angleZ * M_PI / 180.0;

  for (auto& vertex : notation_->geometricVertices) {
    float newY = vertex.y.data * cos(radX) - vertex.z.data * sin(radX);
    float newZ = vertex.y.data * sin(radX) + vertex.z.data * cos(radX);
    vertex.y.data = newY;
    vertex.z.data = newZ;

    float newX = vertex.x.data * cos(radY) + vertex.z.data * sin(radY);
    newZ = -vertex.x.data * sin(radY) + vertex.z.data * cos(radY);
    vertex.x.data = newX;
    vertex.z.data = newZ;

    newX = vertex.x.data * cos(radZ) - vertex.y.data * sin(radZ);
    newY = vertex.x.data * sin(radZ) + vertex.y.data * cos(radZ);
    vertex.x.data = newX;
    vertex.y.data = newY;
  }

  std::cout << "Rotate - "
            << "angleX: " << angleX << ", "
            << "angleY: " << angleY << ", "
            << "angleZ: " << angleZ << ", " << std::endl;
}

void Model::scale(const float scaleFactor) const {
  if (scaleFactor < 0) {
    for (auto& vertex : notation_->geometricVertices) {
      vertex.x.data /= -scaleFactor;
      vertex.y.data /= -scaleFactor;
      vertex.z.data /= -scaleFactor;
    }
  } else {
    for (auto& vertex : notation_->geometricVertices) {
      vertex.x.data *= scaleFactor;
      vertex.y.data *= scaleFactor;
      vertex.z.data *= scaleFactor;
    }
  }

  std::cout << "scale - " << scaleFactor << std::endl;
}

/**
 * @brief Изменение цвета линий модели
 * @param red Интенсивность красного канала
 * @param green Интенсивность зеленого канала
 * @param blue Интенсивность синего канала
 * @param alpha Прозрачность цвета (по умолчанию 1.0)
 */
void Model::setLineColor(const float red, const float green, const float blue,
                         const float alpha) {
  settings_.setLineColor(red, green, blue, alpha);

  std::cout << "Line Color - "
            << "Red: " << settings_.getLineColor()[0] << ", "
            << "Green: " << settings_.getLineColor()[1] << ", "
            << "Blue: " << settings_.getLineColor()[2] << ", "
            << "Alpha: " << settings_.getLineColor()[3] << std::endl;

  // Обновить отображение модели
  //  updateModelRendering();
}

/**
 * @brief Изменение цвета граней модели
 * @param red Интенсивность красного канала
 * @param green Интенсивность зеленого канала
 * @param blue Интенсивность синего канала
 * @param alpha Прозрачность цвета (по умолчанию 1.0)
 */
void Model::setVertexColor(const float red, const float green, const float blue,
                           const float alpha) {
  settings_.setVertexColor(red, green, blue, alpha);

  std::cout << "Vertex Color - "
            << "Red: " << settings_.getVertexColor()[0] << ", "
            << "Green: " << settings_.getVertexColor()[1] << ", "
            << "Blue: " << settings_.getVertexColor()[2] << ", "
            << "Alpha: " << settings_.getVertexColor()[3] << std::endl;
}

/**
 * @brief Изменение цвета фона сцены
 * @param red Интенсивность красного канала
 * @param green Интенсивность зеленого канала
 * @param blue Интенсивность синего канала
 * @param alpha Прозрачность цвета (по умолчанию 1.0)
 */
void Model::setBackgroundColor(const float red, const float green,
                               const float blue, const float alpha) {
  settings_.setBackgroundColor(red, green, blue, alpha);

  std::cout << "Background Color - "
            << "Red: " << settings_.getBackgroundColor()[0] << ", "
            << "Green: " << settings_.getBackgroundColor()[1] << ", "
            << "Blue: " << settings_.getBackgroundColor()[2] << ", "
            << "Alpha: " << settings_.getBackgroundColor()[3] << std::endl;
}

void Model::setProjectionType(const std::string& type) {
  settings_.setProjectionType(type);
  std::cout << "Projection Type: " << settings_.getProjectionType()
            << std::endl;
}

void Model::setLineType(const std::string& type) {
  settings_.setLineType(type);
  std::cout << "Line Type: " << settings_.getLineType() << std::endl;
}

void Model::setVertexDisplay(const std::string& type) {
  settings_.setVertexDisplay(type);
  std::cout << "Vertex Display: " << settings_.getVertexDisplay() << std::endl;
}

void Model::setVertexSize(const std::string& type) {
  settings_.setVertexSize(type);
  std::cout << "Vertex Size: " << settings_.getVertexSize() << std::endl;
}

void Model::setLineSize(const std::string& size) {
  settings_.setLineSize(size);
  std::cout << "Line Size: " << settings_.getLineSize() << std::endl;
}

}  // namespace s21
