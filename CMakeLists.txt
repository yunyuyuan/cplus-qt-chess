cmake_minimum_required(VERSION 3.17)
project(c)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(c main.cpp windows/connect/connect.h windows/connect/connect.cpp windows/game/game.h windows/game/game.cpp components/button/button.h components/button/button.cpp components/utils.h windows/chief/chief.h windows/chief/chief.cpp components/board/board.h components/board/board.cpp components/board/board.cpp components/board/board.h)

set_target_properties(c PROPERTIES AUTOMOC TRUE)
target_link_libraries(c Qt5::Widgets Qt5::Network)

