cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${INCLUDE_DIRECTORIES} "../include/")

file(GLOB_RECURSE SRC
    "../include/*.h"
    "../include/*.hpp"
    "tests/*.hpp"
)

add_executable(${PROJECT_NAME} main.cpp ${SRC})
