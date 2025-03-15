cmake_minimum_required(VERSION 3.5)

enable_testing()

find_package(GTest REQUIRED)

add_executable(
  test
  test.cpp
)

target_include_directories(test PUBLIC "${CMAKE_SOURCE_DIR}/src/lib/core")

target_link_libraries(
  test
  schifra
  GTest::gtest_main
)
