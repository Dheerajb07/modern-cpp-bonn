# compile executalble

add_executable(image_trial ${PROJECT_SOURCE_DIR}/dev/image_trial.cpp)
target_link_libraries(image_trial image ${OpenCV_LIBS})

add_executable(histogram_trial ${PROJECT_SOURCE_DIR}/dev/histogram_trial.cpp)
target_link_libraries(histogram_trial image)
