cmake_minimum_required(VERSION 3.10)

project(map_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(s21_map INTERFACE s21_map.h)

target_include_directories(s21_map INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})







add_executable(test_s21_map unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_map PRIVATE s21_map gtest)

add_custom_target(test_map_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_map
        COMMAND $<TARGET_FILE:test_s21_map>
        COMMENT "Building and running s21_map unit tests"
)

add_custom_target(test_map_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_map
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_map> > /dev/null
        COMMENT "Running s21_map tests with Valgrind"
)

add_custom_target(test_map_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_map
        COMMAND $<TARGET_FILE:test_s21_map>
        COMMENT "Running s21_map tests with AddressSanitizer"
)

add_custom_target(test_map_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_map
        COMMAND $<TARGET_FILE:test_s21_map> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o map_coverage_report.html
        COMMAND xdg-open map_coverage_report.html 2>/dev/null || open map_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_map"
)

add_custom_target(test_map_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_map"
)

