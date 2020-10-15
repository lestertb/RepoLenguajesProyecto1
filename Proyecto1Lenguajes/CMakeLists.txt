cmake_minimum_required(VERSION 3.17)
project(Proyecto1Lenguajes C)

set(CMAKE_C_STANDARD 99)

find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(Proyecto1Lenguajes main.c)

target_link_libraries(Proyecto1Lenguajes sfml-system sfml-system sfml-graphics)

target_link_libraries(Proyecto1Lenguajes csfml-system csfml-system csfml-graphics)



