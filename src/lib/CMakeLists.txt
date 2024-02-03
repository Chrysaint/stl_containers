cmake_minimum_required(VERSION 3.10)

project(containers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(containers/array)
add_subdirectory(containers/list)
add_subdirectory(containers/map)
add_subdirectory(containers/multiset)
add_subdirectory(containers/queue)
add_subdirectory(containers/set)
add_subdirectory(containers/stack)
add_subdirectory(containers/vector)
add_subdirectory(containers/tree)

add_library(s21_containers INTERFACE s21_containers.h)
target_link_libraries(s21_containers
        INTERFACE
        s21_list
        s21_map
        s21_queue
        s21_set
        s21_stack
        s21_vector
)

add_library(s21_containersplus INTERFACE s21_containersplus.h)
target_link_libraries(s21_containersplus
        INTERFACE
        s21_array
        s21_multiset
)

target_include_directories(s21_containers INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/containers
)

add_custom_target(test_units
        DEPENDS test_array_units test_list_units test_map_units test_multiset_units test_queue_units test_set_units test_stack_units test_vector_units test_tree_units
        COMMENT "Running all unit tests"
)

add_custom_target(test_valgrind
        DEPENDS test_array_valgrind test_list_valgrind test_map_valgrind test_multiset_valgrind test_queue_valgrind test_set_valgrind test_stack_valgrind test_vector_valgrind test_tree_valgrind
        COMMENT "Running all tests with Valgrind"
)

add_custom_target(test_sanitizer
        DEPENDS test_vector_sanitizer test_list_sanitizer test_map_sanitizer
        DEPENDS test_array_sanitizer test_list_sanitizer test_map_sanitizer test_multiset_sanitizer test_queue_sanitizer test_set_sanitizer test_stack_sanitizer test_vector_sanitizer test_tree_sanitizer
        COMMENT "Running all tests with Sanitizer"
)

add_custom_target(test_coverage
        DEPENDS test_vector_coverage test_list_coverage test_map_coverage
        DEPENDS test_array_coverage test_list_coverage test_map_coverage test_multiset_coverage test_queue_coverage test_set_coverage test_stack_coverage test_vector_coverage test_tree_coverage
        COMMENT "Running all coverage reports"
)

add_custom_target(test_cppcheck
        DEPENDS test_vector_cppcheck test_list_cppcheck test_map_cppcheck
        DEPENDS test_array_cppcheck test_list_cppcheck test_map_cppcheck test_multiset_cppcheck test_queue_cppcheck test_set_cppcheck test_stack_cppcheck test_vector_cppcheck test_tree_cppcheck
        COMMENT "Running cppcheck on all containers"
)

add_custom_target(test
        DEPENDS test_units test_valgrind test_sanitizer test_coverage test_cppcheck
        COMMENT "Running all test suites sequentially"
)


set(TEST_EXECUTABLES
        test_s21_array
        test_s21_list
        test_s21_map
        test_s21_multiset
        test_s21_queue
        test_s21_set
        test_s21_stack
        test_s21_vector
        test_s21_tree
)


function(add_leak_check_target exe)
    if(APPLE)
        add_custom_command(
                OUTPUT ${exe}_leaks
                COMMAND leaks -atExit -- $<TARGET_FILE:${exe}> | grep LEAK:
                COMMENT "Running leaks on ${exe}"
                DEPENDS ${exe}
        )
    elseif(UNIX)
        add_custom_command(
                OUTPUT ${exe}_leaks
                COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $<TARGET_FILE:${exe}> > /dev/null
                COMMENT "Running valgrind on ${exe}"
                DEPENDS ${exe}
        )
    endif()
    add_custom_target(${exe}_leaks_run DEPENDS ${exe}_leaks)
endfunction()

foreach(test_exe IN LISTS TEST_EXECUTABLES)
    add_leak_check_target(${test_exe})
endforeach()

add_custom_target(test_leaks
        DEPENDS
        test_s21_array_leaks_run
        test_s21_list_leaks_run
        test_s21_map_leaks_run
        test_s21_multiset_leaks_run
        test_s21_queue_leaks_run
        test_s21_set_leaks_run
        test_s21_stack_leaks_run
        test_s21_vector_leaks_run
        test_s21_tree_leaks_run
        COMMENT "Running all leak checks (Valgrind on Linux, leaks on macOS)"
)
