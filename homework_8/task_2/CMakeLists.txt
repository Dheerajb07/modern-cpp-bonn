cmake_minimum_required(VERSION 3.10)
project(homework_8_task_2)

# CPP standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXPORT_COMPILE_COMMANDS ON)

# Define an option to enable/disable tests
option(BUILD_TESTS "Build the tests" OFF)

# set output diretories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# include clang-tidy and static analyzer
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ClangFormat StaticAnalyzers)

# include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# compile Image library
add_library(image ${PROJECT_SOURCE_DIR}/src/image.cpp ${PROJECT_SOURCE_DIR}/include/image.hpp)

if(BUILD_TESTS)
    # compile tests
    add_subdirectory(tests)
endif()