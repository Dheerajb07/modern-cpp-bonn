#include "convert_dataset.hpp"
#include "serialize.hpp"
#include <filesystem>
#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace ipb::serialization::sifts {
void ConvertDataset(const std::filesystem::path &data_path) {
  // get bin dir path
  std::filesystem::path bin_dir_path = data_path.parent_path() / "bin";

  // create bin dir if not exists
  if (!std::filesystem::exists(bin_dir_path)) {
    std::filesystem::create_directory(bin_dir_path);
  }

  // keypoint detector init
  auto detector = cv::SiftFeatureDetector::create();
  // SIFT descriptor extractor init
  auto extractor = cv::SiftDescriptorExtractor::create();

  // init variables
  std::filesystem::path bin_filepath;
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat img;
  cv::Mat sift_descriptor;

  // loop over directory to find images
  for (auto &image : std::filesystem::directory_iterator(data_path)) {

    // check file extension
    if (image.path().extension() == ".png") {
      // print out image path
      std::cout << "Found image : " << image.path() << std::endl;

      // read image
      img = cv::imread(image.path(), cv::IMREAD_GRAYSCALE);

      // detect keypoints
      detector->detect(img, keypoints);

      // extract sift descriptors
      extractor->compute(img, keypoints, sift_descriptor);

      // get bin file path
      bin_filepath = bin_dir_path / (image.path().stem().string() + ".bin");

      // serialize sift descriptor to bin file
      ipb::serialization::Serialize(sift_descriptor, bin_filepath);

      std::cout << "SIFT descriptors written to : " << bin_filepath
                << std::endl;
    }
  }
}

std::vector<cv::Mat> LoadDataset(const std::filesystem::path &bin_path) {
  // init vector to store mat data read from bin files
  std::vector<cv::Mat> data;

  // init matrix
  cv::Mat matrix;

  // loop through directory to fin bin files
  for (auto &bin_file : std::filesystem::directory_iterator(bin_path)) {
    // check file extension
    if (bin_file.path().extension() == ".bin") {
      // print out bin path
      std::cout << "Found bin file : " << bin_file.path() << std::endl;

      // deserialize bin file to mat
      matrix = ipb::serialization::Deserialize(bin_file.path());

      // add mat to vector
      data.push_back(matrix);
    }
  }
  return data;
}
} // namespace ipb::serialization::sifts