cmake_minimum_required(VERSION 3.10)
project(web_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Compile Libraries
# set library output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# add library: html_writer
add_library(html_writer src/html_writer.cpp api/html_writer.hpp)
target_include_directories(html_writer PUBLIC api/)
# add library: image_browser
add_library(image_browser src/image_browser.cpp api/image_browser.hpp)
target_include_directories(image_browser PUBLIC api/)
target_link_libraries(image_browser html_writer)

## Compile executables
# set executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# compile test_hml_writer.cpp
add_executable(test_html_writer src/test_html_writer.cpp)
target_link_libraries(test_html_writer html_writer)
# compile test_image_browser.cpp
add_executable(test_image_browser src/test_image_browser.cpp)
target_link_libraries(test_image_browser image_browser)
