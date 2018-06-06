enable_testing()

find_package(Check REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

include_directories(. ../src)


add_executable(test_vector test_vector.c ../src/vector.c)
add_executable(test_vector_int test_vector_int.c ../src/vector_int.c)
add_executable(test_vector_qsort test_vector_qsort.c ../src/vector.c ../src/vector_int.c)

target_link_libraries(test_vector ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_vector_int ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_vector_qsort ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(test_vector ${CMAKE_CURRENT_BINARY_DIR}/lab4)
add_test(test_vector_int ${CMAKE_CURRENT_BINARY_DIR}/lab4)
add_test(test_vector_qsort ${CMAKE_CURRENT_BINARY_DIR}/lab4)
