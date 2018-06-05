enable_testing()

find_package(Check REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

include_directories(. ../src)

add_executable(test_ipd test_ipd.c ../src/pointers.c)
add_executable(test_ipu test_ipu.c ../src/pointers.c)
add_executable(test_pointer_validation_function test_pointer_validation_function.c ../src/pointers.c)
add_executable(test_ips test_ips.c ../src/pointers.c)
add_executable(test_md test_md.c ../src/pointers.c)

target_link_libraries(test_ipd ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_ipu ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_pointer_validation_function ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_ips ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_md ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(test_ipd ${CMAKE_CURRENT_BINARY_DIR}/lab4)
add_test(test_ipu ${CMAKE_CURRENT_BINARY_DIR}/lab4)
add_test(test_pointer_validation_function ${CMAKE_CURRENT_BINARY_DIR}/lab4)
add_test(test_ips ${CMAKE_CURRENT_BINARY_DIR}/lab4)
add_test(test_md ${CMAKE_CURRENT_BINARY_DIR}/lab4)
