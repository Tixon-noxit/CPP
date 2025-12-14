# Компилятор
CXX = g++
CC = gcc
INCLUDE = -I/usr/include/ncurses -Isrc/common/inc -Iinc
BIN_FOLDER = ../../../bin/


# Флаги линковки
LDFLAGS =

# Флаги для GTK и ncurses
NCURSES_FLAGS = -lncurses

# Флаги компилятора
CXXFLAGS = -std=c++17 -g3 -Wall -Wextra $(INCLUDE)
CFLAGS = -std=c11 -g3 -Wall -Wextra $(INCLUDE)

# Названия целей сборки
TARGET_SNAKE_CLI = snake_cli

OBJ_FOLDER = ./out

# Имя исполняемого файла
TARGET = snake_game

# Исходные файлы
SRCS = ../src/Model.cpp \
./src/View_cli.cpp \
../../../common/src/common.c \
./src/snake_cli.cpp \
../../../gui/cli/src/frontend.c

# Объектные файлы
OBJS = $(OBJ_FOLDER)/Model.o \
$(OBJ_FOLDER)/View_cli.o \
$(OBJ_FOLDER)/snake_cli.o \
$(OBJ_FOLDER)/common.o \
$(OBJ_FOLDER)/frontend.o


# Правило по умолчанию
all: $(TARGET)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
	@echo "┏=================================================┓"
	@echo "┃  Начало сборки и установки консольной змейки    ┃"
	@echo "┗=================================================┛"
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(NCURSES_FLAGS)

# Создание директории для объектных файлов
$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

# Правило для сборки объектных файлов из C
$(OBJ_FOLDER)/%.o: ../../../common/src/%.c | $(OBJ_FOLDER)
	@$(CC) $(CFLAGS) -c $< -o $@

# Дополнительное правило для frontend.c
$(OBJ_FOLDER)/frontend.o: ../../../gui/cli/src/frontend.c | $(OBJ_FOLDER)
	@$(CC) $(CFLAGS)  -c $< -o $@

# Правило для сборки объектных файлов из C++
$(OBJ_FOLDER)/%.o: ./src/%.cpp | $(OBJ_FOLDER)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для сборки объектных файлов из C++
$(OBJ_FOLDER)/%.o: ../src/%.cpp | $(OBJ_FOLDER)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	@rm -rf $(TARGET) $(OBJ_FOLDER)



# Правило для установки
install: $(TARGET)
	@cp $(TARGET) $(BIN_FOLDER)
	@echo "┏=================================================┓"
	@echo "┃  Игра успешно установлена в $(BIN_FOLDER)       ┃"
	@echo "┗=================================================┛"

# Правило для удаления установленного файла
uninstall:
	rm -f $(BIN_FOLDER)/$(TARGET)

# Check and format code style
check_style:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -n -style=Google

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@find . \( -name '*.h' -о -name '*.cpp' \) -print0 | xargs -0 clang-format -i -style=Google
