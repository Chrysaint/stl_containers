cmake_minimum_required(VERSION 3.10)

project(queue_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(s21_queue INTERFACE s21_queue.h)

target_include_directories(s21_queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})







add_executable(test_s21_queue unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_queue PRIVATE s21_queue gtest)

add_custom_target(test_queue_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_queue
        COMMAND $<TARGET_FILE:test_s21_queue>
        COMMENT "Building and running s21_queue unit tests"
)

add_custom_target(test_queue_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_queue
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_queue> > /dev/null
        COMMENT "Running s21_queue tests with Valgrind"
)

add_custom_target(test_queue_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_queue
        COMMAND $<TARGET_FILE:test_s21_queue>
        COMMENT "Running s21_queue tests with AddressSanitizer"
)

add_custom_target(test_queue_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_queue
        COMMAND $<TARGET_FILE:test_s21_queue> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o queue_coverage_report.html
        COMMAND xdg-open queue_coverage_report.html 2>/dev/null || open queue_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_queue"
)

add_custom_target(test_queue_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_queue"
)

