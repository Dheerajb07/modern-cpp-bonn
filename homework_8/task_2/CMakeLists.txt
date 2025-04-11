cmake_minimum_required(VERSION 3.10)
project(homework_8_task_2)

# CPP standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXPORT_COMPILE_COMMANDS ON)

## find external dependencies
# libpng++ package
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})

# Define an option to enable/disable tests
option(BUILD_TESTS "Build the tests" OFF)

# set output diretories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)



# include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# compile strategy library
add_library(strategies 
            ${PROJECT_SOURCE_DIR}/src/io_strategy.cpp ${PROJECT_SOURCE_DIR}/include/io_strategy.hpp 
            ${PROJECT_SOURCE_DIR}/src/string_utils.cpp ${PROJECT_SOURCE_DIR}/include/string_utils.hpp
            )
target_link_libraries(strategies PNG::PNG)

# compile image library
add_library(image ${PROJECT_SOURCE_DIR}/src/image.cpp ${PROJECT_SOURCE_DIR}/include/image.hpp)
target_link_libraries(image strategies)

# Compile dev files
# add_subdirectory(dev/)

## TESTING
# include clang-tidy and static analyzer
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ClangFormat StaticAnalyzers)

# Compile Tests
add_subdirectory(tests)
