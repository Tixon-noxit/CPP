CC:=g++
TEST_FILES:= ./models/sourse/Model.cpp ./models/sourse/OBJParser.cpp ./components/Settings/sourse/SettingsModel.cpp ./components/Settings/sourse/ConfigManager.cpp
OFILES := $(shell find ./build/tests -iname '*.o')
LIBS = -lgtest -lgcov
LIBS_GCOV = $(LIBS) -fprofile-arcs -ftest-coverage --coverage -g2
EXECUTE_FILE = CPP4_3DViewer_v2.0
TEST_EXECUTE_FILE = tests
GCOVDIR := gcov_report
TEST_BUILD_DIR := build/tests

all: install

install:
	@make uninstall
	@cd build && cmake . && make
	cd build && ./$(EXECUTE_FILE)

uninstall:
	cd build && rm -rf $(EXECUTE_FILE)

tests: clean $(TEST_BUILD_DIR)
	@echo "Run building tests"
	@$(CC) -c ./models/sourse/Model.cpp $(LIBS_GCOV) -o $(TEST_BUILD_DIR)/Model.o
	@$(CC) -c ./models/sourse/OBJParser.cpp $(LIBS_GCOV) -o $(TEST_BUILD_DIR)/OBJParser.o
	@$(CC) -c ./components/Settings/sourse/SettingsModel.cpp $(LIBS_GCOV) -o $(TEST_BUILD_DIR)/SettingsModel.o
	@$(CC) -c ./components/Settings/sourse/ConfigManager.cpp $(LIBS_GCOV) -o $(TEST_BUILD_DIR)/ConfigManager.o
	@find . \( -name "*.o" -o -name "*.gcno" \) -exec mv {} $(TEST_BUILD_DIR)/ \;
	@$(CC) ./tests/*.cpp $(TEST_BUILD_DIR)/*.o $(LIBS) -o $(TEST_BUILD_DIR)/test
	./$(TEST_BUILD_DIR)/test

gcov_report: tests
	@mkdir -p $(GCOVDIR)
	@find . -name '*.gcda' -exec mv -t $(GCOVDIR) {} +
	@find . -name '*.gcno' -exec mv -t $(GCOVDIR) {} +
	@find . -name '*.gch' -exec mv -t $(GCOVDIR) {} +
	lcov --exclude '/usr/*' --exclude '*/include/*' --capture --directory $(GCOVDIR) --output-file $(GCOVDIR)/coverage.info
	genhtml $(GCOVDIR)/coverage.info --output-directory $(GCOVDIR)/html

dvi:
	doxygen Doxyfile
	@sed -i 's/$$(LATEX_CMD) refman/$$(LATEX_CMD) refman || true/g' ./doxygen_output/latex/Makefile
	make -C ./doxygen_output/latex/ || true

dist:
	tar -cf 3DViewer_v2.0.tar .

style:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -style=file:../materials/linters/.clang-format -i {} +
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -style=file:../materials/linters/.clang-format -n {} +

clean :
	@find ./../ -type f -name '*.gch' ! -name 'CMakeLists.txt' -delete
	@find ./../ -type f -name '*.tar' ! -name 'CMakeLists.txt' -delete
	@find ./../ -type f -name '*.o' ! -name 'CMakeLists.txt' -delete
	@find ./../ -type f -name '*.a' ! -name 'CMakeLists.txt' -delete
	@find ./../ -type f -name '*.gcda' ! -name 'CMakeLists.txt' -delete
	@find ./../ -type f -name '*.gcov' ! -name 'CMakeLists.txt' -delete
	@find ./../ -type f -name '*.gcno' ! -name 'CMakeLists.txt' -delete
	@find ./../ -name '*.dSYM' -exec rm -rv {} +
	@find ./../ -name 'doxygen_output' -exec rm -rv {} +
	@find ./../ -name 'gcov_report' -exec rm -rv {} +
	@find ./../ -type f -name '*.out' ! -name 'CMakeLists.txt' -delete
	@find ./../ -type f -name 'vgcore*' ! -name 'CMakeLists.txt' -delete
	@find ./../ -type f -name 'config.json' ! -name 'CMakeLists.txt' -delete
	@find ./build -type f -name 'tests' ! -name 'CMakeLists.txt' -delete
	@find ./build -type f -name 'test' ! -name 'CMakeLists.txt' -delete
	find build -mindepth 1 ! -path "build/tests" ! -path "build/CMakeLists.txt" -exec rm -rf {} +


rebuild: clean install