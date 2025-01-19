////
//// Created by KWAZAR_ on 12.11.2024.
////
//
// #include "tests.h"
//
// class ConsoleCapture {
// public:
//    ConsoleCapture() {
//        old_buffer_ = std::cout.rdbuf();
//        std::cout.rdbuf(ss_.rdbuf());
//    }
//
//    ~ConsoleCapture() {
//        std::cout.rdbuf(old_buffer_);
//    }
//
//    std::string getCapturedOutput() {
//        return ss_.str();
//    }
//
// private:
//    std::streambuf* old_buffer_;
//    std::stringstream ss_;
//};
//
//// Тест для изменения цвета вершин
// TEST(ModelTest, SetVertexColor) {
//     s21::Model model;
//
//     // Устанавливаем цвет для вершин (красный, зеленый, синий, alpha)
//     model.setVertexColor(0.5f, 0.5f, 0.0f, 1.0f);  // Желтый цвет
//
//     auto settings = model.getSettings();
//
//     // Проверяем значения цвета
//     EXPECT_FLOAT_EQ(settings->getVertexColor()[0], 0.5f);  // Red
//     EXPECT_FLOAT_EQ(settings->getVertexColor()[1], 0.5f);  // Green
//     EXPECT_FLOAT_EQ(settings->getVertexColor()[2], 0.0f);  // Blue
//     EXPECT_FLOAT_EQ(settings->getVertexColor()[3], 1.0f);  // Alpha
// }
//
//// Тест для изменения цвета фона
// TEST(ModelTest, SetBackgroundColor) {
//     s21::Model model;
//
//     // Устанавливаем цвет фона (черный с прозрачностью)
//     model.setBackgroundColor(0.0f, 0.0f, 0.0f, 0.0f);  // Прозрачный черный
//
//     auto settings = model.getSettings();
//
//     // Проверяем значения цвета фона
//     EXPECT_FLOAT_EQ(settings->getBackgroundColor()[0], 0.0f);  // Red
//     EXPECT_FLOAT_EQ(settings->getBackgroundColor()[1], 0.0f);  // Green
//     EXPECT_FLOAT_EQ(settings->getBackgroundColor()[2], 0.0f);  // Blue
//     EXPECT_FLOAT_EQ(settings->getBackgroundColor()[3], 0.0f);  // Alpha
// }
//
//// Тест для установки типа проекции
// TEST(ModelTest, SetProjectionType) {
//     s21::Model model;
//
//     // Устанавливаем тип проекции (например, перспективная)
//     model.setProjectionType("Perspective");
//
//     auto settings = model.getSettings();
//
//     // Проверяем, что тип проекции изменился
//     EXPECT_EQ(settings->getProjectionType(), "Perspective");
// }
//
//// Тест для установки типа линии
// TEST(ModelTest, SetLineType) {
//     s21::Model model;
//
//     // Устанавливаем тип линии (например, пунктирная линия)
//     model.setLineType("Dashed");
//
//     auto settings = model.getSettings();
//
//     // Проверяем, что тип линии изменился
//     EXPECT_EQ(settings->getLineType(), "Dashed");
// }
//
//// Тест для изменения отображения вершин
// TEST(ModelTest, SetVertexDisplay) {
//     s21::Model model;
//
//     // Устанавливаем тип отображения вершин (например, точки)
//     model.setVertexDisplay("Points");
//
//     auto settings = model.getSettings();
//
//     // Проверяем, что отображение вершин изменилось
//     EXPECT_EQ(settings->getVertexDisplay(), "Points");
// }
//
//// Тест на установку и получение размера вершины
// TEST(SettingsModelTest, SetAndGetVertexSize_Test) {
//     s21::SettingsModel settings;
//
//     // Установка разных значений для vertexSize_
//     settings.setVertexSize("Large");
//     EXPECT_EQ(settings.getVertexSize(), 20.0f);
//
//     settings.setVertexSize("Medium");
//     EXPECT_EQ(settings.getVertexSize(), 10.0f);
//
//     settings.setVertexSize("Small");
//     EXPECT_EQ(settings.getVertexSize(), 1.0f);
//
//     settings.setVertexSize("Unknown");
//     EXPECT_EQ(settings.getVertexSize(), 1.0f);  // Проверка на неизвестное
//     значение
// }
//
//// Тест на установку и получение ширины линии
// TEST(SettingsModelTest, SetAndGetLineSize_Test) {
//     s21::SettingsModel settings;
//
//     // Установка разных значений для lineWidth_
//     settings.setLineSize("Thick");
//     EXPECT_EQ(settings.getLineSize(), 7.0f);
//
//     settings.setLineSize("Medium");
//     EXPECT_EQ(settings.getLineSize(), 4.0f);
//
//     settings.setLineSize("Thin");
//     EXPECT_EQ(settings.getLineSize(), 1.0f);
//
//     settings.setLineSize("Unknown");
//     EXPECT_EQ(settings.getLineSize(), 1.0f);  // Проверка на неизвестное
//     значение
// }