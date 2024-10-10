# Название проекта
TEMPLATE = app
TARGET = snake_desktop

# Версия стандарта C++
CONFIG += c++17

# Указание на использование Qt
QT += widgets core gui

# Путь к исходникам и заголовочным файлам
INCLUDEPATH += ../../../../common/inc \
               ../../../../brick_game/snake/inc \
               inc

# Исходные файлы
SOURCES += ../src/Model.cpp \
           ./src/ControllerDesktop.cpp \
           ./src/snake_desktop.cpp \
           ../../../common/src/common.c \
           ../../../gui/desktop/src/frontend.cpp

# Заголовочные файлы
HEADERS += ../../../common/inc/common.h \
           ../../../brick_game/snake/inc/Model.h \
           ../../../brick_game/snake/Desktop/inc/ControllerDesktop.h \
           ./inc/snake_desktop.h \
           ../../../gui/desktop/inc/frontend.h

# Настройка компилятора и линкера
QMAKE_CXXFLAGS += -Wall -Wextra -g3
QMAKE_LFLAGS += -g

# Выходная директория для сборки
DESTDIR = ../../../bin
OBJECTS_DIR = ./build/obj  # Директория для объектных файлов
MOC_DIR = ./build/moc      # Директория для файлов, сгенерированных MOC
RCC_DIR = ./build/rcc      # Директория для файлов, сгенерированных RCC
UI_DIR = ./build/ui        # Директория для файлов, сгенерированных UIC

# Дополнительные библиотеки
LIBS += -lncurses
