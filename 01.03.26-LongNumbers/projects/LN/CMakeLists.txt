
cmake_minimum_required(VERSION 3.10)

project(LN)

add_subdirectory(test)

add_library(${LN_LIB_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LongNumber.cpp
)


target_sources(${LN_LIB_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LongNumber.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LongNumbers.hpp
)

target_include_directories(${LN_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

