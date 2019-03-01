cmake_minimum_required(VERSION 3.10)
project(group_hw_2 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Wshadow")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

enable_testing()

set(CMAKE_C_STANDARD 99)
include_directories(${CHECK_INCLUDE_DIRS})

find_package(Check REQUIRED)
find_package(Threads REQUIRED)

add_executable(test_priority_queue src/priority_queue.c src/priority_queue.h tests/test_priority_queue.c)
add_executable(test_stack  src/stack.c src/stack.h tests/test_stack.c)

target_link_libraries(test_stack ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_priority_queue ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(test_stack ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stack)
add_test(test_priority_queue ${CMAKE_CURRENT_BINARY_DIR}/tests/test_priority_queue)
