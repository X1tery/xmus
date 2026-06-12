cmake_minimum_required(VERSION 3.23)

project(xmus)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/headers")

add_executable(xmus)

target_sources(xmus
PRIVATE
    src/main.cpp
    src/headers/input.hpp
    src/headers/file.hpp
    src/headers/parser.hpp
    src/headers/wave.hpp
    src/headers/pcm.hpp
    src/code/input.cpp
    src/code/file.cpp
    src/code/parser.cpp
    src/code/wave.cpp
    src/code/pcm.cpp
)