cmake_minimum_required(VERSION 3.8)
project(template)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES test_binarize.c)
add_executable(template ${SOURCE_FILES})