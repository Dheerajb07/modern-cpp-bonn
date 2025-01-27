#include "homework_5.h"
#include <filesystem>
#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

void display_image(cv::Mat &img, const std::string &window_name) {
  cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
  cv::imshow(window_name, img);
}

void print_properties(cv::Mat &img) {
  std::cout << "Rows: " << img.rows << std::endl;
  std::cout << "Columns: " << img.cols << std::endl;
  std::cout << "Channels: " << img.channels() << std::endl;
  std::cout << "Type: " << img.type() << std::endl;
}

int main() {
  // set dataset path
  std::filesystem::path images_dir_path = "data/freiburg/images";
  std::filesystem::path bin_dir_path = "data/freiburg/bin";
//   std::filesystem::create_directory(bin_dir_path);

  /* 
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
  for (auto &image : std::filesystem::directory_iterator(images_dir_path)) {
    // check file extension
    if (image.path().extension() == ".png") {
      // print out path
      std::cout << image.path() << std::endl;
      // read image
      img = cv::imread(image.path(), cv::IMREAD_COLOR);
      //   display_image(img, image.path().filename());
      //   cv::waitKey(0);

      // detect keypoints
      detector->detect(img, keypoints);
      cv::drawKeypoints(img, keypoints, img_with_keypoints);
      //   display_image(img_with_keypoints, image.path().filename());
      //   cv::waitKey(0);

      // extract sift descriptors
      extractor->compute(img, keypoints, sift_descriptor);
      //   display_image(sift_descriptor, image.path().filename());
      //   cv::waitKey(0);
      print_properties(sift_descriptor);
      // serialize the descriptor
      bin_filepath = bin_dir_path / (image.path().stem().string() + ".bin");
      std::cout << bin_filepath << std::endl;
      ipb::serialization::Serialize(sift_descriptor, bin_filepath);
    }
  }
  */

    // test serialization
    std::cout << "********TESTING DATA SERIALIZATION**********" << std::endl;
    
    ipb::serialization::sifts::ConvertDataset(images_dir_path);
    
    std::cout << "**********SERIALIZATION COMPLETE************" << std::endl << std::endl;
    
    // test deserialization
    std::cout << "**********TESTING DATA DESERIALIZATION**********" << std::endl;
    std::vector<cv::Mat> dataset = ipb::serialization::sifts::LoadDataset(bin_dir_path);

    std::cout << "Loaded Dataset : " << dataset.size() << " files" << std::endl;

    std::cout << "************DESERIALIZATION COMPLETE************" << std::endl << std::endl;

    return 0;
}