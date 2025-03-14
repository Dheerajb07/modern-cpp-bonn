# compile dev programs
add_executable(sift_serialization ${PROJECT_SOURCE_DIR}/dev/sift_serialization.cpp)
target_link_libraries(sift_serialization convert_dataset)