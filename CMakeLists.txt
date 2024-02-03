cmake_minimum_required(VERSION 3.10)
project(CPP2_s21_containers.ID_353534-Team_TL_senellev.19e781b8_9135_4be5-1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Coverage;Sanitizer" CACHE STRING "" FORCE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g")
set(CMAKE_CXX_FLAGS_COVERAGE "--coverage -fprofile-arcs -ftest-coverage -g" CACHE STRING "Coverage flags" FORCE)
set(CMAKE_CXX_FLAGS_SANITIZER "-fsanitize=address -fno-omit-frame-pointer -g" CACHE STRING "Sanitizer flags" FORCE)


add_subdirectory(src/lib)
