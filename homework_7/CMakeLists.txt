cmake_minimum_required(VERSION 3.10)
project(homework_7)

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
# serialization lib
add_library(serialization 
            ${PROJECT_SOURCE_DIR}/src/serialize.cpp ${PROJECT_SOURCE_DIR}/include/serialize.hpp 
            ${PROJECT_SOURCE_DIR}/src/convert_dataset.cpp ${PROJECT_SOURCE_DIR}/include/convert_dataset.hpp)

target_link_libraries(serialization ${OpenCV_LIBS})

# kmeans lib
add_library(kmeans ${PROJECT_SOURCE_DIR}/src/kmeans_opencv.cpp ${PROJECT_SOURCE_DIR}/include/kmeans.hpp)
target_link_libraries(kmeans ${OpenCV_LIBS})

# bow_dictionary lib
add_library(bow_dictionary ${PROJECT_SOURCE_DIR}/src/bow_dictionary.cpp ${PROJECT_SOURCE_DIR}/include/bow_dictionary.hpp)
target_link_libraries(bow_dictionary kmeans ${OpenCV_LIBS})

## COMPILE DEV PROGRAMS
add_subdirectory(dev/)

## COMPILE TESTS
add_subdirectory(tests/)