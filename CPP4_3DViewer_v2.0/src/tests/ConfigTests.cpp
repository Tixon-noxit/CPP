////
//// Created by KWAZAR_ on 12.11.2024.
////
//
// #include "tests.h"
//
// class ConfigManagerTest : public ::testing::Test {
// protected:
//    s21::ConfigManager configManager;
//
//    void SetUp() override {
//        // Инициализируем настройки вручную
//        configManager.updateSetting("vertexSize", "Large");
//        configManager.updateSetting("lineWidth", "Medium");
//    }
//};
//
// TEST_F(ConfigManagerTest, TestGetSettingAsString_NotFound) {
//    // Проверяем поведение при отсутствии ключа
//    std::string result =
//    configManager.getSettingAs<std::string>("nonExistingKey");
//    EXPECT_EQ(result, "");
//}
//
// TEST_F(ConfigManagerTest, TestUpdateSetting_InvalidKey) {
//    configManager.updateSetting("nonExistingKey", "NewValue");
//    std::string result =
//    configManager.getSettingAs<std::string>("nonExistingKey");
//    EXPECT_EQ(result, "");
//}
//
//
//
