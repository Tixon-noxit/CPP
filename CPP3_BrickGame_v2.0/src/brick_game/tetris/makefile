CC := gcc
MKDIR_P := mkdir -p
TAR := tar -cvzf
RM_RF := rm -rf
RM := rm
NAME_PROGRAMM = tetris
TARGET := $(NAME_PROGRAMM)
BUILD_FOLDER = ./build
OBJ_FOLDER = ./out
INC_FOLDER := -I ./inc -I ../../gui/cli/inc -I common/inc
#TEST_FILES =  tests/test.c  -lncurses -lcheck -lpthread
TEST_FLAG = -lncurses -lcheck -lpthread #-lsubunit -lm
CFLAGS := -std=c99 -g3 -Wall -Wextra -Werror --coverage -fprofile-arcs -ftest-coverage
OBJS_FSMSWITCHCASE := out/$(NAME_PROGRAMM).o out/matrix.o out/backend.o out/frontend.o out/common.o
INSTALL_DIR := ../../bin
GCOVDIR := gcov_report

UNAME := $(shell uname)

ifeq ($(UNAME),  Darwin)
	TEST_FLAG = -lncurses -lcheck -lpthread
else
	TEST_FLAG = -lncurses -lcheck -lpthread -lsubunit -lm
endif

.PHONY: all run install uninstall dvi dist test retest gcov_report clean format_project



# Основная цель сборки
all:  $(NAME_PROGRAMM)

#run: $(NAME_PROGRAMM)
#	@$(BUILD_FOLDER)/$(NAME_PROGRAMM)

$(NAME_PROGRAMM): $(OBJS_FSMSWITCHCASE)
	@$(MKDIR_P) $(BUILD_FOLDER)
	@ar rcs $(BUILD_FOLDER)/$(NAME_PROGRAMM).a out/*.o
	@$(CC) $(INC_FOLDER) $(CFLAGS) $^ -o $(BUILD_FOLDER)/$@ -lncurses
	@$(RM) out/*.o
	@$(RM_RF) ./out

out/%.o: ./src/%.c
	@$(MKDIR_P) ./out
	@$(CC) $(CFLAGS) -c $< -o $@

out/%.o: ../../gui/cli/src/%.c
	@$(MKDIR_P) ./out
	@$(CC) $(CFLAGS) -c $< -o $@

out/%.o: ../../common/src/%.c
	@$(MKDIR_P) ./out
	@$(CC) $(CFLAGS) -c $< -o $@

install: $(NAME_PROGRAMM)
	@$(MKDIR_P) $(DESTDIR)$(INSTALL_DIR)
	cp $(BUILD_FOLDER)/$(NAME_PROGRAMM) $(DESTDIR)$(INSTALL_DIR)/$(NAME_PROGRAMM)

uninstall:
	$(RM) $(DESTDIR)$(INSTALL_DIR)/$(NAME_PROGRAMM)
	$(RM_RF) $(BUILD_FOLDER) $(OBJ_FOLDER)


# Построение документации.
dvi:
	@open doxygen/html/index.html
	# doxygen Doxyfile

# Выполняется создание tar-файла, содержащего дистрибутивную
# поставку этой программы.
dist: $(NAME_PROGRAMM)
	@tar -cvzf $(NAME_PROGRAMM).tar.gz -C $(CURDIR) .

test: $(OBJS_FSMSWITCHCASE)
	@$(MKDIR_P) $(BUILD_FOLDER)
	@$(CC) $(CFLAGS) ../../tests/test.c ../../common/src/common.c ./src/matrix.c ./src/backend.c   -o $(BUILD_FOLDER)/$@ $(TEST_FLAG)
	@$(BUILD_FOLDER)/test
ifeq ($(UNAME),  Darwin)
	mv *.gcda *.gcno $(OBJ_FOLDER)
endif

gdb:
	gdb ./build/test
	run
	bt

gcov_report: test
	@$(MKDIR_P) $(BUILD_FOLDER)
	@lcov --capture --directory $(OBJ_FOLDER) --output-file $(BUILD_FOLDER)/coverage.info
	@genhtml $(BUILD_FOLDER)/coverage.info --output-directory $(BUILD_FOLDER)/html

clean:
	@echo "┏=========================================┓"
	@echo "┃     Cleaning up your $(TARGET)             ┃"
	@echo "┗=========================================┛"
	@$(RM_RF) $(BUILD_FOLDER) ./out

format_project:
	find .. -iname '*.c' | xargs clang-format -i
	find .. -iname '*.h' | xargs clang-format -i
	cppcheck --check-config --enable=all --suppress=missingIncludeSystem ..


