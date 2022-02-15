cmake_minimum_required(VERSION 3.20)
project(Laba5b C)

set(CMAKE_C_STANDARD 11)

add_executable(Laba5b main.c libs/algorithms/algorithms.c libs/algorithms/algorithms.h libs/data_structures/matrix/matrix.h libs/data_structures/matrix/matrix.c)
add_subdirectory(libs)

target_link_libraries(Laba5b algorithms)
target_link_libraries(Laba5b data_structures)