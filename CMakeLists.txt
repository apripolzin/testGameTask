cmake_minimum_required(VERSION 2.8.12)

project(testGameTask)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)

set(SRC "main.cpp" "game_field_element.cpp" "game_field.cpp" "mainwindow.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
