cmake_minimum_required(VERSION 3.10)
project(homework_5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(trial ${PROJECT_SOURCE_DIR}/src/trial.cpp)
target_link_libraries(trial ${OpenCV_LIBS})
