# compile executalble

add_executable(image_trial ${PROJECT_SOURCE_DIR}/dev/image_trial.cpp)
target_link_libraries(image_trial image ${OpenCV_LIBS})

add_executable(histogram_trial ${PROJECT_SOURCE_DIR}/dev/histogram_trial.cpp)
target_link_libraries(histogram_trial image)

add_executable(scaling_trial ${PROJECT_SOURCE_DIR}/dev/scaling_trial.cpp)
target_link_libraries(scaling_trial image ${OpenCV_LIBS})