#include "homework_5.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

int main(){
    // set dataset path
    std::filesystem::path dataset_dir_path = std::filesystem::current_path() / "data/freiburg";
    std::filesystem::path images_dir_path = dataset_dir_path / "images";
    std::filesystem::path bin_dir_path = dataset_dir_path / "bin";

    // keypoint detector init
    auto detector = cv::SiftFeatureDetector::create();
    // SIFT descriptor extractor init
    auto extractor = cv::SiftDescriptorExtractor::create();

    // init variables
    std::filesystem::path bin_filepath;
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat img;
    cv::Mat img_with_keypoints;
    cv::Mat sift_descriptor;

    // loop over directory to find images
    for(auto &image: std::filesystem::directory_iterator(images_dir_path)){
        // check file extension
        if (image.path().extension() == ".png"){
            // print out path
            std::cout << image.path() << std::endl;
            // read image
            img = cv::imread(image.path(), cv::IMREAD_COLOR);
            // detect keypoints
            detector->detect(img,keypoints);
            // extract sift descriptors
            extractor->compute(img,keypoints,sift_descriptor);

            // serialize the descriptor
            bin_filepath = bin_dir_path / image.path().stem() / ".bin";
            ipb::serialization::Serialize(sift_descriptor, bin_filepath);
        }
    }
}