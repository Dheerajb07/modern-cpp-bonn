cmake_minimum_required(VERSION 3.10)
project(homework_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(trial ${PROJECT_SOURCE_DIR}/src/trial.cpp)
target_include_directories(trial PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/tests)