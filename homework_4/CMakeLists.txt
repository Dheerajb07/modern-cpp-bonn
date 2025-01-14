cmake_minimum_required(VERSION 3.10)
project(homework_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(ipb_algorithm ${PROJECT_SOURCE_DIR}/src/ipb_algorithm.cpp ${PROJECT_SOURCE_DIR}/include/homework_4.h)
target_include_directories(ipb_algorithm PRIVATE ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(example ${PROJECT_SOURCE_DIR}/src/example.cpp)
target_include_directories(example PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(example ipb_algorithm)

add_subdirectory(${PROJECT_SOURCE_DIR}/tests)