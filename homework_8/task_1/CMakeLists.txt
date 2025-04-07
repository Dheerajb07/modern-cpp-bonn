cmake_minimum_required(VERSION 3.10)
project(homework_8_task_1)

# CXX standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXPORT_COMPILE_COMMANDS ON)

# set clang-format and static-analyzer : clang-tidy,cppcheck
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ClangFormat StaticAnalyzers)

# binaries output directory after build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# compile executable
add_executable(stack_limit ${PROJECT_SOURCE_DIR}/src/stack_limit.cpp)
