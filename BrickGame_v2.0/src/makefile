# Названия целей сборки
TARGET_SNAKE_CONSOLE = snake_console
TARGET_SNAKE_DESKTOP = snake_desktop
TARGET_TETRIS_CONSOLE = tetris_console
TARGET_TETRIS_DESKTOP = tetris_desktop







# Правило по умолчанию
all:
	@read -p "Что собрать (snake console (1) / snake desktop (2) / tetris console (3) / tetris desktop (4) ): " target; \
    	if [ $$target = "1" ]; then \
    		$(MAKE) $(TARGET_SNAKE_CONSOLE); \
    	elif [ $$target = "2" ]; then \
    		$(MAKE) $(TARGET_SNAKE_DESKTOP); \
		elif [ $$target = "3" ]; then \
			$(MAKE) $(TARGET_TETRIS_CONSOLE); \
    	else \
    		echo "Неправильный выбор, используйте '1', '2' или 'snake', 'tetris'."; \
    		exit 1; \
    	fi

# Создание директории для исполняемых файлов
$(BIN_FOLDER):
	@if [ ! -d "$(BIN_FOLDER)" ]; then \
        echo "Папка $(BIN_FOLDER) не существует. Создаю..."; \
        mkdir -p $(BIN_FOLDER); \
    else \
        echo "Папка $(BIN_FOLDER) уже существует."; \
    fi

# Сборка десктопной версии Змейки
$(TARGET_SNAKE_DESKTOP): $(BIN_FOLDER)
	@echo "Сборка Десктопной версии Змейки"
	$(MAKE) -C ./brick_game/snake -f Makefile_Desktop all

# Сборка консольной версии Змейки
$(TARGET_SNAKE_CONSOLE): $(BIN_FOLDER)
	@echo "┏=================================================┓"
	@echo "┃        Сборка Консольной версии Змейки          ┃"
	@echo "┗=================================================┛"
	$(MAKE) -C ./brick_game/snake/Console install

# Сборка консольной версии Тетриса
$(TARGET_TETRIS_CONSOLE): $(BIN_FOLDER)
	@echo "Сборка Консольной версии Тетриса"
	$(MAKE) -C ./brick_game/tetris all

MKDIR_P := mkdir -p
CFLAGS += -std=c11 -g3 -Wall -Wextra -fprofile-arcs -ftest-coverage
BUILD_FOLDER = bin
BIN_FOLDER = $(BUILD_FOLDER)
OBJ_FOLDER = $(BUILD_FOLDER)/obj

# Define compiler and flags
CXX = g++
C = gcc
CXXFLAGS = -std=c++17 -g3 -Wall -Wextra -I/include -I/include -fprofile-arcs -ftest-coverage
CFLAGS = -std=c11 -g3 -Wall -Wextra -fprofile-arcs -ftest-coverage
LIBS = -lgtest -lgtest_main -pthread

# Targets
#all: test gcov_report

tests: $(BUILD_FOLDER)/test_snake_model
	./$(BUILD_FOLDER)/test_snake_model

$(BUILD_FOLDER)/test_snake_model: $(OBJ_FOLDER)/test_snake_model.o $(OBJ_FOLDER)/Model.o $(OBJ_FOLDER)/common.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJ_FOLDER)/test_snake_model.o: tests/test_snake_model.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_FOLDER)/Model.o: brick_game/snake/src/Model.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_FOLDER)/common.o: common/src/common.c
	@mkdir -p $(dir $@)
	$(C) $(CFLAGS) -c $< -o $@

gcov_report: tests
	lcov --capture --directory $(OBJ_FOLDER) --output-file coverage.info --ignore-errors inconsistent
	genhtml coverage.info --output-directory out --ignore-errors inconsistent
	open ./out/index.html

# Построение документации.
dvi:
	# doxygen brick_game/snake/Doxyfile
	open brick_game/snake/docs/html/index.html


# Выполняется создание tar-файла, содержащего дистрибутивную
# поставку этой программы.
dist: $(NAME_PROGRAMM)
	tar -cvzf snake_cpp.tar.gz -C $(CURDIR) brick_game/snake/Desktop



install:
	$(MAKE) -C ./brick_game/tetris install
	$(MAKE) -C ./brick_game/snake/Console install
#	$(MAKE) -C ./brick_game/tetris/Desktop
#	$(MAKE) -C ./brick_game/snake/Desktop

uninstall:
	rm -rf bin/


check_style:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -n -style=Google
	@find . \( -name '*.h' -o -name '*.c' \) -print0 | xargs -0 clang-format -n -style=Google

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -i -style=Google
	@find . \( -name '*.h' -o -name '*.c' \) -print0 | xargs -0 clang-format -i -style=Google


# Цель для очистки
clean:
	rm -f $(TARGET_SNAKE_CLI) $(TARGET_SNAKE_DESKTOP) $(TARGET_TETRIS_CLI) $(TARGET_TETRIS_DESKTOP)
	$(MAKE) -C ./brick_game/tetris clean
	$(MAKE) -C ./brick_game/snake/Console clean
	$(MAKE) -C ./brick_game/tetris/Desktop clean
	$(MAKE) -C ./brick_game/snake/Desktop clean
	rm -rf bin/
	find . -name 'snake_high_scores.txt' -type f -delete
	find . -name 'max_score.txt' -type f -delete

