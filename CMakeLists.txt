cmake_minimum_required(VERSION 3.20)

project(PIC)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE PIC_SRC src/*.cpp)

add_executable(PIC pic.cpp ${PIC_SRC})

add_subdirectory(libraries/magic_enum)

add_subdirectory(libraries/fmt)

target_link_libraries(PIC PUBLIC magic_enum fmt)
