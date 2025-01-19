#include <gtest/gtest.h>

#include <sstream>

#include "../models/include/OBJParser.h"

using namespace s21;

// Фикстура для тестов
class OBJParserTest : public ::testing::Test {
 protected:
  OBJParserTest() { parser_ = new OBJParser(); }

  ~OBJParserTest() override { delete parser_; }

  OBJParser* parser_;
};

// Метод `getType`
TEST_F(OBJParserTest, Get_Type_Test_Valid_Type) {
  const char* validType = "v";

  EXPECT_EQ(parser_->getType(validType), SyntaxType::VLine);
}

TEST_F(OBJParserTest, Get_Type_Test_Invalid_Type) {
  const char* invalidType = "xyz";

  EXPECT_EQ(parser_->getType(invalidType), static_cast<SyntaxType>(-1));
}

// Метод `parse`
TEST_F(OBJParserTest, Invalid_Input_Test) {
  std::string invalidData = "invalid line content";
  std::istringstream input(invalidData);

  try {
    auto parsed = parser_->parse(input);
    SUCCEED();
    delete parsed;
  } catch (const std::runtime_error& e) {
    EXPECT_TRUE(std::string(e.what()).find("Problem string") !=
                std::string::npos)
        << "Unexpected error message: " << e.what();
    EXPECT_TRUE(std::string(e.what()).find("Invalid line #0") !=
                std::string::npos)
        << "Unexpected line information: " << e.what();
  } catch (...) {
    FAIL() << "Expected std::runtime_error, but got a different exception.";
  }
}

// Тест на обработку валидного ввода
TEST_F(OBJParserTest, Valid_Input_Test) {
  std::string validData = "v 1.0 2.0 3.0\nf 1 2 3";
  std::istringstream input(validData);

  try {
    OBJNotation* notation = parser_->parse(input);
    ASSERT_NE(notation, nullptr)
        << "Notation should not be null for valid input.";
    delete notation;
  } catch (...) {
    FAIL() << "Unexpected exception for valid input.";
  }
}
