#include "serialize.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <string>
#include <vector>

namespace ipb::serialization {

void Serialize(const cv::Mat &img, const std::string &filename) {
  std::ofstream bin_file(filename, std::ios_base::out | std::ios_base::binary |
                                       std::ios_base::trunc);

  // vector to store image info
  std::vector<int> img_info = {img.rows, img.cols, img.type()};
  // write info into to the beginning of binary file
  bin_file.write(reinterpret_cast<char *>(&img_info.front()),
                 img_info.size() * sizeof(int));

  // check mat type
  // type == CV_8UC3 == 16 == RGB Image
  // type == CV_32FC1 == 5  == SIFT Descriptor
  if (img.type() == CV_8UC3) {
    cv::Vec3b pixel;
    for (int i = 0; i < img.rows; i++) {
      for (int j = 0; j < img.cols; j++) {
        pixel = img.at<cv::Vec3b>(i, j);
        bin_file.write(reinterpret_cast<char *>(&pixel), sizeof(cv::Vec3b));
      }
    }
  } else if (img.type() == CV_32FC1) {
    float val;
    for (int i = 0; i < img.rows; i++) {
      for (int j = 0; j < img.cols; j++) {
        val = img.at<float>(i, j);
        bin_file.write(reinterpret_cast<char *>(&val), sizeof(float));
      }
    }
  }
}

cv::Mat Deserialize(const std::string &filename) {
  std::ifstream bin_file(filename, std::ios_base::in | std::ios_base::binary);

  // read info vector
  std::vector<int> img_info = {0, 0, 0};
  bin_file.read(reinterpret_cast<char *>(&img_info.front()),
                img_info.size() * sizeof(int));
  cv::Mat img = cv::Mat::zeros(img_info[0], img_info[1], img_info[2]);

  // check mat type
  // type == 16 == CV_8UC3 == RGB Image
  // type == 5  == CV_32FC1 == SIFT Descriptor
  if (img_info[2] == CV_8UC3) {
    cv::Vec3b pixel;
    for (int i = 0; i < img_info[0]; i++) {
      for (int j = 0; j < img_info[1]; j++) {
        bin_file.read(reinterpret_cast<char *>(&pixel), sizeof(cv::Vec3b));
        img.at<cv::Vec3b>(i, j) = pixel;
      }
    }
  } else if (img_info[2] == CV_32FC1) {
    cv::Mat img = cv::Mat::zeros(img_info[0], img_info[1], CV_32FC1);
    float val;
    for (int i = 0; i < img_info[0]; i++) {
      for (int j = 0; j < img_info[1]; j++) {
        bin_file.read(reinterpret_cast<char *>(&val), sizeof(float));
        img.at<float>(i, j) = val;
      }
    }
  }
  return img;
}
} // namespace ipb::serialization