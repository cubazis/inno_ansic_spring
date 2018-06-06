enable_testing()

find_package(Check REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})
include_directories(. ../sources)

add_executable(test_stack test_stack.c ../sources/stack.c ../sources/node.c)
add_executable(test_queue test_priority_queue.c ../sources/priority_queue.c ../sources/node.c)
add_executable(debug ../main.c ../sources/priority_queue.c ../sources/node.c)

target_link_libraries(test_stack ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_queue ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
