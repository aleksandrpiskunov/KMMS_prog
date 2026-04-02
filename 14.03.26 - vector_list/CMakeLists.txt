cmake_minimum_required(VERSION 4.2)
project(containers)
include(FetchContent)
include(CTest)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

set(CONTAINERS_LIB "containers_lib")
add_library(${CONTAINERS_LIB} "")

add_subdirectory(src)
add_subdirectory(test)
