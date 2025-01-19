#ifndef CPP4_3DVIEWER_V2_0_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_CONTROLLER_H

#include "../../../models/include/Model.h"
#include "Transformation.h"

namespace s21 {

class Controller {
 private:
  Model* model_;
  void initialize() {
    std::cout << typeid(this).name() << " is initialized! " << std::endl;
  }

 public:
  explicit Controller(Model* model) : model_(model) { initialize(); }

  void loadModel(const std::string& filename) const {
    model_->loadFromFile(filename);
  }

  void transformModel(Transformation* transformation) const {
    transformation->apply(*model_);
  }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_CONTROLLER_H
