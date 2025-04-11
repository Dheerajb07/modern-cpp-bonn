# read ppm image dev
# add_executable(read_ppm_dev ${PROJECT_SOURCE_DIR}/dev/read_ppm_dev.cpp)

# image io strategy dev
add_executable(img_iostrat_dev ${PROJECT_SOURCE_DIR}/dev/img_iostrat_dev.cpp)
target_link_libraries(img_iostrat_dev image)