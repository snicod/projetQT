cmake_minimum_required(VERSION 3.24)
project(qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(RESOURCES resources.qrc)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)


add_executable(qt main.cpp mainWindow.h mainWindow.cpp target.h target.cpp gamehandler.h gamehandler.cpp ${RESOURCES})

target_link_libraries(qt
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Multimedia
        )
