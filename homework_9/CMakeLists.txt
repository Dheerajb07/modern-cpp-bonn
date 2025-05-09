cmake_minimum_required(VERSION 3.10)
project(homework_9)

# CXX standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXPORT_COMPILE_COMMANDS ON)

# set clang-format and static-analyzer : clang-tidy,cppcheck
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ClangFormat StaticAnalyzers)

# set output params
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# include opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# include dir
include_directories(${PROJECT_SOURCE_DIR}/include)

## COMPILE LIBRARIES
# kmeans lib
add_library(kmeans ${PROJECT_SOURCE_DIR}/src/kmeans.cpp ${PROJECT_SOURCE_DIR}/include/kmeans.hpp)
target_link_libraries(kmeans PRIVATE ${OpenCV_LIBS})

# bow_dictionary lib
add_library(bow_dictionary ${PROJECT_SOURCE_DIR}/src/bow_dictionary.cpp ${PROJECT_SOURCE_DIR}/include/bow_dictionary.hpp)
target_link_libraries(bow_dictionary PRIVATE kmeans PRIVATE ${OpenCV_LIBS})

# histogram lib
add_library(histogram STATIC
            ${PROJECT_SOURCE_DIR}/src/histogram_utils.cpp ${PROJECT_SOURCE_DIR}/include/histogram_utils.hpp            
            ${PROJECT_SOURCE_DIR}/src/histogram.cpp ${PROJECT_SOURCE_DIR}/include/histogram.hpp   
            )
target_link_libraries(histogram PRIVATE bow_dictionary PRIVATE ${OpenCV_LIBS})

## COMPILE DEV PROGRAMS
# add_subdirectory(dev/)

## COMPILE TESTS
add_subdirectory(tests/)