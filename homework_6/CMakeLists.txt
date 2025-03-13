cmake_minimum_required(VERSION 3.10)
project(homework_6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXPORT_COMPILE_COMMANDS ON)

# include clang-tidy and static analyzer
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(StaticAnalyzers)
include(ClangFormat)

# set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# ext libs/packages
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# compile io_tools lib
add_library(io_tools ${PROJECT_SOURCE_DIR}/include/io_tools/io_tools.hpp ${PROJECT_SOURCE_DIR}/include/io_tools/io_tools.cpp)

# compile image lib
add_library(image ${PROJECT_SOURCE_DIR}/include/image.hpp ${PROJECT_SOURCE_DIR}/include/image.cpp)
target_link_libraries(image io_tools)

# compile executables
add_subdirectory(dev/)

# compile tests
add_subdirectory(tests/)