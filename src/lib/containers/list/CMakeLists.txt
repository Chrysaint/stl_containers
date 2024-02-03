cmake_minimum_required(VERSION 3.10)

project(list_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(s21_list INTERFACE s21_list.h)

target_include_directories(s21_list INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})






add_executable(test_s21_list unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_list PRIVATE s21_list gtest)

add_custom_target(test_list_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_list
        COMMAND $<TARGET_FILE:test_s21_list>
        COMMENT "Building and running s21_list unit tests"
)

add_custom_target(test_list_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_list
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_list> > /dev/null
        COMMENT "Running s21_list tests with Valgrind"
)

add_custom_target(test_list_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_list
        COMMAND $<TARGET_FILE:test_s21_list>
        COMMENT "Running s21_list tests with AddressSanitizer"
)

add_custom_target(test_list_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_list
        COMMAND $<TARGET_FILE:test_s21_list> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o list_coverage_report.html
        COMMAND xdg-open list_coverage_report.html 2>/dev/null || open list_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_list"
)

add_custom_target(test_list_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_list"
)

