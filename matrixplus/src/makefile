# Название компилятора и флагов
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2 --coverage
LDFLAGS = -lgtest -lgtest_main -lpthread --coverage

# Путь к исходным файлам
SRC_DIR = .
TEST_DIR = test
OBJ_DIR = obj

# Исходные файлы
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Файлы тестов
TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES = $(TEST_SRC_FILES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_BIN = test_runner

# Название статической библиотеки
STATIC_LIB = s21_matrix_oop.a

# Цели Makefile
all: $(STATIC_LIB) $(TEST_BIN)

# Создание статической библиотеки
$(STATIC_LIB): $(OBJ_FILES)
	ar rcs $@ $^

# Создание объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание объектных файлов для тестов
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

# Создание исполняемого файла для тестов
$(TEST_BIN): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CXX) $^ $(LDFLAGS) -o $@

# Запуск тестов
test: $(TEST_BIN)
	./$(TEST_BIN)

# Анализ покрытия кода
coverage: test
	lcov --capture --directory $(OBJ_DIR) --output-file coverage.info --ignore-errors inconsistent
	genhtml coverage.info --output-directory out --ignore-errors inconsistent
	open ./out/index.html

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(STATIC_LIB) $(TEST_BIN) *.gcda *.gcno coverage.info out

.PHONY: all test clean
