#include "homework_7.h"
#include <filesystem>
#include <iostream>
#include <opencv2/core.hpp>
#include <vector>

int main() {
  // set dataset path
  std::filesystem::path bin_dir_path = "data/freiburg/bin";

  // Load dataset : deserialize bin files
  std::cout << "Loading Dataset ..." << std::endl;
  const std::vector<cv::Mat> dataset =
      ipb::serialization::sifts::LoadDataset(bin_dir_path);
  std::cout << "Loaded Dataset : " << dataset.size() << " files" << std::endl;
  std::cout << std::endl;

  // K-Means
  int k = 5;
  int max_iter = 100;
  cv::Mat centroids = ipb::kMeans(dataset, k, max_iter);

  return 0;
}