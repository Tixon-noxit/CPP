//
// Created by KWAZAR_ on 03.10.2024.
//
#pragma once

#include "../../../models/include/Model.h"
#include "Controller.h"
#include "Transformation.h"

namespace s21 {

class ModelControllerFacade {
 private:
  Model model_;
  Controller controller_;
  void initialize() {
    std::cout << typeid(this).name() << " is initialized! " << std::endl;
  }

 public:
  ModelControllerFacade() : controller_(&model_) { initialize(); }

  void loadModel(const std::string& filename) {
    controller_.loadModel(filename);
  }

  void translateModel(const float x, const float y, const float z) {
    model_.translate(x, y, z);
  }

  void rotateModel(const float angleX, const float angleY, const float angleZ) {
    Rotate rotate(angleX, angleY, angleZ);
    controller_.transformModel(&rotate);
  }

  void scaleModel(const float scaleFactor) { model_.scale(scaleFactor); }

  void setLineColor(const float red, const float green, const float blue,
                    const float alpha) {
    LineColor lineColor(red, green, blue, alpha);
    controller_.transformModel(&lineColor);
  }

  void setVertexColor(const float red, const float green, const float blue,
                      const float alpha) {
    VertexColor vertexColor(red, green, blue, alpha);
    controller_.transformModel(&vertexColor);
  }

  void setBackgroundColor(const float red, const float green, const float blue,
                          const float alpha) {
    BackgroundColor backgroundColor(red, green, blue, alpha);
    controller_.transformModel(&backgroundColor);
  }

  void setProjectionType(std::string type) {
    ProjectionType projectionType(type);
    controller_.transformModel(&projectionType);
  }

  void setLineType(std::string type) {
    LineType lineType(type);
    controller_.transformModel(&lineType);
  }

  void setVertexDisplay(std::string type) {
    VertexDisplay vertexDisplay(type);
    controller_.transformModel(&vertexDisplay);
  }

  void setVertexSize(std::string type) {
    VertexSize vertexSize(type);
    controller_.transformModel(&vertexSize);
  }

  void setLineSize(std::string size) {
    LineSize lineSize(size);
    controller_.transformModel(&lineSize);
  }

  std::array<float, 4> getBack() {
    return model_.getSettings()->getBackgroundColor();
  };

  Model* getModel() { return &model_; }
};

}  // namespace s21
