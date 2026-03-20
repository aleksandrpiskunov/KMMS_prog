# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.10)
# Включить поддержку тестирования (CTest)
enable_testing()
# Имя и версия подпроекта тестов
project(tests)

# Создать исполняемый файл test_bubble из test_bubble.cpp
add_executable(test_bubble test_bubble.cpp)
# Указать директорию с заголовочными файлами для test_bubble
target_include_directories(test_bubble PRIVATE ${CMAKE_SOURCE_DIR}/projects/sort/src)
# Подключить к test_bubble библиотеку сортировки и GoogleTest
target_link_libraries(test_bubble PRIVATE 
    ${SORTING_LIB_NAME}
    GTest::gtest
    GTest::gtest_main)

# Зарегистрировать тест для автоматического запуска через CTest
add_test(NAME bubble_test COMMAND test_bubble)
