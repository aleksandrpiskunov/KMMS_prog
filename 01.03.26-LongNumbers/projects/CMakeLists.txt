set(CMAKE_MACOSX_RPATH ON)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)


cmake_minimum_required(VERSION 3.10)


enable_testing()


project(projects)




set(LN_LIB_NAME LNlib)


add_subdirectory(obuchaika)


add_subdirectory(LN)

add_subdirectory(lib/googletest)

