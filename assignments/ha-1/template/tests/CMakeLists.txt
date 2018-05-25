enable_testing()

find_package(Check REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

include_directories(. ../src)

add_executable(test_binarize test_binarize.c ../src/binarize.c)
add_executable(test_task test_task.c ../src/task.c)

target_link_libraries(test_binarize ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_task ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(test_binarize ${CMAKE_CURRENT_BINARY_DIR}/test_binarize)