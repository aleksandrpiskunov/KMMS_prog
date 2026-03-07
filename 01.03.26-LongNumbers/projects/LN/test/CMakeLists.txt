
cmake_minimum_required(VERSION 3.10)


enable_testing()

project(tests)

add_executable(test_LN test_LN.cpp)

target_include_directories(test_LN PRIVATE ${CMAKE_SOURCE_DIR}/LN/src)


target_link_libraries(test_LN PRIVATE 
    ${LN_LIB_NAME}
    gtest
    gtest_main)

add_test(NAME LN_test COMMAND test_LN)
