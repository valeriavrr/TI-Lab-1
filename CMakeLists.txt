cmake_minimum_required(VERSION 4.0)
project(ti_lab_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "D:/Qt/6.9.3/msvc2022_64")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(ti_lab_1 main.cpp
        mainwindow.cpp
        mainwindow.h)

target_link_libraries(ti_lab_1
        Qt6::Core
        Qt6::Widgets
)