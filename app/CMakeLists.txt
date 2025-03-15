cmake_minimum_required(VERSION 3.5)

project(app LANGUAGES CXX)

add_executable(app main.cpp)

target_include_directories(app PUBLIC "${CMAKE_SOURCE_DIR}/src/lib/core")

target_link_libraries(
  app
  schifra
)
