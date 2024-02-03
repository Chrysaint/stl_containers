cmake_minimum_required(VERSION 3.10)

project(array_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(s21_array INTERFACE s21_array.h)

target_include_directories(s21_array INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})






add_executable(test_s21_array unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_array PRIVATE s21_array gtest)

add_custom_target(test_array_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_array
        COMMAND $<TARGET_FILE:test_s21_array>
        COMMENT "Building and running s21_array unit tests"
)

add_custom_target(test_array_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_array
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_array> > /dev/null
        COMMENT "Running s21_array tests with Valgrind"
)

add_custom_target(test_array_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_array
        COMMAND $<TARGET_FILE:test_s21_array>
        COMMENT "Running s21_array tests with AddressSanitizer"
)

add_custom_target(test_array_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_array
        COMMAND $<TARGET_FILE:test_s21_array> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o array_coverage_report.html
        COMMAND xdg-open array_coverage_report.html 2>/dev/null || open array_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_array"
)

add_custom_target(test_array_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_array"
)

