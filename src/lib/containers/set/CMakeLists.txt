cmake_minimum_required(VERSION 3.10)

project(set_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(s21_set INTERFACE s21_set.h)

target_include_directories(s21_set INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})








add_executable(test_s21_set unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_set PRIVATE s21_set gtest)

add_custom_target(test_set_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_set
        COMMAND $<TARGET_FILE:test_s21_set>
        COMMENT "Building and running s21_set unit tests"
)

add_custom_target(test_set_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_set
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_set> > /dev/null
        COMMENT "Running s21_set tests with Valgrind"
)

add_custom_target(test_set_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_set
        COMMAND $<TARGET_FILE:test_s21_set>
        COMMENT "Running s21_set tests with AddressSanitizer"
)

add_custom_target(test_set_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_set
        COMMAND $<TARGET_FILE:test_s21_set> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o set_coverage_report.html
        COMMAND xdg-open set_coverage_report.html 2>/dev/null || open set_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_set"
)

add_custom_target(test_set_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_set"
)

