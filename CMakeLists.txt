# DimitriiTrater

cmake_minimum_required(VERSION 3.23)

project(ping-pong)

set(CMAKE_CXX_STANDARD 20)


set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "C:/Users/1/CLionProjects/libs/SFML-2.5.1/lib/cmake/SFML")



set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)

add_executable(
    ping-pong                           main.cpp

    player/player.hpp                   player/player.cpp
    player_control/player_control.hpp   player_control/player_control.cpp


    ball/ball.hpp                       ball/ball.cpp
    ball_collision/ball_collision.hpp   ball_collision/ball_collision.cpp
    
)

target_link_libraries(ping-pong sfml-graphics)