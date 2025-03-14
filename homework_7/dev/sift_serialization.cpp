#include "homework_7.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // set dataset path
  std::filesystem::path images_dir_path = "data/freiburg/images";
  std::filesystem::path bin_dir_path = "data/freiburg/bin";

  // dataset serialization
  std::cout << "Serializing Dataset ..." << std::endl;

  ipb::serialization::sifts::ConvertDataset(images_dir_path);

  std::cout << "Serialization Complete!" << std::endl << std::endl;

  // test deserialization
  std::cout << "Deserializing Dataset ..." << std::endl;
  std::vector<cv::Mat> dataset =
      ipb::serialization::sifts::LoadDataset(bin_dir_path);

  std::cout << "Loaded Dataset : " << dataset.size() << " files" << std::endl;

  std::cout << "Deserialization Complete!" << std::endl;

  return 0;
}