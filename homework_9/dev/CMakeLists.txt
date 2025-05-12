## COMPILE DEV PROGRAMS
add_executable(histogram_trial
               histogram_trial.cpp)
            #    test_data.cpp)
# target_link_libraries(histogram_trial PRIVATE histogram PRIVATE bow_dictionary PRIVATE ${OpenCV_LIBS})
target_link_libraries(histogram_trial histogram bow_dictionary ${OpenCV_LIBS})