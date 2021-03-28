cmake_minimum_required(VERSION 3.17)
project(3d_render C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2)
link_libraries(m)


add_executable(3d_render
        src/main.c)
