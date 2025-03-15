cmake_minimum_required(VERSION 3.5)

project(ecc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GMP_LIB_PATH "/usr/local/lib")

add_library(
    schifra
    core/core.h
    core/point.cpp
    core/add.cpp
    core/mult.cpp
    core/embed.cpp
    core/sqrt.cpp
)

target_link_directories(schifra PRIVATE ${GMP_LIB_PATH})
target_link_libraries(schifra gmp)
