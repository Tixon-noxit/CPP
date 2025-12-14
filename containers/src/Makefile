CXX      := -g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -O2 --coverage
LDFLAGS  := -L/usr/lib -lm -lgtest -lgtest_main -lpthread --coverage
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
COVERAGE_DIR := coverage
TARGET   := s21_containers
INCLUDE  := -Iinclude/
SRC      :=                      \
   $(wildcard containers/*.cpp)         \
   $(wildcard containers/s21_list/*.cpp) \
   $(wildcard containers/s21_vector/*.cpp) \
   $(wildcard containers/s21_map/*.cpp) \
   $(wildcard containers/s21_array/*.cpp) \
   $(wildcard containers/s21_multiset/*.cpp) \
   $(wildcard containers/s21_set/*.cpp) \
   $(wildcard containers/s21_queue/*.cpp) \
   $(wildcard containers/s21_stack/*.cpp) \
   $(wildcard tests/*.cpp) \

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)
AUTHORS := essiecel, filchlen, peanutgr

all: build test # $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)


test: $(OBJECTS)
	@echo "┏=========================================┓"
	@echo "┃              Building tests             ┃"
	@echo "┗=========================================┛"
	@mkdir -p $(APP_DIR)/$@
	@$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $(APP_DIR)/$@/$@
	@echo "┏=========================================┓"
	@echo "┃               Running tests             ┃"
	@echo "┗=========================================┛"
	@./build/apps/$@/$@

coverage: test
	@echo "┏=========================================┓"
	@echo "┃      Collecting test coverage data      ┃"
	@echo "┗=========================================┛"
	@mkdir -p $(COVERAGE_DIR)
	@lcov --capture --directory $(OBJ_DIR) --output-file $(COVERAGE_DIR)/$(TARGET).info --ignore-errors inconsistent
	@genhtml $(COVERAGE_DIR)/$(TARGET).info --output-directory $(COVERAGE_DIR) --ignore-errors inconsistent
	@open ./$(COVERAGE_DIR)/index.html


check_style:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@find . \( -name '*.hpp' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -n -style=Google

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@find . \( -name '*.hpp' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -i -style=Google

cppcheck:
	@echo "Running cppcheck..."
	cppcheck --enable=all --std=c++17 .

finish_project: check_style cppcheck test

.PHONY: all build clean debug release info

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	@echo "┏=========================================┓"
	@echo "┃     Cleaning up your $(TARGET)     ┃"
	@echo "┗=========================================┛"
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -rvf $(COVERAGE_DIR)/

info:
	@echo "[*] Project:         ${TARGET}      "
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
	@echo "[*] Authors:         ${AUTHORS}"
