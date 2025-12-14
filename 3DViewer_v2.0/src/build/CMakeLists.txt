cmake_minimum_required(VERSION 3.22)
project(CPP4_3DViewer_v2.0)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#SET(CMAKE_CXX_FLAGS_DEBUG "-g2")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

add_definitions(-DGL_SILENCE_DEPRECATION)

add_executable(CPP4_3DViewer_v2.0
        ../main.cpp
        ../components/controllers/include/Controller.h
        ../components/controllers/include/ModelControllerFacade.h
        ../components/controllers/include/Transformation.h
        ../gui/MainWindow.cpp
        ../gui/Scene3DView.cpp
        ../gui/methods/main_window_methods.cpp
        ../models/include/OBJParser.h
        ../models/include/Model.h
        ../models/sourse/OBJParser.cpp
        ../models/sourse/Model.cpp
        ../models/include/utils.h
        ../components/Settings/sourse/ConfigManager.cpp
        ../components/Settings/sourse/SettingsModel.cpp
        ../components/Settings/include/ConfigManager.h
        ../components/Settings/include/SettingsModel.h
        ../gui/methods/GifCreator.cpp
       ../gui/methods/gif.h
        ../gui/methods/gif.cpp
)

target_link_libraries(CPP4_3DViewer_v2.0
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::OpenGL
        Qt::OpenGLWidgets
)
