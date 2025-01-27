## COMPILE EXECUTABLES
# serial trial
add_executable(serial_trial ${PROJECT_SOURCE_DIR}/dev/serial_trial.cpp)
target_link_libraries(serial_trial mat_serialization convert_dataset ${OpenCV_LIBS})

# dataset trial
add_executable(dataset_trial ${PROJECT_SOURCE_DIR}/dev/dataset_trial.cpp)
target_link_libraries(dataset_trial mat_serialization convert_dataset ${OpenCV_LIBS})