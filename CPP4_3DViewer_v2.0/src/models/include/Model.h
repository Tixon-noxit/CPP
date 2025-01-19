#ifndef CPP4_3DVIEWER_V2_0_MODEL_H
#define CPP4_3DVIEWER_V2_0_MODEL_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../../components/Settings/include/SettingsModel.h"
#include "OBJParser.h"

namespace s21 {

class Model {
 private:
  OBJNotation* notation_ = nullptr;
  SettingsModel settings_;

  void initialize() {
    std::cout << typeid(this).name() << " is initialized! " << std::endl;
  }

 public:
  Model() { initialize(); }
  ~Model() { delete notation_; }

  void loadFromFile(const std::string& filename);

  // Преобразования модели
  void translate(float x, float y, float z) const;
  void rotate(float angleX, float angleY, float angleZ) const;
  void scale(float scaleFactor) const;

  // Геттеры для информации о модели
  [[nodiscard]] int getVertexCount() const {
    return notation_->geometricVertices.size();
  }
  [[nodiscard]] int getFaceCount() const {
    return notation_->faceNormalVertices.size();
  }

  // Геттеры для вершин и граней
  [[nodiscard]] const std::vector<GeometricVertex>& getVertices() const {
    return notation_->geometricVertices;
  }

  void setLineColor(float red, float green, float blue,
                    float alpha);  // Цвет фона сцены

  void setVertexColor(float red, float green, float blue, float alpha);
  void setBackgroundColor(float red, float green, float blue, float alpha);

  void setProjectionType(const std::string& type);
  void setLineType(const std::string& type);
  void setVertexDisplay(const std::string& type);
  void setVertexSize(const std::string& type);
  void setLineSize(const std::string& size);

  bool objLoaded() const { return notation_ != nullptr; }

  [[nodiscard]] const std::vector<FaceNormal>& getFaces() const {
    return notation_->faceNormalVertices;
  }
  SettingsModel* getSettings() { return &settings_; };
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_MODEL_H
