cmake_minimum_required(VERSION 3.10)
project(homework_5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXPORT_COMPILE_COMMANDS ON)

# set output params
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# include opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

## COMPILE libraries
# mat_serialization library
add_library(mat_serialization ${PROJECT_SOURCE_DIR}/include/serialize.hpp ${PROJECT_SOURCE_DIR}/src/serialize.cpp)
target_link_libraries(mat_serialization ${OpenCV_LIBS})

# convert_dataset library
add_library(convert_dataset ${PROJECT_SOURCE_DIR}/include/convert_dataset.hpp ${PROJECT_SOURCE_DIR}/src/convert_dataset.cpp)
target_link_libraries(convert_dataset mat_serialization ${OpenCV_LIBS})

## COMPILE examples
add_subdirectory(dev/)

## COMPILE tests
add_subdirectory(tests/)
