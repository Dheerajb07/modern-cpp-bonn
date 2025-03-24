# compile dev programs
# add_executable(sift_serialization ${PROJECT_SOURCE_DIR}/dev/sift_serialization.cpp)
# target_link_libraries(sift_serialization convert_dataset)

# add_executable(kmeans_dev ${PROJECT_SOURCE_DIR}/dev/kmeans_dev.cpp)
# target_link_libraries(kmeans_dev ${OpenCV_LIBS})

add_executable(kmeans_testing ${PROJECT_SOURCE_DIR}/dev/kmeans_testing.cpp)
target_link_libraries(kmeans_testing kmeans)

# add_executable(kmeans_opencv ${PROJECT_SOURCE_DIR}/dev/kmeans_opencv.cpp)
# target_link_libraries(kmeans_opencv ${OpenCV_LIBS})