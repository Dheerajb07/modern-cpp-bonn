#include "homework_5.h"
#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>

void print_properties(cv::Mat &img) {
  std::cout << "Rows: " << img.rows << std::endl;
  std::cout << "Columns: " << img.cols << std::endl;
  std::cout << "Channels: " << img.channels() << std::endl;
  std::cout << "Type: " << img.type() << std::endl;
}

void display_image(cv::Mat &img, const std::string &window_name) {
  cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
  cv::imshow(window_name, img);
}

int main() {
  // get current path
  std::filesystem::path imgPath =
      std::filesystem::current_path() / "data/lenna.png";
  // std::cout << imgPath << std::endl;

  // Read image
  cv::Mat img = cv::imread(imgPath, cv::IMREAD_GRAYSCALE);

  // return error if image not found
  if (!img.data) {
    std::cerr << "No Image data" << std::endl;
    return 1;
  }

  // print image properties
  print_properties(img);
  // std::cout << (int)img.at<unsigned char>(0,0,0) << std::endl;

  // serialize img
  ipb::serialization::Serialize(img, std::filesystem::current_path() /
                                         "data/lenna.bin");
  std::cout << "Serialized image" << std::endl;

  // deserialize image
  cv::Mat deserial_img = ipb::serialization::Deserialize(
      std::filesystem::current_path() / "data/lenna.bin");
  std::cout << "Deserialized image" << std::endl;

  // display original image
  display_image(img, "Original Image");

  // display deserialzed image
  display_image(deserial_img, "Deserialized Image");

  // wait to close windows
  cv::waitKey(0);

  return 0;
}