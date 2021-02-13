cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-ftemplate-depth=1000 -fconstexpr-ops-limit=1000")

include_directories(${INCLUDE_DIRECTORIES} "../include/")

file(GLOB_RECURSE SRC
    "../include/*.h"
    "../include/*.hpp"
    "tests/*.hpp"
)

add_executable(${PROJECT_NAME} main.cpp ${SRC})
