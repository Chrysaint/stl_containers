cmake_minimum_required(VERSION 3.10)

project(stack_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(s21_stack INTERFACE s21_stack.h)

target_include_directories(s21_stack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})






add_executable(test_s21_stack unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_stack PRIVATE s21_stack gtest)

add_custom_target(test_stack_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_stack
        COMMAND $<TARGET_FILE:test_s21_stack>
        COMMENT "Building and running s21_stack unit tests"
)

add_custom_target(test_stack_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_stack
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_stack> > /dev/null
        COMMENT "Running s21_stack tests with Valgrind"
)

add_custom_target(test_stack_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_stack
        COMMAND $<TARGET_FILE:test_s21_stack>
        COMMENT "Running s21_stack tests with AddressSanitizer"
)

add_custom_target(test_stack_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_stack
        COMMAND $<TARGET_FILE:test_s21_stack> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o stack_coverage_report.html
        COMMAND xdg-open stack_coverage_report.html 2>/dev/null || open stack_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_stack"
)

add_custom_target(test_stack_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_stack"
)


