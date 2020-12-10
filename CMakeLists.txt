cmake_minimum_required(VERSION 3.17)
project(c)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(c main.cpp windows/connect/connect.h windows/connect/connect.cpp windows/game/game.h windows/game/game.cpp components/button/button.h components/button/buton.cpp components/utils.cpp)

target_link_libraries(c Qt5::Widgets)

