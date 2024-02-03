cmake_minimum_required(VERSION 3.10)

project(multiset_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(s21_multiset INTERFACE s21_multiset.h)

target_include_directories(s21_multiset INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})






add_executable(test_s21_multiset unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_multiset PRIVATE s21_multiset gtest)

add_custom_target(test_multiset_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_multiset
        COMMAND $<TARGET_FILE:test_s21_multiset>
        COMMENT "Building and running s21_multiset unit tests"
)

add_custom_target(test_multiset_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_multiset
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_multiset> > /dev/null
        COMMENT "Running s21_multiset tests with Valgrind"
)

add_custom_target(test_multiset_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_multiset
        COMMAND $<TARGET_FILE:test_s21_multiset>
        COMMENT "Running s21_multiset tests with AddressSanitizer"
)

add_custom_target(test_multiset_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_multiset
        COMMAND $<TARGET_FILE:test_s21_multiset> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o multiset_coverage_report.html
        COMMAND xdg-open multiset_coverage_report.html 2>/dev/null || open multiset_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_multiset"
)

add_custom_target(test_multiset_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_multiset"
)

