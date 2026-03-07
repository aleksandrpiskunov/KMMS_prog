

cmake_minimum_required(VERSION 3.10)


project(obuchaika)


add_executable(menu
    menu.cpp
    menu_func.cpp
    menu_items.cpp
)


target_include_directories(menu PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


install(TARGETS menu RUNTIME DESTINATION bin)
