//
// Created by KWAZAR_ on 12.11.2024.
//

#include "tests.h"

namespace s21 {

class ModelTest : public ::testing::Test {
 protected:
  std::unique_ptr<Model> model = std::make_unique<Model>();

  std::string objData =
      "v 0.0 0.0 0.0\nv 1.0 0.0 0.0\nv 0.0 1.0 0.0\n"
      "f 1 2 3\nvn 0.0 0.0 1.0\n";

  void SetUp() override {
    // Создаем тестовый .obj файл
    std::ofstream file("test.obj");
    file << objData;
    file.close();
  }

  void TearDown() override {
    std::remove("test.obj");
    model.reset();
    model.release();
    if (!model) std::cout << "Model deleted" << std::endl;
  }
};

// Проверка загрузки .obj файла
TEST_F(ModelTest, LoadOBJFile) {
  model->loadFromFile("test.obj");

  EXPECT_TRUE(model->objLoaded());
  EXPECT_EQ(model->getVertexCount(), 3);
  EXPECT_EQ(model->getFaceCount(), 1);
}

// Проверка метода translate
TEST_F(ModelTest, TranslateVertices) {
  model->loadFromFile("test.obj");
  model->translate(1.0f, 2.0f, 3.0f);

  auto vertices = model->getVertices();
  EXPECT_FLOAT_EQ(vertices[0].x.data, 1.0f);
  EXPECT_FLOAT_EQ(vertices[0].y.data, 2.0f);
  EXPECT_FLOAT_EQ(vertices[0].z.data, 3.0f);
}

TEST_F(ModelTest, TranslateVertices2) {
  model->loadFromFile("test.obj");
  model->translate(2.0f, 1.0f, 3.0f);

  auto vertices = model->getVertices();
  EXPECT_FLOAT_EQ(vertices[0].x.data, 2.0f);
  EXPECT_FLOAT_EQ(vertices[0].y.data, 1.0f);
  EXPECT_FLOAT_EQ(vertices[0].z.data, 3.0f);
}

TEST_F(ModelTest, TranslateVertices3) {
  model->loadFromFile("test.obj");
  model->translate(3.0f, 2.0f, 1.0f);

  auto vertices = model->getVertices();
  EXPECT_FLOAT_EQ(vertices[0].x.data, 3.0f);
  EXPECT_FLOAT_EQ(vertices[0].y.data, 2.0f);
  EXPECT_FLOAT_EQ(vertices[0].z.data, 1.0f);
}

// Проверка метода rotate
TEST_F(ModelTest, RotateVertices) {
  model->loadFromFile("test.obj");
  model->rotate(90.0f, 0.0f, 0.0f);

  auto vertices = model->getVertices();
  EXPECT_NEAR(vertices[2].y.data, 0.0f, 1e-5);
  EXPECT_NEAR(vertices[2].z.data, 1.0f, 1e-5);
}

// Проверка метода scale
TEST_F(ModelTest, ScaleVertices) {
  model->loadFromFile("test.obj");
  model->scale(2.0f);

  auto vertices = model->getVertices();
  EXPECT_FLOAT_EQ(vertices[1].x.data, 2.0f);
  EXPECT_FLOAT_EQ(vertices[1].y.data, 0.0f);
  EXPECT_FLOAT_EQ(vertices[1].z.data, 0.0f);
}

TEST_F(ModelTest, ScaleVertices2) {
  model->loadFromFile("test.obj");
  model->scale(22.0f);

  auto vertices = model->getVertices();
  EXPECT_FLOAT_EQ(vertices[1].x.data, 22.0f);
  EXPECT_FLOAT_EQ(vertices[1].y.data, 0.0f);
  EXPECT_FLOAT_EQ(vertices[1].z.data, 0.0f);
}

TEST_F(ModelTest, ScaleVertices3) {
  model->loadFromFile("test.obj");
  model->scale(12.0f);

  auto vertices = model->getVertices();
  EXPECT_FLOAT_EQ(vertices[1].x.data, 12.0f);
  EXPECT_FLOAT_EQ(vertices[1].y.data, 0.0f);
  EXPECT_FLOAT_EQ(vertices[1].z.data, 0.0f);
}

// Тест: Исключение при невозможности открыть файл
TEST_F(ModelTest, LoadFromFile_FileNotOpen) {
  // Передаем несуществующий файл
  EXPECT_THROW(model->loadFromFile("non_existent.obj"), std::runtime_error);
}

TEST_F(ModelTest, LoadFromFile_FailedToParse_NullInput) {
  EXPECT_THROW(model->loadFromFile(""), std::runtime_error);  // Пустой путь
}

TEST_F(ModelTest, LoadFromFile_FailedToParse_InvalidPath) {
  EXPECT_THROW(model->loadFromFile("nonexistent_file.obj"),
               std::runtime_error);  // Несуществующий файл
}

TEST_F(ModelTest, NegativeScaleVertices) {
  model->loadFromFile("test.obj");
  model->scale(-2.0f);

  auto vertices = model->getVertices();
  EXPECT_FLOAT_EQ(vertices[1].x.data, 0.5f);
  EXPECT_FLOAT_EQ(vertices[1].y.data, 0.0f);
  EXPECT_FLOAT_EQ(vertices[1].z.data, 0.0f);
}

// Проверка методов установки цвета
TEST_F(ModelTest, SetColors) {
  model->setLineColor(1.0f, 0.5f, 0.5f, 1.0f);
  auto settings = model->getSettings();

  std::vector<float> expectedLineColor = {1.0f, 0.5f, 0.5f, 1.0f};
  std::vector<float> actualLineColor(settings->getLineColor().begin(),
                                     settings->getLineColor().end());
  EXPECT_EQ(actualLineColor, expectedLineColor);

  model->setBackgroundColor(0.1f, 0.2f, 0.3f, 1.0f);
  std::vector<float> expectedBackgroundColor = {0.1f, 0.2f, 0.3f, 1.0f};
  std::vector<float> actualBackgroundColor(
      settings->getBackgroundColor().begin(),
      settings->getBackgroundColor().end());
  EXPECT_EQ(actualBackgroundColor, expectedBackgroundColor);
}

// Проверка настроек проекции
TEST_F(ModelTest, SetProjectionType) {
  model->setProjectionType("Perspective");
  auto settings = model->getSettings();
  EXPECT_EQ(settings->getProjectionType(), "Perspective");
}

// Проверка метода setLineType
TEST_F(ModelTest, SetLineType) {
  model->setLineType("Dashed");
  auto settings = model->getSettings();
  EXPECT_EQ(settings->getLineType(), "Dashed");

  model->setLineType("Solid");
  EXPECT_EQ(settings->getLineType(), "Solid");
}

// Проверка метода setVertexDisplay
TEST_F(ModelTest, SetVertexDisplay) {
  model->setVertexDisplay("Points");
  auto settings = model->getSettings();
  EXPECT_EQ(settings->getVertexDisplay(), "Points");

  model->setVertexDisplay("Lines");
  EXPECT_EQ(settings->getVertexDisplay(), "Lines");
}

TEST_F(ModelTest, SetLineColor) {
  // Устанавливаем значения цвета
  model->setLineColor(0.1f, 0.2f, 0.3f, 0.4f);

  // Получаем настройки из модели
  auto settings = model->getSettings();

  // Проверяем, что значения цвета корректно установлены
  EXPECT_FLOAT_EQ(settings->getLineColor()[0], 0.1f);  // Красный
  EXPECT_FLOAT_EQ(settings->getLineColor()[1], 0.2f);  // Зеленый
  EXPECT_FLOAT_EQ(settings->getLineColor()[2], 0.3f);  // Синий
  EXPECT_FLOAT_EQ(settings->getLineColor()[3], 0.4f);  // Альфа
}

TEST_F(ModelTest, SetVertexColor) {
  // Устанавливаем цвет вершин
  model->setVertexColor(0.5f, 0.7f, 0.2f, 1.0f);

  // Получаем настройки
  auto settings = model->getSettings();

  // Получаем цвет вершин как std::array и преобразуем его в std::vector для
  // сравнения
  std::vector<float> expectedColor = {0.5f, 0.7f, 0.2f, 1.0f};
  std::vector<float> actualColor(settings->getVertexColor().begin(),
                                 settings->getVertexColor().end());

  // Проверяем, что цвет вершин установлен правильно
  EXPECT_EQ(actualColor, expectedColor);

  // Устанавливаем новый цвет для вершин
  model->setVertexColor(1.0f, 0.0f, 0.0f, 1.0f);

  // Новый цвет
  expectedColor = {1.0f, 0.0f, 0.0f, 1.0f};
  actualColor = std::vector<float>(settings->getVertexColor().begin(),
                                   settings->getVertexColor().end());

  // Проверяем, что новый цвет вершин установлен правильно
  EXPECT_EQ(actualColor, expectedColor);
}

// Тест с числовыми значениями, если getVertexSize возвращает числовое значение
TEST_F(ModelTest, SetVertexSize) {
  // Устанавливаем размер вершин
  model->setVertexSize("Small");

  // Получаем настройки и проверяем, что верное числовое значение установлено
  auto settings = model->getSettings();
  EXPECT_EQ(settings->getVertexSize(), 1.0f);

  // Устанавливаем новый размер вершин
  model->setVertexSize("Large");

  // Проверяем, что новый размер вершин установлен правильно
  EXPECT_EQ(settings->getVertexSize(), 20.0f);
}

TEST_F(ModelTest, SetLineSize) {
  // Устанавливаем размер линии
  model->setLineSize("Thin");

  // Получаем настройки и проверяем, что верное числовое значение установлено
  auto settings = model->getSettings();
  EXPECT_EQ(settings->getLineSize(), 1.0f);

  // Устанавливаем новый размер линии
  model->setLineSize("Thick");

  // Проверяем, что новый размер линии установлен правильно
  EXPECT_EQ(settings->getLineSize(), 7.0f);
}

}  // namespace s21
