cmake_minimum_required(VERSION 3.10)

project(tree_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(s21_tree INTERFACE s21_tree.h)
target_include_directories(s21_tree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})






add_executable(test_s21_tree unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_tree PRIVATE s21_tree gtest)

add_custom_target(test_tree_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_tree
        COMMAND $<TARGET_FILE:test_s21_tree>
        COMMENT "Building and running s21_tree unit tests"
)

add_custom_target(test_tree_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_tree
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_tree> > /dev/null
        COMMENT "Running s21_tree tests with Valgrind"
)

add_custom_target(test_tree_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_tree
        COMMAND $<TARGET_FILE:test_s21_tree>
        COMMENT "Running s21_tree tests with AddressSanitizer"
)

add_custom_target(test_tree_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_tree
        COMMAND $<TARGET_FILE:test_s21_tree> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o tree_coverage_report.html
        COMMAND xdg-open tree_coverage_report.html 2>/dev/null || open tree_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_tree"
)

add_custom_target(test_tree_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_tree"
)

