cmake_minimum_required(VERSION 3.10)

project(vector_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(s21_vector INTERFACE s21_vector.h)
set_target_properties(s21_vector PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(s21_vector INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})




add_executable(test_s21_vector unit_tests/tests.cpp
        ../testing_include/test_include.h)
target_link_libraries(test_s21_vector PRIVATE s21_vector gtest)

add_custom_target(test_vector_units
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_vector
        COMMAND $<TARGET_FILE:test_s21_vector>
        COMMENT "Building and running s21_vector unit tests"
)

add_custom_target(test_vector_valgrind
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_vector
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
        $<TARGET_FILE:test_s21_vector> > /dev/null
        COMMENT "Running s21_vector tests with Valgrind"
)

add_custom_target(test_vector_sanitizer
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Sanitizer ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_vector
        COMMAND $<TARGET_FILE:test_s21_vector>
        COMMENT "Running s21_vector tests with AddressSanitizer"
)

add_custom_target(test_vector_coverage
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Coverage ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_s21_vector
        COMMAND $<TARGET_FILE:test_s21_vector> > /dev/null
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --exclude-unreachable-branches --exclude-throw-branches --html --html-details -o vector_coverage_report.html
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --exclude-unreachable-branches --exclude-throw-branches --print-summary
        COMMAND xdg-open vector_coverage_report.html 2>/dev/null || open vector_coverage_report.html 2>/dev/null
        COMMENT "Generating coverage report for s21_vector"
)


add_custom_target(test_vector_cppcheck
        COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck on s21_vector"
)

